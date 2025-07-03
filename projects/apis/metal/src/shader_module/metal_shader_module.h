#pragma once
#include "shader_module/gryphn_shader_module.h"
#include "utils/lists/gryphn_array_list.h"
#import <Metal/Metal.h>

#define METAL_MAX_SET_COUNT 16
#define METAL_MAX_BINDING_COUNT 16

typedef struct metalSetMap {
    uint32_t bindings[METAL_MAX_BINDING_COUNT];
} metalSetMap;

typedef struct metalShaderMap {
    metalSetMap sets[METAL_MAX_SET_COUNT];
    uint32_t pushConstantBufferIndex;
} metalShaderMap;

typedef struct gnPlatformShaderModule_t {
    id<MTLFunction> function;
    metalShaderMap map;
} gnPlatformShaderModule;

gnReturnCode createMetalShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo);
void destroyMetalShaderModule(gnShaderModule module);
