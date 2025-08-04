#include "metal_texture.h"
#include "surface/metal_surface.h"
#include "devices/metal_output_devices.h"

NSUInteger mtlSampleCount(gnMultisampleCountFlags flags) {
    if ((flags & GN_SAMPLE_BIT_64) == GN_SAMPLE_BIT_64) { return 64; }
    if ((flags & GN_SAMPLE_BIT_32) == GN_SAMPLE_BIT_32) { return 32; }
    if ((flags & GN_SAMPLE_BIT_16) == GN_SAMPLE_BIT_16) { return 16; }
    if ((flags & GN_SAMPLE_BIT_8) == GN_SAMPLE_BIT_8) { return 8; }
    if ((flags & GN_SAMPLE_BIT_4) == GN_SAMPLE_BIT_4) { return 4; }
    if ((flags & GN_SAMPLE_BIT_2) == GN_SAMPLE_BIT_2) { return 2; }
    if ((flags & GN_SAMPLE_BIT_1) == GN_SAMPLE_BIT_1) { return 1; }
    return 1;
}

gnReturnCode createMetalTexture(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    texture->texture = malloc(sizeof(struct gnPlatformTexture_t));
    MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.sampleCount = mtlSampleCount(info.samples);
    textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    textureDescriptor.storageMode = MTLStorageModePrivate;
    textureDescriptor.depth = info.extent.depth;
    textureDescriptor.width = info.extent.width;
    textureDescriptor.height = info.extent.height;
    textureDescriptor.pixelFormat = mtlGryphnFormatToMetalFormat(info.format);

    if (textureDescriptor.sampleCount > 1)
        textureDescriptor.textureType = MTLTextureType2DMultisample;
    else
        textureDescriptor.textureType = MTLTextureType2D;

    MTLSamplerDescriptor *samplerDesc = [[MTLSamplerDescriptor alloc] init];
    samplerDesc.minFilter = (info.minFilter == GN_FILTER_NEAREST) ? MTLSamplerMinMagFilterNearest : MTLSamplerMinMagFilterLinear;
    samplerDesc.magFilter = (info.magFilter == GN_FILTER_NEAREST) ? MTLSamplerMinMagFilterNearest : MTLSamplerMinMagFilterLinear;;
    samplerDesc.mipFilter = MTLSamplerMipFilterNotMipmapped;
    samplerDesc.sAddressMode = MTLSamplerAddressModeClampToEdge;
    samplerDesc.tAddressMode = MTLSamplerAddressModeClampToEdge;
    samplerDesc.supportArgumentBuffers = true;
    texture->texture->sampler = [device->outputDevice->device newSamplerStateWithDescriptor:samplerDesc];
    texture->texture->texture = [device->outputDevice->device newTextureWithDescriptor:textureDescriptor];

    [textureDescriptor release];
    [samplerDesc release];
    return GN_SUCCESS;
}

void metalTextureData(gnTextureHandle texture, void* pixelData) {
    NSUInteger fullBytesPerRow = 4 * texture->info.extent.width;
    id<MTLBuffer> stagingBuffer = [texture->device->outputDevice->stagingBuffer retain];
    NSUInteger maxRowsPerChunk = stagingBuffer.length / fullBytesPerRow;
    if (maxRowsPerChunk == 0) maxRowsPerChunk = 1;
    NSUInteger yOffset = 0;
    while (yOffset < texture->info.extent.height) {
        NSUInteger rowsThisChunk = MIN(maxRowsPerChunk, texture->info.extent.height - yOffset);
        NSUInteger chunkSize = rowsThisChunk * fullBytesPerRow;

        // Copy chunk of pixel data into staging buffer
        memcpy(stagingBuffer.contents, (uint8_t*)pixelData + yOffset * fullBytesPerRow, chunkSize);

        id<MTLCommandBuffer> cmd = [texture->device->outputDevice->transferQueue commandBuffer];
        id<MTLBlitCommandEncoder> blitEncoder = [cmd blitCommandEncoder];

        MTLOrigin origin = { 0, (NSUInteger)yOffset, 0 };
        MTLSize size = { (NSUInteger)texture->info.extent.width, (NSUInteger)rowsThisChunk, 1 };

        [blitEncoder copyFromBuffer:stagingBuffer
                      sourceOffset:0
                 sourceBytesPerRow:fullBytesPerRow
               sourceBytesPerImage:chunkSize
                        sourceSize:size
                         toTexture:texture->texture->texture
                  destinationSlice:0
                  destinationLevel:0
                 destinationOrigin:origin];

        [blitEncoder endEncoding];
        [cmd commit];

        yOffset += rowsThisChunk;
    }

    [stagingBuffer release];

    // NSUInteger chunkSize = texture->device->outputDevice->stagingBuffer.length;
    // NSUInteger totalSize = texture->info.extent.width * texture->info.extent.height * texture->info.extent.depth * 4;
    // NSUInteger offset = 0;

    // while (offset < totalSize) {
    //     NSUInteger sizeToCopy = MIN(chunkSize, totalSize - offset);
    //     memcpy(texture->device->outputDevice->stagingBuffer.contents, (char*)pixelData + offset, sizeToCopy);

    //     id<MTLCommandBuffer> transfer = [texture->device->outputDevice->transferQueue commandBuffer];
    //     id<MTLBlitCommandEncoder> blit = [transfer blitCommandEncoder];

    //     [blit copyFromBuffer:texture->device->outputDevice->stagingBuffer
    //                   sourceOffset:0
    //                       toTexture:gpuBuffer
    //              destinationOffset:offset
    //                           size:sizeToCopy];

    //     [blit endEncoding];
    //     [transfer commit];

    //     offset += sizeToCopy;
    // }

}

void metalDestroyTexture(gnTexture texture) {
    [texture->texture->texture release];
    free(texture->texture);
}
