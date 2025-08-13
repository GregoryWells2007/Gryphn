#include "metal_shader_compiler.h"
#include "spirv_msl.hpp"
#include "stdlib.h"
// #include "iostream"

typedef struct mtlCompiler_t {
    spirv_cross::CompilerMSL* mslCompiler;
    bool usingArgumentBuffers = false;
    mtlShaderModuleStage stage;
} mtlInternalCompiler;

void handle_resources(spirv_cross::CompilerMSL& compiler, spirv_cross::SmallVector<spirv_cross::Resource>& resources) {
    for (size_t i = 0; i < resources.size(); i++) {
        uint32_t set = compiler.get_decoration(resources[i].id, spv::DecorationDescriptorSet);
        compiler.unset_decoration(resources[i].id, spv::DecorationDescriptorSet);
        compiler.set_decoration(resources[i].id, spv::DecorationDescriptorSet, set + 1);
    }
}

GN_CPP_FUNCTION mtlCompiler mtlCreateCompiler(mtlCompilerInfo* info) {
    mtlInternalCompiler* compiler = (mtlInternalCompiler*)malloc(sizeof(mtlInternalCompiler));
    // if(info->stage == mtlVertex) compiler->mslCompiler->set_entry_point(info->entryPoint, spv::ExecutionModelVertex);
    // if(info->stage == mtlFragment) compiler->mslCompiler->set_entry_point(info->entryPoint, spv::ExecutionModelFragment);
    compiler->mslCompiler = new spirv_cross::CompilerMSL(info->code, info->wordCount);

    spirv_cross::CompilerMSL::Options options = compiler->mslCompiler->get_msl_options();
    options.argument_buffers = (bool)info->useArgumentBuffers;
    options.set_msl_version(info->mslMajorVersion, info->minorVersion);
    compiler->mslCompiler->set_msl_options(options);

    compiler->usingArgumentBuffers = (info->mslMajorVersion >= 2 && info->useArgumentBuffers);
    compiler->stage = info->stage;

    return compiler;
}

GN_CPP_FUNCTION const char* mtlCompilerShader(mtlCompiler compiler, gnUniformLayout* uniformLayout) {
    if (uniformLayout->setCount == 0) goto compile;

    if (compiler->usingArgumentBuffers) {
        // std::vector<spirv_cross::MSLResourceBinding> bindings;
        for (uint32_t i = 0; i < uniformLayout->setCount; i++) {
            uint32_t currentBinding = 0;
            for (size_t c = 0; c < uniformLayout->sets[i].uniformBindingCount; c++) {
                gnUniformBinding gryphnBinding = uniformLayout->sets[i].uniformBindings[c];
                spirv_cross::MSLResourceBinding binding = {
                    .stage = (compiler->stage == mtlVertex) ? spv::ExecutionModelVertex : spv::ExecutionModelFragment,
                    .desc_set = ((uint32_t)i + 1),
                    .binding = gryphnBinding.binding,
                    .count = 1,
                };
                if (gryphnBinding.type == GN_COMBINED_IMAGE_SAMPLER_DESCRIPTOR) {
                    binding.msl_texture = currentBinding;
                    binding.msl_sampler = currentBinding + 1;
                    currentBinding += 2;
                } else if (gryphnBinding.type == GN_SHADER_STORE_BUFFER_DESCRIPTOR || gryphnBinding.type == GN_UNIFORM_BUFFER_DESCRIPTOR) {
                    binding.msl_buffer = currentBinding;
                    currentBinding++;
                }
                // bindings.push_back(binding);
                compiler->mslCompiler->add_msl_resource_binding(binding);
            }
        }
    } else {
        printf("please add support for not using argument buffers on metal\n");
        goto compile;
    }

compile:
    auto arg_buffers = compiler->mslCompiler->get_shader_resources();
    handle_resources(*compiler->mslCompiler, arg_buffers.uniform_buffers);
    handle_resources(*compiler->mslCompiler, arg_buffers.storage_buffers);
    handle_resources(*compiler->mslCompiler, arg_buffers.sampled_images);

    std::string output = compiler->mslCompiler->compile();
    char* copied_output = (char*)malloc(sizeof(char*) * (output.size() + 1));
    strcpy(copied_output, output.c_str());
    copied_output[output.size()] = '\0';
    return copied_output;
}
