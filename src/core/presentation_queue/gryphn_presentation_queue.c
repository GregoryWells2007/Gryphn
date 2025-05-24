#include "gryphn_presentation_queue.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreatePresentationQueue(gnPresentationQueue* presentationQueue, const gnOutputDevice* device, struct gnPresentationQueueInfo_t presentationInfo){
    return device->deviceFunctions->_gnCreatePresentationQueue(presentationQueue, device, presentationInfo);
}

// gnTexture* gnGetPresentationQueueImage(gnPresentationQueue& presentationQueue, int index) {
//     // if (index < gnListLength(presentationQueue.images))
//     return gnListGetPtr(presentationQueue.images, index); // zero fucking error checking in this file, im not doing that shit
// }
