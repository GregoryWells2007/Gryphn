#include <core/buffers/gryphn_buffer.h>
#include <core/devices/metal_output_devices.h>
#include "metal_buffer.h"

GN_EXPORT gnErrorCode gnCreateBufferFn(gnBuffer* buffer, const gnOutputDevice& outputDevice) {
    if (!buffer->buffer) buffer->buffer = new gnPlatformBuffer();

    buffer->buffer->buffer = outputDevice.outputDevice->device->newBuffer(buffer->size, MTL::ResourceStorageModeShared);

    return GN_SUCCESS;
}

GN_EXPORT void gnBufferDataFn(gnBuffer& buffer, void* data) {
    memcpy(buffer.buffer->buffer->contents(), data, buffer.size);
}

GN_EXPORT void gnBufferSubDataFn(gnBuffer& buffer, gnSize offset, gnSize size, void* data) {
    memcpy((char*)buffer.buffer->buffer->contents() + offset, data, size);
}
GN_EXPORT void gnBufferClearDataFn(gnBuffer& buffer) {
    memcpy(buffer.buffer->buffer->contents(), 0, buffer.size);
}

GN_EXPORT void gnBufferMapDataFn(gnBuffer& buffer, void** data) {
    *data = buffer.buffer->buffer->contents();
}

GN_EXPORT void gnDestroyBufferFn(gnBuffer& buffer) {
    buffer.buffer->buffer->release();
}
