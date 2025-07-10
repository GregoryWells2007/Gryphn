#include "gryphn_synced_presentation_queue.h"
#include "core/src/presentation_queue/gryphn_presentation_queue.h"

gnReturnCode gnPresentationQueueGetImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex) {
    return presentationQueue->outputDevice->instance->callingLayer->syncFunctions._gnPresentationQueueGetImageAsync(presentationQueue, timeout, semaphore, imageIndex);
}
