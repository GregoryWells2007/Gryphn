#include "present/gryphn_present.h"
#include <sync/semaphore/vulkan_semaphore.h>
#include <presentation_queue/vulkan_presentation_queue.h>
#include <output_device/vulkan_output_devices.h>

gnReturnCode vulkanPresentSync(gnDevice device, gnPresentSyncInfo info);
gnReturnCode vulkanQueuePresentSync(gnDevice device, gnQueue queue, gnPresentSyncInfo info);
gnReturnCode vulkanPresent(gnDevice device, gnPresentInfo info);
gnReturnCode vulkanQueuePresent(gnOutputDevice device, gnQueue queue, gnPresentInfo info);
