#include "gryphn_semaphore.h"
#include "gryphn_platform_functions.h"

gnReturnCode gnCreateSemaphore(gnSemaphore* semaphore, struct gnOutputDevice_t* device) {
    *semaphore = malloc(sizeof(struct gnSemaphore_t));
    (*semaphore)->device = device;
    return device->deviceFunctions->_gnCreateSemaphore((*semaphore), device);
}
void gnDestroySemaphore(struct gnSemaphore_t* semaphore) {
    semaphore->device->deviceFunctions->_gnDestroySemaphore(semaphore);
}
