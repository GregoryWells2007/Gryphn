#include "gryphn_presentation_queue.h"

gnReturnCode gnCreatePresentationQueue(gnPresentationQueueHandle* presentationQueue, gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo){
    *presentationQueue = malloc(sizeof(struct gnPresentationQueue_t));
    (*presentationQueue)->outputDevice = device;
    (*presentationQueue)->info = presentationInfo;
    return device->instance->callingLayer->deviceFunctions._gnCreatePresentationQueue(*presentationQueue, device, presentationInfo);
}

// gnReturnCode gnPresentationQueueGetImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex) {
//     return presentationQueue->outputDevice->instance->callingLayer->deviceFunctions._gnPresentationQueueGetImageAsync(presentationQueue, timeout, semaphore, imageIndex);
// }
gnReturnCode gnPresentationQueueGetImage(gnPresentationQueueHandle presentationQueue, uint32_t* imageIndex) {
    return presentationQueue->outputDevice->instance->callingLayer->deviceFunctions._gnPresentationQueueGetImage(presentationQueue, imageIndex);
}
uint32_t gnGetPresentationQueueImageCount(gnPresentationQueueHandle presentationQueue) { return presentationQueue->imageCount; }
gnTextureHandle gnGetPresentationQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t index) {
    return presentationQueue->images[index];
}
void gnDestroyPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    presentationQueue->outputDevice->instance->callingLayer->deviceFunctions._gnDestroyPresentationQueue(presentationQueue);
    free(presentationQueue);
}
