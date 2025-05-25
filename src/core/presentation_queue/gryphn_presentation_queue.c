#include "gryphn_presentation_queue.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreatePresentationQueue(gnPresentationQueue* presentationQueue, struct gnOutputDevice_t* device, struct gnPresentationQueueInfo_t presentationInfo){
    presentationQueue->outputDevice = device;
    return device->deviceFunctions->_gnCreatePresentationQueue(presentationQueue, device, presentationInfo);
}

void gnDestroyPresentationQueue(gnPresentationQueue *presentationQueue) {
    presentationQueue->outputDevice->deviceFunctions->_gnDestroyPresentationQueue(presentationQueue);
}
