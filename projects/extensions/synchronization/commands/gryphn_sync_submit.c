#include "gryphn_sync_submit.h"
#include "core/src/output_device/gryphn_output_device.h"
#include "core/src/instance/gryphn_instance.h"

gnReturnCode gnSubmitSync(gnOutputDevice device, gnSubmitSyncInfo info) {
    return device->instance->callingLayer->syncFunctions._gnSubmitSync(device, info);
}
