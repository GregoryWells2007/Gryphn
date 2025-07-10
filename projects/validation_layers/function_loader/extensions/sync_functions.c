#include "sync_functions.h"
#include "loader_utils.h"
#include "core/src/presentation_queue/gryphn_presentation_queue.h"
#include <core/src/debugger/gryphn_debugger.h>
#include "synchronization/semaphore/gryphn_semaphore.h"
#include "synchronization/fence/gryphn_fence.h"
#include "synchronization/commands/gryphn_sync_submit.h"

gnReturnCode checkPresentationQueueGetImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex) {
    CHECK_FUNCTION_WITH_RETURN_CODE(presentationQueue->outputDevice->instance, _gnPresentationQueueGetImageAsync, syncFunctions, presentationQueue, timeout, semaphore, imageIndex);
}

gnReturnCode checkCreateSemaphore(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateSemaphore, syncFunctions, semaphore, device);
}
void checkDestroySemaphore(gnSemaphoreHandle semaphore) {
    CHECK_VOID_FUNCTION(semaphore->device->instance, _gnDestroySemaphore, syncFunctions, semaphore);
}

gnReturnCode checkCreateFence(gnFenceHandle fence, gnOutputDeviceHandle device) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateFence, syncFunctions, fence, device);
}
void checkWaitForFence(gnFenceHandle fence, uint64_t timeout) {
    CHECK_VOID_FUNCTION(fence->device->instance, _gnWaitForFence, syncFunctions, fence, timeout);
}
void checkResetFence(gnFenceHandle fence) {
    CHECK_VOID_FUNCTION(fence->device->instance, _gnResetFence, syncFunctions, fence);
}
void checkDestroyFence(gnFenceHandle fence) {
    CHECK_VOID_FUNCTION(fence->device->instance, _gnDestroyFence, syncFunctions, fence);
}

gnReturnCode checkSubmitSync(gnOutputDevice device, gnSubmitSyncInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnSubmitSync, syncFunctions, device, info);
}
