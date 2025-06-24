#include "gryphn_present.h"
#include "output_device/gryphn_output_device.h"

gnReturnCode gnPresent(gnDevice device, gnPresentInfo info) {
    return device->deviceFunctions->_gnPresent(device, info);
}
