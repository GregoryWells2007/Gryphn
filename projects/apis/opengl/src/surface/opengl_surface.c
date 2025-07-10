#include <glad/glad.h>
#include "GL/glext.h"
#include "opengl_surface.h"

#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
#include <X11/Xlib.h>
gnReturnCode createGLXContext(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo) {
    windowSurface->windowSurface = malloc(sizeof(gnPlatformWindowSurface));
    int attribs[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
    };

    XVisualInfo* vi = glXChooseVisual(createInfo.display, 0, attribs);
    windowSurface->windowSurface->context = glXCreateContext(createInfo.display, vi, NULL, GL_TRUE);
    if (glXMakeCurrent(createInfo.display, createInfo.window, windowSurface->windowSurface->context) == GL_FALSE)
        return GN_FAILED_TO_ATTACH_WINDOW;
    windowSurface->windowSurface->window = createInfo.window;
    windowSurface->windowSurface->display = createInfo.display;
    if (!gladLoadGLLoader((GLADloadproc)glXGetProcAddress))
        return GN_FAILED_TO_INIT_OPENGL;
    return GN_SUCCESS;
}

gnUInt2 getWindowSize(gnPlatformWindowSurface* surface) {
    XWindowAttributes attr;
    XGetWindowAttributes(surface->display, surface->window, &attr);
    return (gnUInt2){ attr.width, attr.height };
}

#endif

#ifdef GN_WINFDOW_WAYLAND
gnReturnCode gnCreateWaylandWindowSurface(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnWaylandWindowSurfaceInfo createInfo) {
    return GN_FAILED_TO_ATTACH_WINDOW;
}
#endif
#endif

gnSurfaceDetails genOpenGLSurfaceDetails(
    gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device
) {
    gnSurfaceDetails surfaceDetails;
    surfaceDetails.formatCount = 1;
    surfaceDetails.formats = (gnSurfaceFormat[]){
        (gnSurfaceFormat){
            .format = GN_FORMAT_RGBA8_SRGB,
            .colorSpace = GN_COLOR_SPACE_SRGB_NONLINEAR
        }
    };

    surfaceDetails.minImageCount = 2;
    surfaceDetails.maxImageCount = 3;

    gnUInt2 windowSize = getWindowSize(windowSurface->windowSurface);
    surfaceDetails.minImageSize = windowSize;
    surfaceDetails.maxImageSize = windowSize;
    surfaceDetails.currentSize = windowSize;

    return surfaceDetails;
}

void destroyOpenGLSurface(gnWindowSurface surface) {
    free(surface->windowSurface);
}

GLint glGryphnFormatToOpenGLFormat(gnImageFormat format) {
    switch (format) {
    case GN_FORMAT_NONE: return GL_NONE;
    case GN_FORMAT_BGRA8: return GL_BGRA;
    case GN_FORMAT_RGBA8_SRGB: return GL_SRGB_ALPHA;
    case GN_FORMAT_D32S8_UINT: return GL_DEPTH_STENCIL;
    case GN_FORMAT_D24S8_UINT: return GL_DEPTH_STENCIL;

    // unsupprted formats
    case GN_FORMAT_BGRA8_SRGB: return GL_NONE;
    }
}
GLint glGryphnFormatToOpenGLInternalFormat(gnImageFormat format) {
    switch (format) {
    case GN_FORMAT_NONE: return GL_NONE;
    case GN_FORMAT_BGRA8: return GL_BGRA8_EXT;
    case GN_FORMAT_RGBA8_SRGB: return GL_SRGB8_ALPHA8;
    case GN_FORMAT_D32S8_UINT: return GL_DEPTH32F_STENCIL8;
    case GN_FORMAT_D24S8_UINT: return GL_DEPTH24_STENCIL8;

    // unsupprted formats
    case GN_FORMAT_BGRA8_SRGB: return GL_NONE;
    }
}
