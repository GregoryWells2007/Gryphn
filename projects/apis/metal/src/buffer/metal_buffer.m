#include "metal_buffer.h"

gnReturnCode createMetalBuffer(gnBufferHandle buffer, gnDevice device, gnBufferInfo info) {
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
void metalBufferData(gnBufferHandle buffer, size_t dataSize, void* data) {
    metalBufferSubData(buffer, 0, dataSize, data);
}
void metalBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, gnBufferMemory data) {
    if (buffer->buffer->useStagingBuffer) {
        memcpy((char*)buffer->buffer->stagingBuffer.contents + offset, data, dataSize);
        id<MTLCommandBuffer> commandBuffer = [buffer->device->outputDevice->transferQueue commandBuffer];
        id<MTLBlitCommandEncoder> encoder = [commandBuffer blitCommandEncoder];
        [encoder copyFromBuffer:buffer->buffer->stagingBuffer sourceOffset:0 toBuffer:buffer->buffer->buffer destinationOffset:0 size:dataSize];
        [encoder endEncoding];
        [commandBuffer commit];
        [commandBuffer waitUntilCompleted];
    } else
        memcpy((char*)buffer->buffer->buffer.contents + offset, data, dataSize);
}
void* mapMetalBuffer(gnBufferHandle buffer) {
    return buffer->buffer->buffer.contents;
}
void destroyMetalBuffer(gnBufferHandle buffer) {
    if (buffer->buffer->useStagingBuffer)
        [buffer->buffer->stagingBuffer release];
    [buffer->buffer->buffer release];
    free(buffer->buffer);
}
