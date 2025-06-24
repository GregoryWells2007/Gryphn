#include "gryphn_submit.h"
#include "output_device/gryphn_output_device.h"

gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info) {
    return device->deviceFunctions->_gnSubmit(device, info);
}
