#pragma once
#import <Metal/Metal.h>

struct gnPlatformBuffer_t {
    id<MTLBuffer> buffer, stagingBuffer;
    bool useStagingBuffer;
};
