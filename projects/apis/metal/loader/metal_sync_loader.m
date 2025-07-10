#include "metal_loader.h"
#include <sync/semaphore/metal_semaphore.h>
#include <sync/fence/metal_fence.h>
#include "presentation_queue/metal_presentation_queue.h"
#include "submit/metal_submit.h"
#include "present/metal_present.h"

gnSyncExtFunctions loadMetalSyncFunctions() {
    return (gnSyncExtFunctions){
        ._gnPresentationQueueGetImageAsync = getMetalPresentQueueImageAsync,

        ._gnCreateSemaphore = createMetalSemaphore,
        ._gnDestroySemaphore = destroyMetalSemaphore,

        ._gnCreateFence = createMetalFence,
        ._gnWaitForFence = waitForMetalFence,
        ._gnResetFence = resetMetalFence,
        ._gnDestroyFence = destroyMetalFence,

        ._gnSubmitSync = metalSyncSubmit,
        ._gnPresentSync = metalPresentSync
    };
}
