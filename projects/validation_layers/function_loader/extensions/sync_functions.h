#include <loader/src/gryphn_loader.h>

gnReturnCode checkPresentationQueueGetImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex);
gnReturnCode checkCreateSemaphore(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device);
void checkDestroySemaphore(gnSemaphoreHandle semaphore);
gnReturnCode checkCreateFence(gnFenceHandle fence, gnOutputDeviceHandle device);
void checkWaitForFence(gnFenceHandle fence, uint64_t timeout);
void checkResetFence(gnFenceHandle fence);
void checkDestroyFence(gnFenceHandle fence);
// gnReturnCode fdsfsdf(gnOutputDevice device, gnSubmitSyncInfo info);

gnReturnCode checkSubmitSync(gnOutputDevice device, gnSubmitSyncInfo info);
gnReturnCode checkPresentSync(gnOutputDevice device, gnPresentSyncInfo info);
