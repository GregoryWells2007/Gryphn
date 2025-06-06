#include "gryphn_presentation_queue.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreatePresentationQueue(gnPresentationQueueHandle* presentationQueue, gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo){
    *presentationQueue = malloc(sizeof(struct gnPresentationQueue_t));
    (*presentationQueue)->outputDevice = device;
    (*presentationQueue)->info = presentationInfo;
    return device->deviceFunctions->_gnCreatePresentationQueue(*presentationQueue, device, presentationInfo);
}

gnReturnCode gnPresentationQueueGetImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex) {
    return presentationQueue->outputDevice->deviceFunctions->_gnPresentationQueueGetImage(presentationQueue, timeout, semaphore, imageIndex);
}
uint32_t gnGetPresentationQueueImageCount(gnPresentationQueueHandle presentationQueue) { return presentationQueue->imageCount; }
gnTextureHandle gnGetPresentationQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t index) {
    return presentationQueue->images[index];
}
void gnDestroyPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    presentationQueue->outputDevice->deviceFunctions->_gnDestroyPresentationQueue(presentationQueue);
    free(presentationQueue);
}
