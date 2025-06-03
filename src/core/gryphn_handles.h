#pragma once

#define GN_HANDLE(type) \
typedef struct type##_t* type##Handle; \
typedef struct type##_t* type

GN_HANDLE(gnInstance);
GN_HANDLE(gnDebugger);
GN_HANDLE(gnWindowSurface);
GN_HANDLE(gnPresentationQueue);
GN_HANDLE(gnTexture);
