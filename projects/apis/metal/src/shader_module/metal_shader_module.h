#pragma once
#include "shader_module/gryphn_shader_module.h"
#include "utils/lists/gryphn_array_list.h"
#import <Metal/Metal.h>

typedef struct metalBindingMap {
    uint32_t set;
    uint32_t binding;
    uint32_t metalBindingIndex;
} metalBindingMap;
GN_ARRAY_LIST(metalBindingMap);

typedef struct metalBindingMaps {
    metalBindingMapArrayList textureMaps;
} metalBindingMaps;

typedef struct gnPlatformShaderModule_t {
    id<MTLFunction> function;
    uint32_t pushConstantIndex;
    metalBindingMaps maps;
} gnPlatformShaderModule;

gnReturnCode createMetalShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo);
void destroyMetalShaderModule(gnShaderModule module);
