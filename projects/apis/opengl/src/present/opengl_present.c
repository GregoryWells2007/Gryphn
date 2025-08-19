#include "opengl_present.h"
#include "presentation_queue/opengl_presentation_queue.h"
#include "device/opengl_output_device.h"
#include "surface/opengl_surface.h"

gnReturnCode openglPresent(gnOutputDeviceHandle device, gnPresentInfo info) {
    for (uint32_t i =0 ; i < info.presentationQueueCount; i++) {
        uint32_tArrayListAdd(info.presentationQueues[i]->presentationQueue->avaliableTextures, info.imageIndices[i]);

        glUseProgram(device->outputDevice->shaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, device->outputDevice->buffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        swapBuffers(info.presentationQueues[i]->info.surface);

        // id<MTLBlitCommandEncoder> blit = [commandBuffer blitCommandEncoder];
        // [blit copyFromTexture:info.presentationQueues[i]->images[info.imageIndices[i]]->texture->texture
        //         sourceSlice:0
        //         sourceLevel:0
        //         sourceOrigin:(MTLOrigin){0, 0, 0}
        //         sourceSize:(MTLSize){info.presentationQueues[i]->info.imageSize.x, info.presentationQueues[i]->info.imageSize.y, 1}
        //         toTexture:drawable.texture
        //     destinationSlice:0
        //     destinationLevel:0
        // destinationOrigin:(MTLOrigin){0, 0, 0}];

        // [blit endEncoding];

        // [drawable texture];

        // [commandBuffer presentDrawable:drawable];
        // [commandBuffer commit];
        // device->outputDevice->executingCommandBuffer = commandBuffer;
    }

    // [device->outputDevice->executingCommandBuffer waitUntilCompleted];

    // for (uint32_t i = 0; i < info.presentationQueueCount; i++) {
    //     if (info.presentationQueues[i]->info.imageSize.x != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.width ||
    //         info.presentationQueues[i]->info.imageSize.y != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.height) {
    //             return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
    //         }
    // }

    return GN_SUCCESS;
}
