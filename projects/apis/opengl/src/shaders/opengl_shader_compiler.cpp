#include "opengl_shader_compiler.h"
#include "spirv_glsl.hpp"

typedef struct glCompiler_t {
    spirv_cross::CompilerGLSL* glsl;
} glInternalCompiler;

void handle_resources(spirv_cross::CompilerGLSL& compiler, spirv_cross::SmallVector<spirv_cross::Resource>& resources, int* currentBinding, glSet* setMap) {
    for (size_t i = 0; i < resources.size(); i++) {
        uint32_t
            set     = compiler.get_decoration(resources[i].id, spv::DecorationDescriptorSet),
            binding = compiler.get_decoration(resources[i].id, spv::DecorationBinding);
        setMap[set].bindings[binding] = *currentBinding;

        compiler.unset_decoration(resources[i].id, spv::DecorationBinding);
        compiler.set_decoration(resources[i].id, spv::DecorationBinding, *currentBinding);
        *currentBinding = (*currentBinding) + 1;
    }
}

GN_CPP_FUNCTION glCompiler glCreateCompiler(glCompilerInfo* info) {
    glInternalCompiler* compiler = (glInternalCompiler*)malloc(sizeof(glInternalCompiler));
    compiler->glsl = new spirv_cross::CompilerGLSL(info->code, info->wordCount);
    // spirv_cross::CompilerGLSL::Options options = compiler->glsl->get_common_options();
    // compiler->glsl->set_common_options(options);
    return compiler;
}
GN_CPP_FUNCTION glShader glCompilerCompilerShader(glCompiler compiler) {
    int current_binding = 0;

    glShader shader = {};
    auto arg_buffers = compiler->glsl->get_shader_resources();
    handle_resources(*compiler->glsl, arg_buffers.uniform_buffers, &current_binding, shader.sets);
    handle_resources(*compiler->glsl, arg_buffers.storage_buffers, &current_binding, shader.sets);
    handle_resources(*compiler->glsl, arg_buffers.sampled_images, &current_binding, shader.sets);

    shader.sets[0].bindings[3] = 69;

    std::string output = compiler->glsl->compile();
    shader.source = (char*)malloc(sizeof(char*) * (output.size() + 1));
    strcpy(shader.source, output.c_str());
    shader.source[output.size()] = '\0';
    return shader;
}

GN_CPP_FUNCTION void glDestroyCompiler(glCompiler compiler) {
    delete compiler->glsl;
    free(compiler);
}
