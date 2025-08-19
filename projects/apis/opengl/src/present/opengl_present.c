#include "opengl_present.h"
#include "presentation_queue/opengl_presentation_queue.h"
#include "device/opengl_output_device.h"
#include "surface/opengl_surface.h"

gnReturnCode openglPresent(gnOutputDeviceHandle device, gnPresentInfo info) {
    for (uint32_t i =0 ; i < info.presentationQueueCount; i++) {
        uint32_tArrayListAdd(info.presentationQueues[i]->presentationQueue->avaliableTextures, info.imageIndices[i]);

        glBindVertexArray(0);

        glUseProgram(device->outputDevice->shaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, device->outputDevice->buffer);
        glBindTexture(GL_TEXTURE_2D, GLuintArrayListAt(info.presentationQueues[i]->presentationQueue->textures, info.imageIndices[i]));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glActiveTexture(GL_TEXTURE0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        swapBuffers(info.presentationQueues[i]->info.surface);
    }

    // for (uint32_t i = 0; i < info.presentationQueueCount; i++) {
    //     if (info.presentationQueues[i]->info.imageSize.x != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.width ||
    //         info.presentationQueues[i]->info.imageSize.y != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.height) {
    //             return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
    //         }
    // }

    return GN_SUCCESS;
}
