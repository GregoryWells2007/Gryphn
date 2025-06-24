#include "gryphn_submit.h"
#include "gryphn_platform_functions.h"

gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info) {
    return device->deviceFunctions->_gnSubmit(device, info);
}
