#include "vulkan_loader.h"
#include <sync/semaphore/vulkan_semaphore.h>
#include <sync/fence/vulkan_fence.h>
#include "presentation_queue/vulkan_presentation_queue.h"
#include "submit/vulkan_submit.h"

gnSyncExtFunctions loadVulkanSyncFunctions() {
    return (gnSyncExtFunctions){
        ._gnPresentationQueueGetImageAsync = getPresentQueueImageAsync,

        ._gnCreateSemaphore = createSemaphore,
        ._gnDestroySemaphore = destroySemaphore,

        ._gnCreateFence = createFence,
        ._gnWaitForFence = waitForFence,
        ._gnResetFence = resetFence,
        ._gnDestroyFence = destroyFence,

        ._gnSubmitSync = vulkanSubmitSync
    };
}
