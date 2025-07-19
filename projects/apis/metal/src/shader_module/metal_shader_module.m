#include "metal_shader_module.h"
#include "spirv_cross_c.h"
#include "instance/gryphn_debugger.h"
#include "devices/metal_output_devices.h"
#include "metal_shader_compiler.h"
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

gnReturnCode createMetalShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo) {
    mtlShaderOptions options = {

    };

    const char* res = mtlCompileShader(shaderModuleInfo.code, shaderModuleInfo.size, &options);
    printf("compiled res: %s\n", res);

    return GN_SUCCESS;
}
// void mtlSpirVErrorCallback(void *userdata, const char *error) {
//     gnDebuggerInfo debugger = *((gnDebuggerInfo*)userdata);
//     gnDebuggerSetErrorMessage(debugger, (gnMessageData){
//         .message = gnCombineStrings(gnCreateString("shader compilation error MSL "), gnCreateString(error))
//     });
// }

// extern "C" gnReturnCode createMetalShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo) {
//     module->shaderModule = (gnPlatformShaderModule_t*)malloc(sizeof(gnPlatformShaderModule_t));

//     MTLArgumentBuffersTier supportsArgumentBuffers = device->outputDevice->device.argumentBuffersSupport;
//     module->shaderModule->useShaderMap = !(supportsArgumentBuffers == MTLArgumentBuffersTier2);

//     spvc_context context = NULL;
//     spvc_parsed_ir ir = NULL;
//     spvc_compiler compiler = NULL;
//     const char *result = NULL;
//     spvc_resources resources = NULL;
//     const spvc_reflected_resource *list = NULL;
//     spvc_compiler_options options = NULL;
//     size_t count;

//     spvc_context_create(&context);
//     spvc_context_set_error_callback(context, mtlSpirVErrorCallback, &module->device->instance->debugger);
//     spvc_context_parse_spirv(context, shaderModuleInfo.code, shaderModuleInfo.size / 4, &ir);
//     spvc_context_create_compiler(context, SPVC_BACKEND_MSL, ir, SPVC_CAPTURE_MODE_COPY, &compiler);
//     spvc_compiler_create_shader_resources(compiler, &resources);

//     spvc_compiler_create_compiler_options(compiler, &options);
//     if (module->shaderModule->useShaderMap) {
//         spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_UNIFORM_BUFFER, &list, &count);
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
//         spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_MSL_VERSION, SPVC_MAKE_MSL_VERSION(1, 0, 0));
//     } else {
//         spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_MSL_VERSION, SPVC_MAKE_MSL_VERSION(3, 0, 0));
//         spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_MSL_ARGUMENT_BUFFERS, true);
//         spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_MSL_FORCE_ACTIVE_ARGUMENT_BUFFER_RESOURCES, true);
//         spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_MSL_ARGUMENT_BUFFERS_TIER, 2);

//         const spvc_combined_image_sampler* samplers;
//         size_t sampler_count;

//         spvc_compiler_build_combined_image_samplers(compiler);
//         spvc_compiler_get_combined_image_samplers(compiler, &samplers, &sampler_count);
//         printf("sampler count: %zu\n", sampler_count);
//         for (size_t i = 0; i < sampler_count; ++i) {
//             printf("Combined: image ID %u + sampler ID %u = ID %u\n",
//                    samplers[i].image_id,
//                    samplers[i].sampler_id,
//                    samplers[i].combined_id);
//         }

//         // spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_SAMPLED_IMAGE, &list, &count);
//         // for (int i = 0; i < count; i++) {
//         //     spvc_compiler
//         //     // uint32_t set = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationDescriptorSet),
//         //     //         binding = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationBinding);
//         //     // spvc_compiler_unset_decoration(compiler, list[i].id, SpvDecorationBinding);
//         //     // spvc_compiler_set_decoration(compiler, list[i].id, SpvDecorationBinding, currentTextureBinding);
//         //     // module->shaderModule->map.sets[set].bindings[binding] = currentTextureBinding;
//         //     // currentTextureBinding++;
//         // }
//     }

//     spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_MSL_ENABLE_DECORATION_BINDING, true);
//     spvc_compiler_install_compiler_options(compiler, options);

//     SpvExecutionModel executionModel = SpvExecutionModelVertex;
//     if (shaderModuleInfo.stage == GN_FRAGMENT_SHADER_MODULE) executionModel = SpvExecutionModelFragment;

//     spvc_compiler_set_entry_point(compiler, shaderModuleInfo.entryPoint.value, executionModel);
//     spvc_result res = spvc_compiler_compile(compiler, &result);
//     printf("res: %s\n", result);

//     if (res != SPVC_SUCCESS)
//         return GN_FAILED_TO_CONVERT_SHADER_CODE;

//     NSError* error = nil;
//     MTLCompileOptions* mtloptions = nil;
//     NSString* sourceCode = [NSString stringWithCString:result encoding:NSUTF8StringEncoding];
//     id<MTLLibrary> shaderLib = [device->outputDevice->device    newLibraryWithSource:sourceCode options:mtloptions error:&error];
//     if (!shaderLib) {
//         const char* errorString = error.localizedDescription.UTF8String;
//         gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
//             .message = gnCombineStrings(gnCreateString("Failed to compile metal library "), errorString)
//         });
//         return GN_FAILED_TO_CREATE_SHADER_MODULE;
//     }

//     const char* name = shaderModuleInfo.entryPoint.value;
//     if (strcmp(name, "main") == 0) {
//         name = "main0";
//     }

//     gnBool foundFunction = false;
//     for (int i = 0; i < shaderLib.functionNames.count; i++) {
//         if (strcmp([shaderLib.functionNames objectAtIndex:0].UTF8String, name) == 0) {
//             foundFunction = true;
//         }
//     }

//     if (!foundFunction) {
//         gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
//            .message = gnCombineStrings(gnCreateString("Failed to find specified entry point "), name)
//         });
//         return GN_FAILED_TO_FIND_ENTRY_POINT;
//     }

//     NSString* functionName = [NSString stringWithCString:name encoding:NSUTF8StringEncoding];
//     module->shaderModule->function = [shaderLib newFunctionWithName:functionName];

//     [shaderLib release];

//     spvc_context_destroy(context);
//     return GN_SUCCESS;
// }

void destroyMetalShaderModule(gnShaderModule module) {
    free(module->shaderModule);
}
