#pragma once
#include <window_surface/gryphn_surface.h>
#include "core/src/window_surface/gryphn_surface_create_functions.h"

#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
#include <GL/glx.h>
typedef struct gnPlatformWindowSurface_t {
    GLXContext context;
} gnPlatformWindowSurface;
gnReturnCode createGLXContext(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo);
#endif
#endif
