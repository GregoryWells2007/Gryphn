#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "utils/gryphn_bool.h"

#define MAX_METAL_SETS 32
#define MAX_METAL_BINDINGS 16

typedef enum mtlShaderModuleStage {
    vertex, fragment
} mtlShaderModuleStage;

typedef struct mtlShaderOptions {
    gnBool useArgumentBuffers;
    mtlShaderModuleStage stage;
    const char* entryPoint;
} mtlShaderOptions;

typedef struct mtlBinding {
    uint32_t spvBinding;
    uint32_t metalID;
} mtlBinding;

typedef struct mtlSetMap {
    uint32_t setIndex, mtlSetIndex;
    mtlBinding bindings[MAX_METAL_BINDINGS];
} mtlSetMap;

typedef struct mtlShaderMap {
    mtlSetMap sets[MAX_METAL_SETS];
} mtlShaderMap;

typedef struct mtlShader {
    const char* code;
    mtlShaderMap map;
} mtlShader;

#ifdef __cplusplus
extern "C"
#endif
mtlShader mtlCompileShader(uint32_t* code, size_t wordCount, mtlShaderOptions* options);
