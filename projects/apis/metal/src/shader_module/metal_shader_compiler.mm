#include "metal_shader_compiler.h"
#include "spirv_msl.hpp"
#include "iostream"

void handle_resources(spirv_cross::CompilerMSL& compiler, spirv_cross::SmallVector<spirv_cross::Resource>& resources, mtlShaderMap* map) {
    for (int i = 0; i < resources.size(); i++) {
        uint32_t set = compiler.get_decoration(resources[i].id, spv::DecorationDescriptorSet);
        compiler.unset_decoration(resources[i].id, spv::DecorationDescriptorSet);
        compiler.set_decoration(resources[i].id, spv::DecorationDescriptorSet, set + 1);
        map->sets[set].setIndex = set;
        map->sets[set].mtlSetIndex = set + 1;
    }
}

void improve_map(spirv_cross::CompilerMSL& compiler, spirv_cross::SmallVector<spirv_cross::Resource>& resources, mtlShaderMap* map) {
    for (int i = 0; i < resources.size(); i++) {
        uint32_t set = compiler.get_decoration(resources[i].id, spv::DecorationDescriptorSet);
        uint32_t binding = compiler.get_decoration(resources[i].id, spv::DecorationBinding);
        map->sets[(set - 1)].bindings[binding].spvBinding = binding;
        map->sets[(set - 1)].bindings[binding].metalID = compiler.get_automatic_msl_resource_binding(resources[i].id);
    }
}

extern "C" mtlShader mtlCompileShader(uint32_t* code, size_t wordCount, mtlShaderOptions* inOptions) {
    spirv_cross::CompilerMSL compiler(code, wordCount);

   	spirv_cross::CompilerMSL::Options options;
    options.enable_base_index_zero = false;
    if (inOptions->useArgumentBuffers) {
	    options.set_msl_version(3);
		options.argument_buffers = true;
    } else {
        options.set_msl_version(1);
        return {};
    }
	compiler.set_msl_options(options);
	if (inOptions->stage == vertex)
	    compiler.set_entry_point(inOptions->entryPoint, spv::ExecutionModelVertex);
	else if (inOptions->stage == fragment)
	    compiler.set_entry_point(inOptions->entryPoint, spv::ExecutionModelFragment);
	else {
	    return {};
	}

    mtlShaderMap map;
    for (int i = 0; i < MAX_METAL_SETS; i++) {
        map.sets[i].mtlSetIndex = -1;
        map.sets[i].setIndex = -1;
        for (int c = 0; c < MAX_METAL_BINDINGS; c++) {
            map.sets[i].bindings[c].spvBinding = -1;
            map.sets[i].bindings[c].metalID = -1;
        }
    }
    auto arg_buffers = compiler.get_shader_resources();
    handle_resources(compiler, arg_buffers.uniform_buffers, &map);
    handle_resources(compiler, arg_buffers.storage_buffers, &map);
    handle_resources(compiler, arg_buffers.sampled_images, &map);

    std::string returnedCode = compiler.compile();

    improve_map(compiler, arg_buffers.uniform_buffers, &map);
    improve_map(compiler, arg_buffers.storage_buffers, &map);
    improve_map(compiler, arg_buffers.sampled_images, &map);

    char* returnString = (char*)malloc(sizeof(char) * (returnedCode.size() + 1));
    strcpy(returnString, returnedCode.c_str());
    return {
        .code = returnString,
        .map = map
    };
}
