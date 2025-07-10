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
