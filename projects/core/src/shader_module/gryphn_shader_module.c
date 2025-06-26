#include "gryphn_shader_module.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateShaderModule(gnShaderModuleHandle* module, gnOutputDeviceHandle device, struct gnShaderModuleInfo shaderModuleInfo) {
    *module = malloc(sizeof(struct gnShaderModule_t));
    (*module)->device = device;
    (*module)->info = shaderModuleInfo;
    return device->instance->callingLayer->deviceFunctions._gnCreateShaderModule(*module, device, shaderModuleInfo);
}

void gnDestroyShaderModule(gnShaderModuleHandle module) {
    module->device->instance->callingLayer->deviceFunctions._gnDestroyShaderModule(module);
}
