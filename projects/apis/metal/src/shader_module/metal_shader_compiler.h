#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "utils/gryphn_bool.h"
#include <core/src/uniforms/gryphn_uniform_layout.h>

#ifdef __cplusplus
#define GN_CPP_FUNCTION extern "C"
#else
#define GN_CPP_FUNCTION
#endif

#define MAX_METAL_SETS 32
#define MAX_METAL_BINDINGS 16

typedef struct mtlCompiler_t* mtlCompiler;

typedef enum mtlShaderModuleStage {
    mtlVertex, mtlFragment, mtlMaxStage
} mtlShaderModuleStage;

typedef struct mtlCompilerInfo {
    uint32_t* code;
    int wordCount;
    const char* entryPoint;
    mtlShaderModuleStage stage;

    int mslMajorVersion, minorVersion;
    gnBool useArgumentBuffers;
} mtlCompilerInfo;

GN_CPP_FUNCTION mtlCompiler mtlCreateCompiler(mtlCompilerInfo* info);
GN_CPP_FUNCTION const char* mtlCompilerShader(mtlCompiler compiler, gnUniformLayout* uniformLayout);

// typedef struct mtlShaderOptions {
//     gnBool useArgumentBuffers;
//     mtlShaderModuleStage stage;
//     const char* entryPoint;
// } mtlShaderOptions;

// typedef struct mtlBinding {
//     uint32_t spvBinding;
//     uint32_t metalID;
// } mtlBinding;

// typedef struct mtlSetMap {
//     uint32_t setIndex, mtlSetIndex;
//     mtlBinding bindings[MAX_METAL_BINDINGS];
// } mtlSetMap;

// typedef struct mtlShaderMap {
//     mtlSetMap sets[MAX_METAL_SETS];
// } mtlShaderMap;

// typedef struct mtlShader {
//     const char* code;
//     mtlShaderMap map;
// } mtlShader;

// #ifdef __cplusplus
// extern "C"
// #endif
// mtlShader mtlCompileShader(uint32_t* code, size_t wordCount, mtlShaderOptions* options);
