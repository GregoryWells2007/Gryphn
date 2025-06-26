#include "gryphn_submit.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info) {
    return device->instance->callingLayer->deviceFunctions._gnSubmit(device, info);
}
