#include "gryphn_texture.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateTexture(gnTexture* texture, gnDevice device, const gnTextureInfo info) {
    *texture = malloc(sizeof(struct gnTexture_t));
    (*texture)->device = device;
    (*texture)->info = info;

    return device->instance->callingLayer->deviceFunctions._gnCreateTexture(*texture, device, info);
}

void gnTextureData(gnTextureHandle texture, void* pixelData) {
    texture->device->instance->callingLayer->deviceFunctions._gnTextureData(texture, pixelData);
}
void gnDestroyTexture(gnTexture texture) {
    if (texture == GN_NULL_HANDLE) return;
    texture->device->instance->callingLayer->deviceFunctions._gnDestroyTexture(texture);
}
