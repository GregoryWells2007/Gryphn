#include "core/gryphn_platform_functions.h"
#include "gryphn_present.h"

gnReturnCode gnPresent(struct gnOutputDevice_t* device, struct gnPresentInfo_t info) {
    return device->deviceFunctions->_gnPresent(device, info);
}
