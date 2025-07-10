#include "opengl_presentation_queue.h"
#include "surface/opengl_surface.h"
#include "textures/opengl_texture.h"

gnReturnCode createOpenGLPresentationQueue(gnPresentationQueueHandle presentationQueue, gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    uint32_t convertedFormat = glGryphnFormatToOpenGLFormat(presentationInfo.format.format);

    presentationQueue->imageCount = presentationInfo.minImageCount;
    presentationQueue->images = malloc(sizeof(gnTexture) * presentationInfo.minImageCount);
    presentationQueue->presentationQueue->textures = GLuintArrayListCreate();
    presentationQueue->presentationQueue->avaliableTextures = uint32_tArrayListCreate();
    for (int i = 0; i < presentationInfo.minImageCount; i++) {
        presentationQueue->images[i] = malloc(sizeof(struct gnTexture_t));
        presentationQueue->images[i]->texture = malloc(sizeof(gnPlatformTexture));
        glGenTextures(1, &presentationQueue->images[i]->texture->id);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            glGryphnFormatToOpenGLInternalFormat(presentationInfo.format.format),
            presentationInfo.imageSize.x, presentationInfo.imageSize.y,
            0,
            glGryphnFormatToOpenGLFormat(presentationInfo.format.format),
            GL_UNSIGNED_BYTE,
            NULL
        );

        GLuintArrayListAdd(&presentationQueue->presentationQueue->textures, presentationQueue->images[i]->texture->id);
        uint32_tArrayListAdd(&presentationQueue->presentationQueue->avaliableTextures, i);
    }
    return GN_SUCCESS;
}
gnReturnCode getOpenGLPresentationQueueImage(gnPresentationQueue presentationQueue, uint32_t* imageIndex) {
    while (presentationQueue->presentationQueue->avaliableTextures.count == 0) {}
    *imageIndex = presentationQueue->presentationQueue->avaliableTextures.data[0];
    uint32_tArrayListPopHead(&presentationQueue->presentationQueue->avaliableTextures);
    return GN_SUCCESS;
}
void destroyOpenGLPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    free(presentationQueue->presentationQueue);
}
