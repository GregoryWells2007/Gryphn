#include "queue_functions.h"
#include "loader_utils.h"
#include "core/src/output_device/gryphn_physical_output_device.h"
#include "core/src/output_device/gryphn_output_device.h"
#include <core/src/instance/gryphn_debugger.h>
#include <core/src/instance/gryphn_instance.h>
#include "core/src/submit/gryphn_submit.h"
#include "core/src/present/gryphn_present.h"
#include "extensions/synchronization/commands/gryphn_sync_submit.h"
#include "extensions/synchronization/commands/gryphn_sync_present.h"

gnReturnCode checkGetPhysicalDeviceQueueProperties(gnPhysicalOutputDeviceHandle device, uint32_t queueCount, gnQueueFamilyProperties* queues) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnGetPhysicalDeviceQueueProperties, queueFunctions, device, queueCount, queues);
}
void checkGetDeviceQueue(gnOutputDevice device, uint32_t queueFamily, uint32_t queueIndex, gnQueue* queue) {
    CHECK_VOID_FUNCTION(device->instance, _gnGetDeviceQueue, queueFunctions, device, queueFamily, queueIndex, queue);
}

gnReturnCode checkQueueSubmit(gnOutputDevice device, gnQueue queue, gnSubmitInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnQueueSubmit, queueFunctions, device, queue, info);
}
gnReturnCode checkQueueSubmitSync(gnOutputDevice device, gnQueue queue, gnSubmitSyncInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnQueueSubmitSync, queueFunctions, device, queue, info);
}

gnReturnCode checkQueuePresent(gnDevice device, gnQueue queue, gnPresentInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnQueuePresent, queueFunctions, device, queue, info);

}
gnReturnCode checkQueuePresentSync(gnDevice device, gnQueue queue, gnPresentSyncInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnQueuePresentSync, queueFunctions, device, queue, info);
}
