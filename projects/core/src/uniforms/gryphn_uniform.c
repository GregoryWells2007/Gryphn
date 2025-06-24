#include "gryphn_uniform.h"
#include "gryphn_uniform_pool.h"
#include "output_device/gryphn_output_device.h"

void gnUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo bufferInfo) {
    uniform->pool->device->deviceFunctions->_gnUpdateBufferUniform(uniform, &bufferInfo);
}

void gnUpdateImageUniform(gnUniform uniform, gnImageUniformInfo imageInfo) {
    uniform->pool->device->deviceFunctions->_gnUpdateImageUniform(uniform, &imageInfo);
}
