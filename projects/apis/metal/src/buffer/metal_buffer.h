#pragma once
#import <Metal/Metal.h>
#include "buffers/gryphn_buffer.h"
#include "output_device/gryphn_output_device.h"
#include "devices/metal_output_devices.h"

struct gnPlatformBuffer_t {
    id<MTLBuffer> buffer, stagingBuffer;
    bool useStagingBuffer;
};

gnReturnCode createMetalBuffer(gnBufferHandle buffer, gnDevice device, gnBufferInfo info);
void metalBufferData(gnBufferHandle buffer, size_t dataSize, void* data);
void* mapMetalBuffer(gnBufferHandle buffer);
void destroyMetalBuffer(gnBufferHandle buffer);
