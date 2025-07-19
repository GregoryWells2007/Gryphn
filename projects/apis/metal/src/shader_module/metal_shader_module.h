#pragma once
#include "shader_module/gryphn_shader_module.h"
#include "utils/lists/gryphn_array_list.h"
#include "metal_shader_compiler.h"
#import <Metal/Metal.h>

typedef struct gnPlatformShaderModule_t {
    id<MTLFunction> function;
    mtlShaderMap shaderMap;
} gnPlatformShaderModule;

#ifdef __cplusplus
extern "C" {
#endif
    gnReturnCode createMetalShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo);
    void destroyMetalShaderModule(gnShaderModule module);
#ifdef __cplusplus
}
#endif
