#pragma once
#include <stdint.h>

#define GN_NULL_HANDLE 0
typedef uint32_t gnFlags;

#define GN_HANDLE(type) \
typedef struct type##_t* type##Handle; \
typedef struct type##_t* type

#define GN_IMPLEMENTATION_HANDLE(type) \
typedef uint64_t type##Handle; \
typedef uint64_t type

#define GN_HANDLE_ALIAS(handle, alias) \
typedef struct handle##_t* alias##Handle; \
typedef struct handle##_t* alias

GN_HANDLE(gnInstance);
GN_HANDLE(gnDebugger);
GN_HANDLE(gnWindowSurface);
GN_HANDLE(gnPresentationQueue);
GN_HANDLE(gnTexture);
GN_HANDLE(gnRenderPassDescriptor);
GN_HANDLE(gnPhysicalOutputDevice);
GN_HANDLE_ALIAS(gnPhysicalOutputDevice, gnPhysicalDevice);
GN_HANDLE(gnOutputDevice);
GN_HANDLE_ALIAS(gnOutputDevice, gnDevice);
GN_HANDLE(gnShaderModule);
GN_HANDLE(gnGraphicsPipeline);
GN_HANDLE(gnCommandPool);
GN_HANDLE(gnCommandBuffer);
GN_HANDLE(gnFramebuffer);
GN_HANDLE(gnBuffer);
GN_HANDLE(gnUniformPool);
GN_HANDLE(gnUniform);

// extension objects
// GN_EXT_SYNCHRONIZATION
GN_HANDLE(gnSemaphore);
GN_HANDLE(gnFence);
// GN_EXT_QUEUES
GN_IMPLEMENTATION_HANDLE(gnQueue); // NOTE: this is an implementaion specific object
