#include "metal_shader_compiler.h"
#include "spirv_msl.hpp"

// spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_UNIFORM_BUFFER, &list, &count);
//         // [[buffer(0)]] is reserved for stage_in, [[buffer(1)]] is reserved for push_constant
//         uint32_t currentBufferBinding = 2, currentTextureBinding = 0;
//         for (int i = 0; i < count; i++) {
//             uint32_t set = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationDescriptorSet),
//                     binding = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationBinding);
//             spvc_compiler_unset_decoration(compiler, list[i].id, SpvDecorationBinding);
//             spvc_compiler_set_decoration(compiler, list[i].id, SpvDecorationBinding, currentBufferBinding);
//             module->shaderModule->map.sets[set].bindings[binding] = currentBufferBinding;
//             currentBufferBinding++;
//         }

//         spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_SAMPLED_IMAGE, &list, &count);
//         for (int i = 0; i < count; i++) {
//             uint32_t set = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationDescriptorSet),
//                     binding = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationBinding);
//             spvc_compiler_unset_decoration(compiler, list[i].id, SpvDecorationBinding);
//             spvc_compiler_set_decoration(compiler, list[i].id, SpvDecorationBinding, currentTextureBinding);
//             module->shaderModule->map.sets[set].bindings[binding] = currentTextureBinding;
//             currentTextureBinding++;
//         }

//         spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_STORAGE_BUFFER, &list, &count);
//         for (int i = 0; i < count; i++) {
//             uint32_t set = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationDescriptorSet),
//                     binding = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationBinding);
//             spvc_compiler_unset_decoration(compiler, list[i].id, SpvDecorationBinding);
//             spvc_compiler_set_decoration(compiler, list[i].id, SpvDecorationBinding, currentBufferBinding);
//             module->shaderModule->map.sets[set].bindings[binding] = currentBufferBinding;
//             currentBufferBinding++;
//         }

//         spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_PUSH_CONSTANT, &list, &count);
//         for (int i = 0; i < count; i++) {
//             spvc_compiler_unset_decoration(compiler, list[i].id, SpvDecorationBinding);
//             spvc_compiler_set_decoration(compiler, list[i].id, SpvDecorationBinding, 1);
//         }

extern "C" const char* mtlCompileShader(uint32_t* code, size_t wordCount, mtlShaderOptions* inOptions) {
    spirv_cross::CompilerMSL compiler(code, wordCount);

   	spirv_cross::CompilerMSL::Options options;
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

    std::string returnedCode = compiler.compile();
    char* returnString = (char*)malloc(sizeof(char) * returnedCode.size());
    strcpy(returnString, returnedCode.c_str());
    return returnString;
}
