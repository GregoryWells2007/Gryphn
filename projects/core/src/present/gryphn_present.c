#include "gryphn_present.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnPresent(gnDevice device, gnPresentInfo info) {
    return device->instance->callingLayer->deviceFunctions._gnPresent(device, info);
}
