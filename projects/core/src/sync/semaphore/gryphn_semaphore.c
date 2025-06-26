#include "gryphn_semaphore.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateSemaphore(gnSemaphore* semaphore, struct gnOutputDevice_t* device) {
    *semaphore = malloc(sizeof(struct gnSemaphore_t));
    (*semaphore)->device = device;
    return device->instance->callingLayer->deviceFunctions._gnCreateSemaphore((*semaphore), device);
}
void gnDestroySemaphore(struct gnSemaphore_t* semaphore) {
    semaphore->device->instance->callingLayer->deviceFunctions._gnDestroySemaphore(semaphore);
}
