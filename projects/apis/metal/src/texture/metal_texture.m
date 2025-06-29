#include "metal_texture.h"
#include "surface/metal_surface.h"
#include "devices/metal_output_devices.h"

gnReturnCode createMetalTexture(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    texture->texture = malloc(sizeof(struct gnPlatformTexture_t));
    MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.pixelFormat = mtlGryphnFormatToMetalFormat(info.format);
    textureDescriptor.width = info.width;
    textureDescriptor.height = info.height;
    texture->texture->texture = [device->outputDevice->device newTextureWithDescriptor:textureDescriptor];
    [textureDescriptor release];
    return GN_SUCCESS;
}

void metalTextureData(gnTextureHandle texture, void* pixelData) {
    MTLRegion region = {
        { 0, 0, 0 },
        {texture->info.width, texture->info.height, 1}
    };

    NSUInteger bytesPerRow = 4 * texture->info.width; // TODO: fix this should not be set to 4
    [texture->texture->texture replaceRegion:region
                mipmapLevel:0
                  withBytes:pixelData
                bytesPerRow:bytesPerRow];

}

void metalDestroyTexture(gnTexture texture) {
    [texture->texture->texture release];
    free(texture->texture);
}
