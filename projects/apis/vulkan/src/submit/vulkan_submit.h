#include <vulkan/vulkan.h>
#include <submit/gryphn_submit.h>
#include <sync/semaphore/vulkan_semaphore.h>
#include <sync/fence/vulkan_fence.h>
#include <commands/command_buffer/vulkan_command_buffer.h>
#include <output_device/vulkan_output_devices.h>
#include <renderpass/vulkan_render_pass_descriptor.h>
#include "extensions/synchronization/commands/gryphn_sync_submit.h"

gnReturnCode vulkanSubmitSyncQueue(gnOutputDevice device, gnQueue queue, gnSubmitSyncInfo info);
gnReturnCode vulkanSubmitSync(gnDevice device, gnSubmitSyncInfo info);
gnReturnCode vulkanSubmitQueue(gnOutputDevice device, gnQueue queue, gnSubmitInfo info);
gnReturnCode vulkanSubmit(gnDevice device, gnSubmitInfo info);
