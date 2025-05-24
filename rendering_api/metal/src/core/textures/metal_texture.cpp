// #include "metal_texture.h"

// GN_EXPORT void gnTextureDataFn(gnTexture& texture, gnSize dataSize, const void* data) {
//     if (texture.texture == nullptr) texture.texture = new gnPlatformTexture();

//     MTL::Region region = MTL::Region(0, 0, 0, texture.textureExtent.x, texture.textureExtent.y, 1);
//     NS::UInteger bytesPerRow = texture.textureExtent.x;

//     if (texture.textureColorFormat == GN_RED)
//         bytesPerRow *= 1;
//     else if (texture.textureColorFormat == GN_RGB8)
//         bytesPerRow *= 3;
//     else if (texture.textureColorFormat == GN_RGBA8)
//         bytesPerRow *= 4;
//     else if (texture.textureColorFormat == GN_BGRA8)
//         bytesPerRow *= 4;
//     else if (texture.textureColorFormat == GN_DEPTH_STENCIL)
//         bytesPerRow *= 32; // this number is straight from my ass and may not work

//     texture.texture->texture->replaceRegion(region, 0, data, bytesPerRow);
// }
// GN_EXPORT void gnTextureCubeMapDataFn(gnTexture& texture, gnSize imageDataSize, void* face1, void* face2, void* face3, void* face4, void* face5, void* face6) {
//     NS::UInteger bytesPerRow = texture.textureExtent.x;

//     if (texture.textureColorFormat == GN_RED)
//         bytesPerRow *= 1;
//     else if (texture.textureColorFormat == GN_RGB8)
//         bytesPerRow *= 3;
//     else if (texture.textureColorFormat == GN_RGBA8)
//         bytesPerRow *= 4;
//     else if (texture.textureColorFormat == GN_BGRA8)
//         bytesPerRow *= 4;
//     else if (texture.textureColorFormat == GN_DEPTH_STENCIL)
//         bytesPerRow *= 32; // this number is straight from my ass and may not work

//     MTL::Region region = MTL::Region::Make2D(0, 0, texture.textureExtent.x, texture.textureExtent.y);
//     texture.texture->texture->replaceRegion(region, 0, 0, face1, bytesPerRow, imageDataSize);
//     texture.texture->texture->replaceRegion(region, 0, 1, face2, bytesPerRow, imageDataSize);
//     texture.texture->texture->replaceRegion(region, 0, 2, face3, bytesPerRow, imageDataSize);
//     texture.texture->texture->replaceRegion(region, 0, 3, face4, bytesPerRow, imageDataSize);
//     texture.texture->texture->replaceRegion(region, 0, 4, face5, bytesPerRow, imageDataSize);
//     texture.texture->texture->replaceRegion(region, 0, 5, face6, bytesPerRow, imageDataSize);
// }
// GN_EXPORT gnErrorCode gnCreateTextureFn(gnTexture* texture, const gnOutputDevice& outputDevice) {
//     if (texture->texture == nullptr) texture->texture = new gnPlatformTexture();

//     MTL::TextureDescriptor* textureDescriptor = MTL::TextureDescriptor::alloc()->init();
//     if (texture->textureType == GN_TEXTURE_CUBE_MAP) textureDescriptor->setTextureType(MTL::TextureType::TextureTypeCube);
//     if (texture->textureColorFormat == GN_RED)
//         textureDescriptor->setPixelFormat(MTL::PixelFormatR8Unorm);
//     else if (texture->textureColorFormat == GN_RGB8)
//         return gnReturnError(GN_UNSUPPORTED_COLOR_FORMAT, "GN_RGB8_UNSUPPORTED");
//     else if (texture->textureColorFormat == GN_RGBA8)
//         textureDescriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
//     else if (texture->textureColorFormat == GN_BGRA8)
//         textureDescriptor->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
//     else if (texture->textureColorFormat == GN_DEPTH_STENCIL)
//         textureDescriptor->setPixelFormat(MTL::PixelFormatDepth32Float_Stencil8);
//     else return gnReturnError(GN_UNKNOWN_COLOR_FORMAT, "unknown pixel format");

//     textureDescriptor->setWidth(texture->textureExtent.x);
//     textureDescriptor->setHeight(texture->textureExtent.y);
//     // textureDescriptor->setUsage(MTL::TextureUsageRenderTarget | MTL::TextureUsageShaderRead);

//     texture->texture->texture = outputDevice.physicalOutputDevice->physicalOutputDevice->device->newTexture(textureDescriptor);
//     MTL::SamplerDescriptor* samplerDescriptor = MTL::SamplerDescriptor::alloc()->init();
//         if (texture->minFilter == GN_FILTER_LINEAR)
//             samplerDescriptor->setMinFilter(MTL::SamplerMinMagFilter::SamplerMinMagFilterLinear);
//         else
//             samplerDescriptor->setMinFilter(MTL::SamplerMinMagFilter::SamplerMinMagFilterNearest);

//         if (texture->magFilter == GN_FILTER_LINEAR)
//             samplerDescriptor->setMagFilter(MTL::SamplerMinMagFilter::SamplerMinMagFilterLinear);
//         else
//             samplerDescriptor->setMagFilter(MTL::SamplerMinMagFilter::SamplerMinMagFilterNearest);
//     texture->texture->sampler = outputDevice.outputDevice->device->newSamplerState(samplerDescriptor);

//     textureDescriptor->release();
//     samplerDescriptor->release();
//     return GN_SUCCESS;
// }
// GN_EXPORT void gnDestroyTextureFn(gnTexture& texture) {
//     texture.texture->texture->release();
// }
