#pragma once
#include "shader_module/gryphn_shader_module.h"
#import <Metal/Metal.h>

typedef struct gnPlatformShaderModule_t {
    id<MTLFunction> function;
} gnPlatformShaderModule;
