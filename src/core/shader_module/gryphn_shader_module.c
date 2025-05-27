#include <core/gryphn_platform_functions.h>
#include "gryphn_shader_module.h"

gnReturnCode gnCreateShaderModule(struct gnShaderModule_t* module, struct gnOutputDevice_t* device, struct gnShaderModuleInfo_t shaderModuleInfo) {
    module->device = device;
    return device->deviceFunctions->_gnCreateShaderModule(module, device, shaderModuleInfo);
}

void gnDestroyShaderModule(struct gnShaderModule_t* module) {
    module->device->deviceFunctions->_gnDestroyShaderModule(module);
}
