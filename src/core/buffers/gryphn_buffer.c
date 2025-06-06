#include "gryphn_buffer.h"
#include "core/output_device/gryphn_output_device.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateBuffer(gnBufferHandle* buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    *buffer = malloc(sizeof(struct gnBuffer_t));
    (*buffer)->device = device;
    return device->deviceFunctions->_gnCreateBuffer(*buffer, device, info);
}
void gnBufferData(gnBufferHandle buffer, size_t dataSize, void* data) {
    buffer->device->deviceFunctions->_gnBufferData(buffer, dataSize, data);
}
void gnDestroyBuffer(gnBufferHandle buffer) {
    buffer->device->deviceFunctions->_gnDestroyBuffer(buffer);
}
