#include "gryphn_buffer.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateBuffer(gnBufferHandle* buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    *buffer = malloc(sizeof(struct gnBuffer_t));
    (*buffer)->device = device;
    (*buffer)->info = info;
    return device->instance->callingLayer->deviceFunctions._gnCreateBuffer(*buffer, device, info);
}
void gnBufferData(gnBufferHandle buffer, size_t dataSize, void* data) {
    buffer->device->instance->callingLayer->deviceFunctions._gnBufferData(buffer, dataSize, data);
}
void gnBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, gnBufferMemory data) {
    buffer->device->instance->callingLayer->deviceFunctions._gnBufferSubData(buffer, offset, dataSize, data);
}
void* gnMapBuffer(gnBufferHandle buffer) {
    if (buffer->info.usage == GN_STATIC_DRAW) return NULL;
    return buffer->device->instance->callingLayer->deviceFunctions._gnMapBuffer(buffer);
}
void gnDestroyBuffer(gnBufferHandle buffer) {
    buffer->device->instance->callingLayer->deviceFunctions._gnDestroyBuffer(buffer);
}
