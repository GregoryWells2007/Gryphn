#include "gryphn_uniform.h"
#include "gryphn_uniform_pool.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

void gnUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo bufferInfo) {
    uniform->pool->device->instance->callingLayer->deviceFunctions._gnUpdateBufferUniform(uniform, &bufferInfo);
}

void gnUpdateStorageUniform(gnUniform uniform, gnStorageUniformInfo storageInfo) {
    uniform->pool->device->instance->callingLayer->deviceFunctions._gnUpdateStorageUniform(uniform, &storageInfo);
}

void gnUpdateImageUniform(gnUniform uniform, gnImageUniformInfo imageInfo) {
    uniform->pool->device->instance->callingLayer->deviceFunctions._gnUpdateImageUniform(uniform, &imageInfo);
}
