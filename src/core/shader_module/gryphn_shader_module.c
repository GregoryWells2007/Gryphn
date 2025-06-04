#include <core/gryphn_platform_functions.h>
#include "gryphn_shader_module.h"

gnReturnCode gnCreateShaderModule(gnShaderModuleHandle* module, gnOutputDeviceHandle device, struct gnShaderModuleInfo_t shaderModuleInfo) {
    *module = malloc(sizeof(struct gnShaderModule_t));
    (*module)->device = device;
    (*module)->info = shaderModuleInfo;
    return device->deviceFunctions->_gnCreateShaderModule(*module, device, shaderModuleInfo);
}

void gnDestroyShaderModule(gnShaderModuleHandle module) {
    module->device->deviceFunctions->_gnDestroyShaderModule(module);
}
