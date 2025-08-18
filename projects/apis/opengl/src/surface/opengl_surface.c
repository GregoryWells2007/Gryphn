#include <glad/glad.h>
#include "opengl_surface.h"
#include "utils/gryphn_string.h"

void GLAPIENTRY openglMessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam ) {
  // fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
  //          ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
  //           type, severity, message );

  gnMessageSeverity gryphnSeverity;
  if (severity == GL_DEBUG_SEVERITY_HIGH) gryphnSeverity = GN_MESSAGE_ERROR;
  if (severity == GL_DEBUG_SEVERITY_MEDIUM) gryphnSeverity = GN_MESSAGE_WARNING;
  if (severity == GL_DEBUG_SEVERITY_LOW) gryphnSeverity = GN_MESSAGE_VERBOSE;

  gnMessageType gryphnType;
  if (type == GL_DEBUG_TYPE_ERROR) gryphnType = GN_DEBUG_MESSAGE_VALIDATION;
  if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) gryphnType = GN_DEBUG_MESSAGE_VALIDATION;
  if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) gryphnType = GN_DEBUG_MESSAGE_VALIDATION;
  if (type == GL_DEBUG_TYPE_PORTABILITY) gryphnType = GN_DEBUG_MESSAGE_VALIDATION;
  if (type == GL_DEBUG_TYPE_PERFORMANCE) gryphnType = GN_DEBUG_MESSAGE_PERFORMANCE;
  if (type == GL_DEBUG_TYPE_OTHER) gryphnType = GN_DEBUG_MESSAGE_GENERAL;

  gnInstanceHandle handle = (gnInstanceHandle)userParam;
  handle->debugger.callback(
      gryphnSeverity,
      gryphnType,
      (gnMessageData){ .message = gnCreateString(message) },
      handle->debugger.userData
  );


}

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
        return GN_WINDOW_IN_USE;
    windowSurface->windowSurface->window = createInfo.window;
    windowSurface->windowSurface->display = createInfo.display;
    if (!gladLoadGLLoader((GLADloadproc)glXGetProcAddress)) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load OpenGL functions")
        });

        return GN_UNKNOWN_ERROR;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(openglMessageCallback, instance);

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
    surfaceDetails.formats = malloc(sizeof(gnSurfaceFormat) * 2);
    surfaceDetails.formats[0] = (gnSurfaceFormat){
        .format = GN_FORMAT_RGBA8,
        .colorSpace = GN_COLOR_SPACE_SRGB_NONLINEAR
    };
    surfaceDetails.formats[1] = (gnSurfaceFormat){
        .format = GN_FORMAT_RGBA8_SRGB,
        .colorSpace = GN_COLOR_SPACE_SRGB_NONLINEAR
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
    case GN_FORMAT_RGBA8: return GL_RGBA;
    case GN_FORMAT_RGBA8_SRGB: return GL_SRGB_ALPHA;
    case GN_FORMAT_D32S8_UINT: return GL_DEPTH_STENCIL;
    case GN_FORMAT_D24S8_UINT: return GL_DEPTH_STENCIL;

    // unsupprted formats
    case GN_FORMAT_BGRA8: return GL_NONE;
    case GN_FORMAT_BGRA8_SRGB: return GL_NONE;
    }
}
GLint glGryphnFormatToOpenGLInternalFormat(gnImageFormat format) {
    switch (format) {
    case GN_FORMAT_NONE: return GL_NONE;
    case GN_FORMAT_RGBA8: return GL_RGBA8;
    case GN_FORMAT_RGBA8_SRGB: return GL_SRGB8_ALPHA8;
    case GN_FORMAT_D32S8_UINT: return GL_DEPTH32F_STENCIL8;
    case GN_FORMAT_D24S8_UINT: return GL_DEPTH24_STENCIL8;

    // unsupprted formats
    case GN_FORMAT_BGRA8: return GL_NONE;
    case GN_FORMAT_BGRA8_SRGB: return GL_NONE;
    }
}
