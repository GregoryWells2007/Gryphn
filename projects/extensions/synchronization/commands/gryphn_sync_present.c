#include "gryphn_sync_present.h"
#include "core/src/output_device/gryphn_output_device.h"
#include "core/src/instance/gryphn_instance.h"

gnReturnCode gnPresentSync(gnOutputDeviceHandle device, gnPresentSyncInfo info) {
    return device->instance->callingLayer->syncFunctions._gnPresentSync(device, info);
}
