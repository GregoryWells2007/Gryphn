#include <uniforms/gryphn_uniform.h>
#include "metal_uniform.h"

void updateMetalBufferUniform(gnUniform uniform, gnBufferUniformInfo* info) {
    for (int i = 0; i < uniform->uniform->bindingCount; i++) {
        if (uniform->uniform->bindings[i].binding == info->binding) {
            uniform->uniform->bindings[i].data = malloc(sizeof(gnBufferUniformInfo));
            memcpy(uniform->uniform->bindings[i].data, info, sizeof(gnBufferUniformInfo));
            break;
        }
    }
}

void updateMetalStorageUniform(gnUniform uniform, gnStorageUniformInfo* info) {
    for (int i = 0; i < uniform->uniform->bindingCount; i++) {
        if (uniform->uniform->bindings[i].binding == info->binding) {
            uniform->uniform->bindings[i].data = malloc(sizeof(gnStorageUniformInfo));
            memcpy(uniform->uniform->bindings[i].data, info, sizeof(gnStorageUniformInfo));
            break;
        }
    }
}

void updateMetalImageUniform(gnUniform uniform, gnImageUniformInfo* info) {
    for (int i = 0; i < uniform->uniform->bindingCount; i++) {
        if (uniform->uniform->bindings[i].binding == info->binding) {
            uniform->uniform->bindings[i].data = malloc(sizeof(gnImageUniformInfo));
            memcpy(uniform->uniform->bindings[i].data, info, sizeof(gnImageUniformInfo));
            break;
        }
    }
}
