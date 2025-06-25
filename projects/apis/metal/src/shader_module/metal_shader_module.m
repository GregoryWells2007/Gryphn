#include "metal_shader_module.h"
#include "spirv_cross_c.h"
#include "debugger/gryphn_debugger.h"
#include "devices/metal_output_devices.h"
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

void mtlSpirVErrorCallback(void *userdata, const char *error) {
    struct gnDebugger_t* debugger = (struct gnDebugger_t*)userdata;
    gnDebuggerSetErrorMessage(debugger, (gnMessageData){
        .message = gnCreateString(error)
    });
}

gnReturnCode gnCreateShaderModuleFn(gnShaderModule module, gnOutputDevice device, gnShaderModuleInfo shaderModuleInfo) {
    module->shaderModule = malloc(sizeof(struct gnPlatformShaderModule_t));

    spvc_context context = NULL;
    spvc_parsed_ir ir = NULL;
    spvc_compiler compiler = NULL;
    const char *result = NULL;
    spvc_resources resources = NULL;
    const spvc_reflected_resource *list = NULL;
    spvc_compiler_options options = NULL;
    size_t count;

    spvc_context_create(&context);
    spvc_context_set_error_callback(context, mtlSpirVErrorCallback, module->device->instance->debugger);
    spvc_context_parse_spirv(context, shaderModuleInfo.code, shaderModuleInfo.size / 4, &ir);
    spvc_context_create_compiler(context, SPVC_BACKEND_MSL, ir, SPVC_CAPTURE_MODE_COPY, &compiler);

    spvc_compiler_create_shader_resources(compiler, &resources);
    spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_UNIFORM_BUFFER, &list, &count);

    for (int i = 0; i < count; i++){
        uint32_t set = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationDescriptorSet),
                 binding = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationBinding);

        if ((shaderModuleInfo.stage & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE)
            binding += 1;
        spvc_compiler_unset_decoration(compiler, list[i].id, SpvDecorationBinding);
        spvc_compiler_set_decoration(compiler, list[i].id, SpvDecorationBinding, binding);
    }


    spvc_compiler_create_compiler_options(compiler, &options);
    spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_MSL_VERSION, 200);
    spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_MSL_ENABLE_DECORATION_BINDING, true);
    spvc_compiler_install_compiler_options(compiler, options);

    SpvExecutionModel executionModel = SpvExecutionModelVertex;
    if (shaderModuleInfo.stage == GN_FRAGMENT_SHADER_MODULE) executionModel = SpvExecutionModelFragment;

    spvc_compiler_set_entry_point(compiler, shaderModuleInfo.entryPoint.value, executionModel);
    spvc_result res = spvc_compiler_compile(compiler, &result);
    if (res != SPVC_SUCCESS)
        return GN_FAILED_TO_CONVERT_SHADER_CODE;

    NSError* error = nil;
    MTLCompileOptions* mtloptions = nil;
    NSString* sourceCode = [NSString stringWithCString:result encoding:NSUTF8StringEncoding];
    id<MTLLibrary> shaderLib = [device->outputDevice->device    newLibraryWithSource:sourceCode options:mtloptions error:&error];
    if (!shaderLib) {
        const char* errorString = error.localizedDescription.UTF8String;
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCombineStrings(gnCreateString("Failed to compile metal library "), errorString)
        });
        return GN_FAILED_TO_CREATE_SHADER_MODULE;
    }

    const char* name = shaderModuleInfo.entryPoint.value;
    if (strcmp(name, "main") == 0) {
        name = "main0";
    }

    gnBool foundFunction = false;
    for (int i = 0; i < shaderLib.functionNames.count; i++) {
        if (strcmp([shaderLib.functionNames objectAtIndex:0].UTF8String, name) == 0) {
            foundFunction = true;
        }
    }

    if (!foundFunction) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
           .message = gnCombineStrings(gnCreateString("Failed to find specified entry point "), name)
        });
        return GN_FAILED_TO_FIND_ENTRY_POINT;
    }

    NSString* functionName = [NSString stringWithCString:name encoding:NSUTF8StringEncoding];
    module->shaderModule->function = [shaderLib newFunctionWithName:functionName];

    [shaderLib release];

    spvc_context_destroy(context);
    return GN_SUCCESS;
}

void gnDestroyShaderModuleFn(struct gnShaderModule_t* module) {
    free(module->shaderModule);
}
