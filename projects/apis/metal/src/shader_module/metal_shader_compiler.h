#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "utils/gryphn_bool.h"

typedef enum mtlShaderModuleStage {
    vertex, fragment
} mtlShaderModuleStage;

typedef struct mtlShaderOptions {
    gnBool useArgumentBuffers;
    mtlShaderModuleStage stage;
    const char* entryPoint;
} mtlShaderOptions;

#ifdef __cplusplus
extern "C"
#endif
const char* mtlCompileShader(uint32_t* code, size_t wordCount, mtlShaderOptions* options);
