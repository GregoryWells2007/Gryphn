#include "metal_shader_module.h"
#include "spirv_cross_c.h"
#include "instance/gryphn_debugger.h"
#include "devices/metal_output_devices.h"
#include "metal_shader_compiler.h"
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

gnReturnCode createMetalShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo) {
    module->shaderModule = malloc(sizeof(gnPlatformShaderModule));

    mtlCompilerInfo info = {
        .code = shaderModuleInfo.code,
        .wordCount = shaderModuleInfo.size / 4,
        .entryPoint = shaderModuleInfo.entryPoint.value,
        .stage = (shaderModuleInfo.stage == GN_FRAGMENT_SHADER_MODULE) ? mtlFragment : mtlVertex
    };
    if ((device->outputDevice->device.argumentBuffersSupport == MTLArgumentBuffersTier2)) {
        info.mslMajorVersion = 3;
        info.minorVersion = 0;
        info.useArgumentBuffers = true;
    } else {
        info.mslMajorVersion = 1;
        info.minorVersion = 0;
        info.useArgumentBuffers = false;
    }
    module->shaderModule->compiler = mtlCreateCompiler(&info);
    return GN_SUCCESS;
}

void destroyMetalShaderModule(gnShaderModule module) {
    free(module->shaderModule);
}
