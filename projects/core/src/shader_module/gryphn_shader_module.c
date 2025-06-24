#include "gryphn_shader_module.h"
#include "output_device/gryphn_output_device.h"

gnReturnCode gnCreateShaderModule(gnShaderModuleHandle* module, gnOutputDeviceHandle device, struct gnShaderModuleInfo shaderModuleInfo) {
    *module = malloc(sizeof(struct gnShaderModule_t));
    (*module)->device = device;
    (*module)->info = shaderModuleInfo;
    return device->deviceFunctions->_gnCreateShaderModule(*module, device, shaderModuleInfo);
}

void gnDestroyShaderModule(gnShaderModuleHandle module) {
    module->device->deviceFunctions->_gnDestroyShaderModule(module);
}
