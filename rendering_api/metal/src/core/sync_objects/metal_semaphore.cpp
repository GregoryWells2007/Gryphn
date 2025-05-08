#include <core/sync_objects/gryphn_sync_semaphore.h>
#include "metal_semaphore.h"

GN_EXPORT gnReturnCode gnCreateSyncSemaphoreFn(gnSyncSemaphore* semaphore, const gnOutputDevice& device) {
    semaphore->semaphore = new gnPlatformSyncSemaphore();
    semaphore->semaphore->semaphore = dispatch_semaphore_create(0);
    // semaphore->semaphore->semaphore = device.outputDevice->device->newFence();
    return GN_SUCCESS;
}
GN_EXPORT void gnDestroySyncSemaphoreFn(const gnSyncSemaphore& semaphore) {
    // semaphore.semaphore->semaphore->release();
}
