#include "gryphn_submit.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info) {
    return device->deviceFunctions->_gnSubmit(device, info);
}
