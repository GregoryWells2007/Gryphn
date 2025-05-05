#include <core/commands/present_command/gryphn_command_present.h>
#include "core/sync_objects/metal_semaphore.h"
#include "core/presentation_queue/metal_presentation_queue.h"
#include "core/devices/metal_output_devices.h"
#include "core/textures/metal_texture.h"
#include "core/metal_instance.h"
#include "bridge/metal_bridge.h"

GN_EXPORT gnPresentationQueueState gnCommandPresentGetValidPresentationQueueFn(gnCommandPresentData& presentCommandData) {
    return GN_VALID;
}
GN_EXPORT gnReturnCode gnCommandPresentFn(gnCommandPresentData& presentCommandData) {
    // dispatch_semaphore_wait(presentCommandData.semaphore->semaphore->semaphore, DISPATCH_TIME_FOREVER);
    // 2. Create the command buffer
    gnOutputDevice* outputDevice = mltGetOutputDevice(presentCommandData.presentationQueue->presentationQueue);
    MTL::CommandBuffer* commandBuffer = outputDevice->outputDevice->commandQueue->commandBuffer();

    // 3. Add a completed handler to signal the semaphore after the GPU has completed rendering.
    __block dispatch_semaphore_t semToSignal = presentCommandData.semaphore->semaphore->semaphore;
    commandBuffer->addCompletedHandler(^(MTL::CommandBuffer* buffer) {
        // Signal the semaphore after GPU work (drawing) is complete
        dispatch_semaphore_signal(semToSignal);
    });


    gnInstance* instance = outputDevice->outputDevice->instance;
    MTK::View* view = outputDevice->outputDevice->contentView;
    CA::MetalDrawable* drawable = presentCommandData.presentationQueue->presentationQueue->currentDrawable;
    // if (drawable == nullptr) {
    //     GN_RETURN_ERROR("drawable is null");
    // }

    MTL::RenderPassDescriptor* desc = MTL::RenderPassDescriptor::alloc()->init();
    desc->colorAttachments()->object(0)->setTexture(drawable->texture());
    desc->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    desc->colorAttachments()->object(0)->setStoreAction(MTL::StoreActionStore);
    desc->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(1, 0, 0, 1));

    auto enc = commandBuffer->renderCommandEncoder(desc);

    enc->setRenderPipelineState(instance->instance->framebufferRenderer);
    enc->setFragmentTexture(presentCommandData.presentationQueue->images[*presentCommandData.imageIndex].texture->texture, 0);
    enc->drawPrimitives(MTL::PrimitiveTypeTriangleStrip, NS::UInteger(0), NS::UInteger(4));

    enc->endEncoding();

    commandBuffer->presentDrawable(drawable);

    // // 5. Commit the command buffer
    commandBuffer->commit();

    // 6. Wait again on the semaphore to ensure the drawable is presented and the GPU work is complete.
    dispatch_semaphore_wait(semToSignal, DISPATCH_TIME_FOREVER);
    return GN_SUCCESS;
}
