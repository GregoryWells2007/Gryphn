#include "opengl_shader_compiler.h"
#include "spirv_glsl.hpp"

typedef struct glCompiler_t {
    spirv_cross::CompilerGLSL* glsl;
} glInternalCompiler;

GN_CPP_FUNCTION glCompiler glCreateCompiler(glCompilerInfo* info) {
    glInternalCompiler* compiler = (glInternalCompiler*)malloc(sizeof(glInternalCompiler));
    compiler->glsl = new spirv_cross::CompilerGLSL(info->code, info->wordCount);
    return compiler;
}
GN_CPP_FUNCTION const char* glCompilerCompilerShader(glCompiler compiler) {
    std::string output = compiler->glsl->compile();
    char* copied_output = (char*)malloc(sizeof(char*) * (output.size() + 1));
    strcpy(copied_output, output.c_str());
    copied_output[output.size()] = '\0';
    return copied_output;
}
