#include "gryphn_texture.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateTexture(gnTexture* texture, gnDevice device, const gnTextureInfo info) {
    *texture = malloc(sizeof(struct gnTexture_t));
    (*texture)->device = device;
    return device->deviceFunctions->_gnCreateTexture(*texture, device, info);
}
