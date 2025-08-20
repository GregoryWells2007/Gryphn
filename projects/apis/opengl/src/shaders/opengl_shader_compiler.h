#pragma once
#include "stdint.h"
#include "glad/glad.h"
#include "utils/gryphn_cpp_function.h"
#include "core/src/uniforms/gryphn_uniform_layout.h"

#define MAX_OPENGL_SETS 16
#define MAX_OPENGL_BINDINGS 32

typedef enum glShaderModuleStage {
    glVertex = GL_VERTEX_SHADER,
    mtlFragment = GL_FRAGMENT_SHADER,
    mtlMaxStage
} glShaderModuleStage;

typedef struct glCompilerInfo {
    uint32_t* code;
    int wordCount;
    const char* entryPoint;
    // glShaderModuleStage stage;
} glCompilerInfo;

typedef struct glSet { uint32_t bindings[MAX_OPENGL_BINDINGS]; } glSet;

typedef struct glShader {
    char* source;
    glSet sets[MAX_OPENGL_SETS];
} glShader;

typedef struct glCompiler_t* glCompiler;
GN_CPP_FUNCTION glCompiler glCreateCompiler(glCompilerInfo* info);
GN_CPP_FUNCTION glShader glCompilerCompilerShader(glCompiler compiler, gnUniformLayout* layout);
GN_CPP_FUNCTION void glDestroyCompiler(glCompiler compiler);
