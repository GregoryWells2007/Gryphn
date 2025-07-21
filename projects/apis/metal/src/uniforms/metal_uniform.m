#include <uniforms/gryphn_uniform.h>
#include "metal_uniform.h"
#include "devices/metal_output_devices.h"
#include "texture/metal_texture.h"
#include <buffer/metal_buffer.h>

void updateMetalBufferUniform(gnUniform uniform, gnBufferUniformInfo* info) {
    // [uniform->uniform->encoder setBuffer:info->buffer->buffer->buffer offset:0 atIndex:0];
}

void updateMetalStorageUniform(gnUniform uniform, gnStorageUniformInfo* info) {
    // [uniform->uniform->encoder setBuffer:info->buffer->buffer->buffer offset:0 atIndex:uniform->uniform->index[info->binding]];
    // for (int i = 0; i < uniform->uniform->bindingCount; i++) {
    //     if (uniform->uniform->bindings[i].binding == info->binding) {
    //         uniform->uniform->bindings[i].data = malloc(sizeof(gnStorageUniformInfo));
    //         memcpy(uniform->uniform->bindings[i].data, info, sizeof(gnStorageUniformInfo));
    //         break;
    //     }
    // }
}

void updateMetalImageUniform(gnUniform uniform, gnImageUniformInfo* info) {
    // mtlResource usedResources[MAX_METAL_BINDINGS];
    // uint32_t indexMap[MAX_METAL_BINDINGS];
    // uint32_t usedResourceCount;

    if (uniform->uniform->indexMap[info->binding] == -1) {
        uniform->uniform->indexMap[info->binding] = uniform->uniform->usedResourceCount;
        uniform->uniform->usedResourceCount++;
    }

    uniform->uniform->usedResources[uniform->uniform->indexMap[info->binding]] = info->texture->texture->texture;

    [uniform->uniform->encoder setTexture:info->texture->texture->texture atIndex:uniform->uniform->index[info->binding]];
    [uniform->uniform->encoder setSamplerState:info->texture->texture->sampler atIndex:uniform->uniform->index[info->binding] + 1];

    // uniform->uniform->resources = mtlResourceArrayListCreate();
    // mtlResourceArrayListAdd(&uniform->uniform->resources, info->texture->texture->texture);
    // mtlResourceArrayListAdd(&uniform->uniform->resources, info->texture->texture->sampler);


    // printf("updating metal image uniform %i\n", uniform->uniform->index[info->binding]);

    // printf("binding: %i\n", info->binding);
    // printf("mapped index: %i\n", uniform->uniform->index[info->binding]);
    // id<MTLBuffer> buffer = [uniform->pool->device->outputDevice->device newBufferWithLength:sizeof(int) options:MTLResourceStorageModeShared];
    // printf("uniform %p | uniform->uniform %p | encoder %p\n", uniform, uniform->uniform, uniform->uniform->encoder);
    // [uniform->uniform->encoder setBuffer:buffer offset:0 atIndex:0];
    //info->binding

    // for (int i = 0; i < uniform->uniform->bindingCount; i++) {
    //     if (uniform->uniform->bindings[i].binding == info->binding) {
    //         uniform->uniform->bindings[i].data = malloc(sizeof(gnImageUniformInfo));
    //         memcpy(uniform->uniform->bindings[i].data, info, sizeof(gnImageUniformInfo));
    //         break;
    //     }
    // }
}
