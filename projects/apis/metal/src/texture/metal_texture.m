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
    return 0;
}

gnReturnCode createMetalTexture(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    texture->texture = malloc(sizeof(struct gnPlatformTexture_t));
    MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.sampleCount = mtlSampleCount(info.samples);
    textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    textureDescriptor.storageMode = MTLStorageModeShared;             // Most efficient for GPU-only textures
    textureDescriptor.depth = info.extent.depth;
    textureDescriptor.width = info.extent.width;
    textureDescriptor.height = info.extent.height;
    textureDescriptor.pixelFormat = mtlGryphnFormatToMetalFormat(info.format);

    if (textureDescriptor.sampleCount >= 2)
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
    MTLRegion region = {
        { 0, 0, 0 },
        {texture->info.extent.width, texture->info.extent.height, texture->info.extent.depth}
    };

    NSUInteger bytesPerRow = 4 * texture->info.extent.width; // TODO: fix this should not be set to 4
    [texture->texture->texture replaceRegion:region
                mipmapLevel:0
                  withBytes:pixelData
                bytesPerRow:bytesPerRow];
}

void metalDestroyTexture(gnTexture texture) {
    [texture->texture->texture release];
    free(texture->texture);
}
