#pragma once
#include "stdint.h"
#include "utils/gryphn_bool.h"
#include "utils/gryphn_cpp_function.h"
#include <core/src/uniforms/gryphn_uniform_layout.h>

#define MAX_METAL_SETS 16
#define MAX_METAL_BINDINGS 32

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
