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

        MTLArgumentDescriptor *texDesc = [[MTLArgumentDescriptor alloc] init];
        texDesc.dataType = MTLDataTypeTexture;
        texDesc.index = 0;
        texDesc.access = MTLBindingAccessReadOnly;

        MTLArgumentDescriptor *samplerDesc = [[MTLArgumentDescriptor alloc] init];
        samplerDesc.dataType = MTLDataTypeSampler;
        samplerDesc.index = 1;

        uniforms[i]->uniform->encoder = [pool->device->outputDevice->device newArgumentEncoderWithArguments:@[texDesc, samplerDesc]];
        uniforms[i]->uniform->argumentBuffer = [pool->device->outputDevice->device newBufferWithLength:[uniforms[i]->uniform->encoder encodedLength]
                                                       options:MTLResourceStorageModeShared];

        [uniforms[i]->uniform->encoder setArgumentBuffer:uniforms[i]->uniform->argumentBuffer offset:0];

        // int currentIndex = 0;
        // NSMutableArray* arguments = [NSMutableArray arrayWithCapacity:allocInfo.sets[i].uniformBindingCount];

        // MTLArgumentDescriptor* textureDescriptor = [[MTLArgumentDescriptor alloc] init];
        // textureDescriptor.dataType = MTLDataTypeTexture;
        // textureDescriptor.index = 0;
        // textureDescriptor.arrayLength = 1;
        // textureDescriptor.access = MTLBindingAccessReadOnly;
        // textureDescriptor.textureType = MTLTextureType2D;

        // MTLArgumentDescriptor* samplerDescriptor = [[MTLArgumentDescriptor alloc] init];
        // samplerDescriptor.dataType = MTLDataTypeSampler;
        // samplerDescriptor.index = 1;
        // samplerDescriptor.arrayLength = 1;
        // samplerDescriptor.access = MTLBindingAccessReadOnly;

        // [arguments addObject:textureDescriptor];
        // [arguments addObject:samplerDescriptor];


        // for (int c = 0; c < allocInfo.sets[i].uniformBindingCount; c++) {
        //     if (allocInfo.sets[i].uniformBindings[c].type == GN_IMAGE_DESCRIPTOR) {
        //         MTLArgumentDescriptor* textureDescriptor = [[MTLArgumentDescriptor alloc] init];
        //         textureDescriptor.dataType = MTLDataTypeTexture;
        //         textureDescriptor.index = 0;
        //         textureDescriptor.arrayLength = 1;
        //         textureDescriptor.access = MTLBindingAccessReadOnly;
        //         textureDescriptor.textureType = MTLTextureType2DMultisample;
        //         [arguments addObject:textureDescriptor];

        //         MTLArgumentDescriptor* samplerDescriptor = [[MTLArgumentDescriptor alloc] init];
        //         samplerDescriptor.dataType = MTLDataTypeSampler;
        //         samplerDescriptor.index = 1;
        //         samplerDescriptor.arrayLength = 1;
        //         samplerDescriptor.access = MTLBindingAccessReadOnly;
        //         [arguments addObject:samplerDescriptor];
        //         uniforms[i]->uniform->index[allocInfo.sets[i].uniformBindings[c].binding] = currentIndex;

        //         currentIndex += 2;
        //     }

        // }
        // for (int c = 0; c < allocInfo.sets[i].uniformBindingCount; c++) {
        //     if (allocInfo.sets[i].uniformBindings[c].type == GN_UNIFORM_BUFFER_DESCRIPTOR ||
        //         allocInfo.sets[i].uniformBindings[c].type == GN_SHADER_STORE_BUFFER_DESCRIPTOR) {
        //             // MTLArgumentDescriptor* bufferDescriptor = [[MTLArgumentDescriptor alloc] init];
        //             // bufferDescriptor.dataType = MTLDataTypePointer;
        //             // bufferDescriptor.index = currentIndex;
        //             // bufferDescriptor.arrayLength = 1;
        //             // bufferDescriptor.access = MTLBindingAccessReadOnly;
        //             // [arguments addObject:bufferDescriptor];
        //             // uniforms[i]->uniform->index[allocInfo.sets[i].uniformBindings[c].binding] = currentIndex;

        //             // currentIndex++;
        //     }
        // }
        // if (arguments.count > 0) {
        // uniforms[i]->uniform->encoder = [pool->device->outputDevice->device newArgumentEncoderWithArguments:arguments];
        // uniforms[i]->uniform->argumentBuffer = [pool->device->outputDevice->device newBufferWithLength:uniforms[i]->uniform->encoder.encodedLength options:MTLResourceStorageModeShared];
        // [uniforms[i]->uniform->encoder setArgumentBuffer:uniforms[i]->uniform->argumentBuffer offset:0];
        // }
        // printf("argument encoder %p, argument buffer %p\n", uniforms[i]->uniform->encoder, uniforms[i]->uniform->argumentBuffer);

        // for (int k = 0; k < arguments.count; k++) [[arguments objectAtIndex:k] release];
    }
    return uniforms;
}

void destroyMetalUniformPool(gnUniformPool pool) { free(pool->uniformPool); }
