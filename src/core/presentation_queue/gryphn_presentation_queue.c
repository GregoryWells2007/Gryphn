#include "gryphn_presentation_queue.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreatePresentationQueue(gnPresentationQueue* presentationQueue, struct gnOutputDevice_t* device, struct gnPresentationQueueInfo_t presentationInfo){
    presentationQueue->outputDevice = device;
    presentationQueue->info = presentationInfo;
    return device->deviceFunctions->_gnCreatePresentationQueue(presentationQueue, device, presentationInfo);
}

gnReturnCode gnPresentationQueueGetImage(gnPresentationQueue* presentationQueue, uint64_t timeout, struct gnSemaphore_t* semaphore, uint32_t* imageIndex) {
    return presentationQueue->outputDevice->deviceFunctions->_gnPresentationQueueGetImage(presentationQueue, timeout, semaphore, imageIndex);
}

void gnDestroyPresentationQueue(gnPresentationQueue *presentationQueue) {
    presentationQueue->outputDevice->deviceFunctions->_gnDestroyPresentationQueue(presentationQueue);
}
