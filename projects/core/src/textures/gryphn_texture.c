#include "gryphn_texture.h"
#include "gryphn_platform_functions.h"

gnReturnCode gnCreateTexture(gnTexture* texture, gnDevice device, const gnTextureInfo info) {
    *texture = malloc(sizeof(struct gnTexture_t));
    (*texture)->device = device;
    (*texture)->info = info;
    return device->deviceFunctions->_gnCreateTexture(*texture, device, info);
}

void gnTextureData(gnTextureHandle texture, void* pixelData) {
    texture->device->deviceFunctions->_gnTextureData(texture, pixelData);
}
void gnDestroyTexture(gnTexture texture) {
    texture->device->deviceFunctions->_gnDestroyTexture(texture);
}
