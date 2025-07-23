#include <uniforms/gryphn_uniform.h>
#include "metal_uniform.h"
#include "devices/metal_output_devices.h"
#include "texture/metal_texture.h"
#include <buffer/metal_buffer.h>

void mtlUpdateMetalBufferUniform(gnUniformHandle uniform, mtlBufferUniformInfo* info) {
    if (uniform->uniform->indexMap[info->baseInfo->binding] == -1) {
        uniform->uniform->indexMap[info->baseInfo->binding] = uniform->uniform->usedResourceCount;
        uniform->uniform->usedResourceCount++;
    }
    uniform->uniform->isDynamic[info->baseInfo->binding] = info->baseInfo->dynamic;
    uniform->uniform->usedResources[uniform->uniform->indexMap[info->baseInfo->binding]] = info->buffer;
    if ((uniform->uniform->stageUsed[info->baseInfo->binding] & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE)
        [uniform->uniform->encoders[mtlVertex] setBuffer:info->buffer offset:info->baseInfo->offset atIndex:uniform->uniform->indexMap[info->baseInfo->binding]];
    if ((uniform->uniform->stageUsed[info->baseInfo->binding] & GN_FRAGMENT_SHADER_MODULE) == GN_FRAGMENT_SHADER_MODULE)
        [uniform->uniform->encoders[mtlFragment] setBuffer:info->buffer offset:info->baseInfo->offset atIndex:uniform->uniform->index[info->baseInfo->binding]];
}

void updateMetalBufferUniform(gnUniform uniform, gnBufferUniformInfo* info) {
    mtlBufferUniformInfo mtlInfo = {
        .baseInfo = info,
        .buffer = info->buffer->buffer->buffer
    };
    mtlUpdateMetalBufferUniform(uniform, &mtlInfo);
}
void updateMetalStorageUniform(gnUniform uniform, gnStorageUniformInfo* info) {
    if (uniform->uniform->indexMap[info->binding] == -1) {
        uniform->uniform->indexMap[info->binding] = uniform->uniform->usedResourceCount;
        uniform->uniform->usedResourceCount++;
    }
    uniform->uniform->usedResources[uniform->uniform->indexMap[info->binding]] = info->buffer->buffer->buffer;
    if ((uniform->uniform->stageUsed[info->binding] & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE)
        [uniform->uniform->encoders[mtlVertex] setBuffer:info->buffer->buffer->buffer offset:info->offset atIndex:uniform->uniform->indexMap[info->binding]];
    if ((uniform->uniform->stageUsed[info->binding] & GN_FRAGMENT_SHADER_MODULE) == GN_FRAGMENT_SHADER_MODULE)
        [uniform->uniform->encoders[mtlFragment] setBuffer:info->buffer->buffer->buffer offset:info->offset atIndex:uniform->uniform->index[info->binding]];
}

void updateMetalImageUniform(gnUniform uniform, gnImageUniformInfo* info) {
    if (uniform->uniform->indexMap[info->binding] == -1) {
        uniform->uniform->indexMap[info->binding] = uniform->uniform->usedResourceCount;
        uniform->uniform->usedResourceCount++;
    }
    uniform->uniform->usedResources[uniform->uniform->indexMap[info->binding]] = info->texture->texture->texture;
    if ((uniform->uniform->stageUsed[info->binding] & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE) {
        [uniform->uniform->encoders[mtlVertex] setTexture:info->texture->texture->texture atIndex:uniform->uniform->indexMap[info->binding]];
        [uniform->uniform->encoders[mtlVertex] setSamplerState:info->texture->texture->sampler atIndex:uniform->uniform->indexMap[info->binding] + 1];
    }
    if ((uniform->uniform->stageUsed[info->binding] & GN_FRAGMENT_SHADER_MODULE) == GN_FRAGMENT_SHADER_MODULE) {
        [uniform->uniform->encoders[mtlFragment] setTexture:info->texture->texture->texture atIndex:uniform->uniform->index[info->binding]];
        [uniform->uniform->encoders[mtlFragment] setSamplerState:info->texture->texture->sampler atIndex:uniform->uniform->index[info->binding] + 1];
    }
}
