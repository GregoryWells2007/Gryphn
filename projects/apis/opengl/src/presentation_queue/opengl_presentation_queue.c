#include "opengl_presentation_queue.h"
#include "surface/opengl_surface.h"
#include "textures/opengl_texture.h"

gnReturnCode createOpenGLPresentationQueue(gnPresentationQueueHandle presentationQueue, gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    presentationQueue->imageCount = presentationInfo.minImageCount;
    presentationQueue->images = malloc(sizeof(gnTexture) * presentationInfo.minImageCount);
    presentationQueue->presentationQueue->textures = GLuintArrayListCreate();
    presentationQueue->presentationQueue->avaliableTextures = uint32_tArrayListCreate();
    presentationQueue->presentationQueue->format = glGryphnFormatToOpenGLInternalFormat(presentationInfo.format.format);
    for (int i = 0; i < presentationInfo.minImageCount; i++) {
        presentationQueue->images[i] = malloc(sizeof(struct gnTexture_t));
        presentationQueue->images[i]->texture = malloc(sizeof(gnPlatformTexture));
        glCreateTextures(GL_TEXTURE_2D, 1, &presentationQueue->images[i]->texture->id);
        glTextureStorage2D(
            presentationQueue->images[i]->texture->id,
            1,
            glGryphnFormatToOpenGLInternalFormat(presentationInfo.format.format),
            presentationInfo.imageSize.x, presentationInfo.imageSize.y
        );
        GLuintArrayListAdd(presentationQueue->presentationQueue->textures, presentationQueue->images[i]->texture->id);
        uint32_tArrayListAdd(presentationQueue->presentationQueue->avaliableTextures, i);
    }
    return GN_SUCCESS;
}
gnReturnCode getOpenGLPresentationQueueImage(gnPresentationQueue presentationQueue, uint32_t* imageIndex) {
    while (uint32_tArrayListCount(presentationQueue->presentationQueue->avaliableTextures) == 0) {}
    *imageIndex = uint32_tArrayListAt(presentationQueue->presentationQueue->avaliableTextures, 0);
    uint32_tArrayListPopHead(presentationQueue->presentationQueue->avaliableTextures);
    return GN_SUCCESS;
}
void destroyOpenGLPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    free(presentationQueue->presentationQueue);
}



GN_ARRAY_LIST_DEFINITION(GLuint);
