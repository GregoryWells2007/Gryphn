#include "metal_semaphore.h"
#include "core/devices/metal_output_devices.h"

gnReturnCode gnCreateSemaphoreFn(struct gnSemaphore_t* semaphore, struct gnOutputDevice_t* device) {
    semaphore->semaphore = malloc(sizeof(gnPlatformSemaphore));
    semaphore->semaphore->event = [device->outputDevice->device newEvent];

    return GN_SUCCESS;
}
void gnDestroySemaphoreFn(struct gnSemaphore_t* semaphore) {
    [semaphore->semaphore->event release];
    free(semaphore->semaphore);
}
