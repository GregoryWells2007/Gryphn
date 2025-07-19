#include "metal_shader_compiler.h"
#include "spirv_msl.hpp"
#include "iostream"

void handle_resources(spirv_cross::CompilerMSL& compiler, spirv_cross::SmallVector<spirv_cross::Resource>& resources) {
    for (int i = 0; i < resources.size(); i++) {
        uint32_t set = compiler.get_decoration(resources[i].id, spv::DecorationDescriptorSet);
        compiler.unset_decoration(resources[i].id, spv::DecorationDescriptorSet);
        compiler.set_decoration(resources[i].id, spv::DecorationDescriptorSet, set + 1);
    }
}

extern "C" const char* mtlCompileShader(uint32_t* code, size_t wordCount, mtlShaderOptions* inOptions) {
    spirv_cross::CompilerMSL compiler(code, wordCount);

   	spirv_cross::CompilerMSL::Options options;
    options.enable_base_index_zero = false;
    if (inOptions->useArgumentBuffers) {
	    options.set_msl_version(3);
		options.argument_buffers = true;
    } else {
        options.set_msl_version(1);
        return NULL;
    }
	compiler.set_msl_options(options);
	if (inOptions->stage == vertex)
	    compiler.set_entry_point(inOptions->entryPoint, spv::ExecutionModelVertex);
	else if (inOptions->stage == fragment)
	    compiler.set_entry_point(inOptions->entryPoint, spv::ExecutionModelFragment);
	else {
	    return NULL;
	}

    auto arg_buffers = compiler.get_shader_resources();
    handle_resources(compiler, arg_buffers.uniform_buffers);
    handle_resources(compiler, arg_buffers.storage_buffers);
    handle_resources(compiler, arg_buffers.sampled_images);

    std::string returnedCode = compiler.compile();
    char* returnString = (char*)malloc(sizeof(char) * returnedCode.size());
    strcpy(returnString, returnedCode.c_str());
    return returnString;
}
