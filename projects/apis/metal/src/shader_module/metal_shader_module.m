#include "metal_shader_module.h"
#include "spirv_cross_c.h"
#include "instance/gryphn_debugger.h"
#include "devices/metal_output_devices.h"
#include "metal_shader_compiler.h"
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

gnReturnCode createMetalShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo) {
    module->shaderModule = malloc(sizeof(gnPlatformShaderModule));

    mtlShaderOptions options = {
        .useArgumentBuffers = (device->outputDevice->device.argumentBuffersSupport == MTLArgumentBuffersTier2),
        .stage = vertex,
        .entryPoint = shaderModuleInfo.entryPoint.value
    };
    if (shaderModuleInfo.stage == GN_FRAGMENT_SHADER_MODULE) options.stage = fragment;

    const char* res = mtlCompileShader(shaderModuleInfo.code, shaderModuleInfo.size / 4, &options);
    if (res == NULL) return GN_FAILED_TO_CONVERT_SHADER_CODE;

    NSError* error = nil;
    MTLCompileOptions* mtloptions = nil;
    NSString* sourceCode = [NSString stringWithCString:res encoding:NSUTF8StringEncoding];
    id<MTLLibrary> shaderLib = [device->outputDevice->device    newLibraryWithSource:sourceCode options:mtloptions error:&error];
    if (!shaderLib) {
        const char* errorString = error.localizedDescription.UTF8String;
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCombineStrings(gnCreateString("Failed to compile metal library "), errorString)
        });
        return GN_FAILED_TO_CREATE_SHADER_MODULE;
    }

    const char* name = shaderModuleInfo.entryPoint.value;
    if (strcmp(name, "main") == 0)  name = "main0";

    gnBool foundFunction = false;
    for (int i = 0; i < shaderLib.functionNames.count; i++) {
        if (strcmp([shaderLib.functionNames objectAtIndex:0].UTF8String, name) == 0) {
            foundFunction = true;
            break;
        }
    }
    if (!foundFunction) return GN_FAILED_TO_FIND_ENTRY_POINT;

    NSString* functionName = [NSString stringWithCString:name encoding:NSUTF8StringEncoding];
    module->shaderModule->function = [shaderLib newFunctionWithName:functionName];

    [shaderLib release];
    free((void*)res);
    return GN_SUCCESS;
}

void destroyMetalShaderModule(gnShaderModule module) {
    free(module->shaderModule);
}
