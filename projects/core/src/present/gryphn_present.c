#include "gryphn_platform_functions.h"
#include "gryphn_present.h"

gnReturnCode gnPresent(gnOutputDeviceHandle device, gnPresentInfo info) {
    return device->deviceFunctions->_gnPresent(device, info);
}
