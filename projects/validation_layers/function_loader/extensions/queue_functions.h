#include <loader/src/gryphn_loader.h>

gnReturnCode checkGetPhysicalDeviceQueueProperties(gnPhysicalOutputDeviceHandle device, uint32_t queueCount, gnQueueFamilyProperties* queues);
void checkGetDeviceQueue(gnOutputDevice device, uint32_t queueFamily, uint32_t queueIndex, gnQueue* queue);

gnReturnCode checkQueueSubmit(gnOutputDevice device, gnQueue queue, gnSubmitInfo info);
gnReturnCode checkQueueSubmitSync(gnOutputDevice device, gnQueue queue, gnSubmitSyncInfo info);

gnReturnCode checkQueuePresent(gnDevice device, gnQueue queue, gnPresentInfo info);
gnReturnCode checkQueuePresentSync(gnDevice device, gnQueue queue, gnPresentSyncInfo info);
