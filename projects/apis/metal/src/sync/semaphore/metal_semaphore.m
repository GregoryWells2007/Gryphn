#include "metal_semaphore.h"
#include "devices/metal_output_devices.h"

gnReturnCode createMetalSemaphore(gnSemaphore semaphore, gnOutputDevice device) {
    semaphore->semaphore = malloc(sizeof(gnPlatformSemaphore));
    semaphore->semaphore->event = [device->outputDevice->device newEvent];
    semaphore->semaphore->currentValue = 0;
    return GN_SUCCESS;
}
void destroyMetalSemaphore(gnSemaphore semaphore) {
    [semaphore->semaphore->event release];
    free(semaphore->semaphore);
}

void mtlSignalSemaphore(gnSemaphore semaphore, id<MTLCommandBuffer> cmdBuf) {
    uint64_t val = atomic_fetch_add_explicit(&semaphore->semaphore->currentValue, 1, memory_order_acq_rel) + 1;
    [cmdBuf encodeSignalEvent:semaphore->semaphore->event value:val];
}

void mtlWaitSemaphore(gnSemaphore semaphore, id<MTLCommandBuffer> cmdBuf) {
    uint64_t val = atomic_load_explicit(&semaphore->semaphore->currentValue, memory_order_acquire);
    [cmdBuf encodeWaitForEvent:semaphore->semaphore->event value:val];
}
