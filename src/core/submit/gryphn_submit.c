#include "gryphn_submit.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnSubmit(struct gnOutputDevice_t* device, struct gnSubmitInfo_t info) {
    return device->deviceFunctions->_gnSubmit(device, info);
}
