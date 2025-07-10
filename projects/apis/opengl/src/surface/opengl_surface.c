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
    return GN_SUCCESS;
}
#endif

#ifdef GN_WINFDOW_WAYLAND
gnReturnCode gnCreateWaylandWindowSurface(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnWaylandWindowSurfaceInfo createInfo) {
    return GN_FAILED_TO_ATTACH_WINDOW;
}
#endif
#endif
