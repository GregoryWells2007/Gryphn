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

    // for (auto &pc : arg_buffers.push_constant_buffers) {
    //     compiler->glsl->set_name(pc.id, "gnPushConstantBlock");
    //     auto type = compiler->glsl->get_type(pc.type_id);
    //     // printf("members: %lu\n", type.member_types.size());
    //     for (uint32_t i = 0; i < type.member_types.size(); ++i) {
    //     //     // std::string name = compiler->glsl->get_member_name(pc.type_id, i);

    //     //     compiler.set_member_name(push_constant_type_id, 0, "myMat4");
    //     //     compiler.set_member_name(push_constant_type_id, 1, "myVec3");
    //     //     compiler.set_member_name(push_constant_type_id, 2, "myInt");

    //         auto member_type = compiler->glsl->get_type(type.member_types[i]);

    //     //     // Example: check if it's a mat4, vec3, or int
    //     //     if (member_type.columns == 4 && member_type.vecsize == 4)
    //     //         printf("member %s: mat4\n", name.c_str());
    //     //     else if (member_type.vecsize == 3 && member_type.columns == 1)
    //     //         printf("member %s: vec3\n", name.c_str());
    //     //     else if (member_type.basetype == spirv_cross::SPIRType::Int)
    //     //         printf("member %s: int\n", name.c_str());
    //     }
    // }

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
