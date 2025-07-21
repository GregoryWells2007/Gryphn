#include <uniforms/gryphn_uniform_pool.h>
#include <uniforms/gryphn_uniform.h>
#include "metal_uniform.h"
#include "devices/metal_output_devices.h"

gnReturnCode createMetalUniformPool(gnUniformPool pool, gnDeviceHandle device) {
    return GN_SUCCESS;
}

gnUniform* allocateMetalUniforms(gnUniformPool pool, const gnUniformAllocationInfo allocInfo) {
    gnUniform* uniforms = malloc(sizeof(gnUniform) * allocInfo.setCount);
    for (int i = 0; i < allocInfo.setCount; i++) {
        uniforms[i] = malloc(sizeof(struct gnUniform_t));
        uniforms[i]->uniform = malloc(sizeof(gnPlatformUniform));
        int currentIndex = 0;
        NSMutableArray* totalArguments = [NSMutableArray arrayWithCapacity:allocInfo.sets[i].uniformBindingCount];
        NSMutableArray* vertexArguments = [NSMutableArray arrayWithCapacity:allocInfo.sets[i].uniformBindingCount];
        NSMutableArray* fragmentArguments = [NSMutableArray arrayWithCapacity:allocInfo.sets[i].uniformBindingCount];

        for (int c = 0; c < allocInfo.sets[i].uniformBindingCount; c++) {
            gnUniformBinding binding = allocInfo.sets[i].uniformBindings[c];
            if (binding.type == GN_UNIFORM_BUFFER_DESCRIPTOR ||
                binding.type == GN_SHADER_STORE_BUFFER_DESCRIPTOR) {
                    MTLArgumentDescriptor* descriptor = [[MTLArgumentDescriptor alloc] init];
                    descriptor.dataType = MTLDataTypePointer;
                    descriptor.index = 0;
                    descriptor.arrayLength = 1;
                    descriptor.access = MTLBindingAccessReadOnly;

                    if ((binding.stage & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE) [vertexArguments addObject:descriptor];
                    if ((binding.stage & GN_FRAGMENT_SHADER_MODULE) == GN_FRAGMENT_SHADER_MODULE) [fragmentArguments addObject:descriptor];
                    [totalArguments addObject:descriptor];

                    uniforms[i]->uniform->index[allocInfo.sets[i].uniformBindings[c].binding] = currentIndex;
                    currentIndex++;
            } else if (allocInfo.sets[i].uniformBindings[c].type == GN_COMBINED_IMAGE_SAMPLER_DESCRIPTOR) {
                    MTLArgumentDescriptor* textureDescriptor = [[MTLArgumentDescriptor alloc] init];
                    textureDescriptor.dataType = MTLDataTypeTexture;
                    textureDescriptor.index = 1;
                    textureDescriptor.arrayLength = 1;
                    textureDescriptor.access = MTLBindingAccessReadOnly;
                    if ((binding.stage & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE) [vertexArguments addObject:textureDescriptor];
                    if ((binding.stage & GN_FRAGMENT_SHADER_MODULE) == GN_FRAGMENT_SHADER_MODULE) [fragmentArguments addObject:textureDescriptor];
                    [totalArguments addObject:textureDescriptor];

                    MTLArgumentDescriptor* samplerDescriptor = [[MTLArgumentDescriptor alloc] init];
                    samplerDescriptor.dataType = MTLDataTypeSampler;
                    samplerDescriptor.index = 2;
                    samplerDescriptor.arrayLength = 1;
                    samplerDescriptor.access = MTLBindingAccessReadOnly;
                    if ((binding.stage & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE) [vertexArguments addObject:samplerDescriptor];
                    if ((binding.stage & GN_FRAGMENT_SHADER_MODULE) == GN_FRAGMENT_SHADER_MODULE) [fragmentArguments addObject:samplerDescriptor];
                    [totalArguments addObject:samplerDescriptor];
                    uniforms[i]->uniform->index[binding.binding] = currentIndex;
                    currentIndex += 2;
            }
            uniforms[i]->uniform->stageUsed[binding.binding] = binding.stage;
        }
        if (vertexArguments.count > 0) {
            uniforms[i]->uniform->encoders[mtlVertex] = [pool->device->outputDevice->device newArgumentEncoderWithArguments:vertexArguments];
            uniforms[i]->uniform->argumentBuffers[mtlVertex] = [pool->device->outputDevice->device newBufferWithLength:uniforms[i]->uniform->encoders[mtlVertex].encodedLength options:MTLResourceStorageModeShared];
            [uniforms[i]->uniform->encoders[mtlVertex] setArgumentBuffer:uniforms[i]->uniform->argumentBuffers[mtlVertex] offset:0];
        }

        if (fragmentArguments.count > 0) {
            uniforms[i]->uniform->encoders[mtlFragment] = [pool->device->outputDevice->device newArgumentEncoderWithArguments:fragmentArguments];
            uniforms[i]->uniform->argumentBuffers[mtlFragment] = [pool->device->outputDevice->device newBufferWithLength:uniforms[i]->uniform->encoders[mtlFragment].encodedLength options:MTLResourceStorageModeShared];
            [uniforms[i]->uniform->encoders[mtlFragment] setArgumentBuffer:uniforms[i]->uniform->argumentBuffers[mtlFragment] offset:0];
        }

        for (int k = 0; k < totalArguments.count; k++) [[totalArguments objectAtIndex:k] release];
        [totalArguments release];
        for (int g = 0; g < MAX_METAL_BINDINGS; g++) uniforms[i]->uniform->indexMap[g] = -1;
    }
    return uniforms;
}

void destroyMetalUniformPool(gnUniformPool pool) { free(pool->uniformPool); }
