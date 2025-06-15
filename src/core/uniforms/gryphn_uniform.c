#include "gryphn_uniform.h"
#include "gryphn_uniform_pool.h"
#include "core/output_device/gryphn_output_device.h"
#include "core/gryphn_platform_functions.h"

void gnUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo bufferInfo) {
    uniform->pool->device->deviceFunctions->_gnUpdateBufferUniform(uniform, &bufferInfo);
}

void gnUpdateImageUniform(gnUniform uniform, gnImageUniformInfo imageInfo) {
    uniform->pool->device->deviceFunctions->_gnUpdateImageUniform(uniform, &imageInfo);
}
