#include "metal_semaphore.h"
#include "devices/metal_output_devices.h"

gnReturnCode gnCreateSemaphoreFn(gnSemaphore semaphore, gnOutputDevice device) {
    semaphore->semaphore = malloc(sizeof(gnPlatformSemaphore));
    semaphore->semaphore->event = [device->outputDevice->device newEvent];

    return GN_SUCCESS;
}
void gnDestroySemaphoreFn(gnSemaphore semaphore) {
    [semaphore->semaphore->event release];
    free(semaphore->semaphore);
}
