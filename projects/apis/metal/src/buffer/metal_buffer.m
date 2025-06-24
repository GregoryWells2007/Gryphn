#include "metal_buffer.h"
#include "core/buffers/gryphn_buffer.h"
#include "core/output_device/gryphn_output_device.h"
#include "core/devices/metal_output_devices.h"

gnReturnCode gnCreateBufferFn(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    buffer->buffer = malloc(sizeof(struct gnPlatformBuffer_t));
    MTLResourceOptions option;
    buffer->buffer->useStagingBuffer = (info.usage == GN_DYNAMIC_DRAW) ? NO : YES;
    if (info.usage == GN_DYNAMIC_DRAW)
        option = MTLResourceStorageModeShared;
    else {
        option = MTLResourceStorageModePrivate;
        buffer->buffer->stagingBuffer = [device->outputDevice->device newBufferWithLength:info.size options:MTLResourceStorageModeShared];
    }
    buffer->buffer->buffer = [device->outputDevice->device newBufferWithLength:info.size options:option];
    return GN_SUCCESS;
}
void gnBufferDataFn(gnBufferHandle buffer, size_t dataSize, void* data) {
    void* bufferData;
    if (buffer->buffer->useStagingBuffer) {
        memcpy(buffer->buffer->stagingBuffer.contents, data, dataSize);
        id<MTLCommandBuffer> commandBuffer = [buffer->device->outputDevice->transferQueue commandBuffer];
        id<MTLBlitCommandEncoder> encoder = [commandBuffer blitCommandEncoder];
        [encoder copyFromBuffer:buffer->buffer->stagingBuffer sourceOffset:0 toBuffer:buffer->buffer->buffer destinationOffset:0 size:dataSize];
        [encoder endEncoding];
        [commandBuffer commit];
        [commandBuffer waitUntilCompleted];
    } else
        memcpy(buffer->buffer->buffer.contents, data, dataSize);
}
void* gnMapBufferFn(gnBufferHandle buffer) {
    return buffer->buffer->buffer.contents;
}
void gnDestroyBufferFn(gnBufferHandle buffer) {
    if (buffer->buffer->useStagingBuffer)
        [buffer->buffer->stagingBuffer release];
    [buffer->buffer->buffer release];
    free(buffer->buffer);
}
