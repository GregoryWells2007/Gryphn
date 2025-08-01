#pragma once
#include <glad/glad.h>
#include "presentation_queue/gryphn_presentation_queue.h"

GN_ARRAY_LIST(GLuint);

typedef struct gnPlatformPresentationQueue_t {
    GLuintArrayList textures;
    uint32_tArrayList avaliableTextures;
} gnPlatformPresentationQueue_t;

gnReturnCode createOpenGLPresentationQueue(gnPresentationQueueHandle presentationQueue, gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo);
gnReturnCode getOpenGLPresentationQueueImage(gnPresentationQueue presentationQueue, uint32_t* imageIndex);
void destroyOpenGLPresentationQueue(gnPresentationQueueHandle presentationQueue);
