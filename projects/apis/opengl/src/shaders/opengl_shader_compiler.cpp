#include "opengl_shader_compiler.h"
#include "spirv_glsl.hpp"

typedef struct glCompiler_t {
    spirv_cross::CompilerGLSL* glsl;
} glInternalCompiler;



void handle_resources(spirv_cross::CompilerGLSL& compiler, spirv_cross::SmallVector<spirv_cross::Resource>& resources, glSet* setMap) {
    for (size_t i = 0; i < resources.size(); i++) {
        uint32_t
            set     = compiler.get_decoration(resources[i].id, spv::DecorationDescriptorSet),
            binding = compiler.get_decoration(resources[i].id, spv::DecorationBinding);
        compiler.unset_decoration(resources[i].id, spv::DecorationBinding);
        compiler.set_decoration(resources[i].id, spv::DecorationBinding, setMap[set].bindings[binding]);
    }
}

GN_CPP_FUNCTION glCompiler glCreateCompiler(glCompilerInfo* info) {
    glInternalCompiler* compiler = (glInternalCompiler*)malloc(sizeof(glInternalCompiler));
    compiler->glsl = new spirv_cross::CompilerGLSL(info->code, info->wordCount);
    // spirv_cross::CompilerGLSL::Options options = compiler->glsl->get_common_options();
    // compiler->glsl->set_common_options(options);
    return compiler;
}
GN_CPP_FUNCTION glShader glCompilerCompilerShader(glCompiler compiler, gnUniformLayout* layout) {
    glShader shader = {};
    uint32_t currentBinding = 0;
    for (uint32_t i = 0; i < layout->setCount; i++) {
        for (size_t c = 0; c < layout->sets[i].uniformBindingCount; c++) {
            gnUniformBinding gryphnBinding = layout->sets[i].uniformBindings[c];
            shader.sets[i].bindings[c] = currentBinding;
            currentBinding++;
        }
    }

    auto arg_buffers = compiler->glsl->get_shader_resources();
    handle_resources(*compiler->glsl, arg_buffers.uniform_buffers, shader.sets);
    handle_resources(*compiler->glsl, arg_buffers.storage_buffers, shader.sets);
    handle_resources(*compiler->glsl, arg_buffers.sampled_images, shader.sets);

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
