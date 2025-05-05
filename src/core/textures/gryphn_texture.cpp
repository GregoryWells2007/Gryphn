#include "gryphn_texture.h"

void gnTextureSetType(gnTexture& texture, gnTextureType type) {
    texture.textureType = type;
}
void gnTextureSetFormat(gnTexture& texture, gnColorMode format) {
    texture.textureColorFormat = format;
}
void gnTextureSetExtent(gnTexture& texture, gnUInt2 extent) {
    texture.textureExtent = extent;
}
void gnTextureSetDataSize(gnTexture& texture, gnUInt dataSize) {
    texture.dataSize = dataSize;
}
void gnTextureSetMinFilter(gnTexture& texture, gnTextureFilter filter) {
    texture.minFilter = filter;
}
void gnTextureSetMagFilter(gnTexture& texture, gnTextureFilter filter) {
    texture.magFilter = filter;
}

// int gnTexture::currentTextureID = 0;

gnUInt gnGetTextureID(const gnTexture& texture) { return texture.TextureID; }
