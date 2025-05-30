#include "gryphn_semaphore.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateSemaphore(struct gnSemaphore_t* semaphore, struct gnOutputDevice_t* device) {
    semaphore->device = device;
    return device->deviceFunctions->_gnCreateSemaphore(semaphore, device);
}
void gnDestroySemaphore(struct gnSemaphore_t* semaphore) {
    semaphore->device->deviceFunctions->_gnDestroySemaphore(semaphore);
}
