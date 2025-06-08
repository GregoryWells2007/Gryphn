#pragma once

#define GN_HANDLE(type) \
typedef struct type##_t* type##Handle; \
typedef struct type##_t* type

#define GN_HANDLE_ALIAS(alias, handle) \
typedef struct handle##_t* alias##Handle; \
typedef struct handle##_t* alias

GN_HANDLE(gnInstance);
GN_HANDLE(gnDebugger);
GN_HANDLE(gnWindowSurface);
GN_HANDLE(gnPresentationQueue);
GN_HANDLE(gnTexture);
GN_HANDLE(gnRenderPassDescriptor);
GN_HANDLE(gnOutputDevice);
GN_HANDLE_ALIAS(gnDevice, gnOutputDevice);
GN_HANDLE(gnShaderModule);
GN_HANDLE(gnGraphicsPipeline);
GN_HANDLE(gnCommandPool);
GN_HANDLE(gnCommandBuffer);
GN_HANDLE(gnSemaphore);
GN_HANDLE(gnFence);
GN_HANDLE(gnFramebuffer);
GN_HANDLE(gnBuffer);
GN_HANDLE(gnUniformPool);
GN_HANDLE(gnUniform);
