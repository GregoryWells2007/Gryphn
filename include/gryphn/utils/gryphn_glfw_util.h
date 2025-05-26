#pragma once
#ifndef GRYPHN_INCLUDE
#error "Must inclue gryphn.h before using this file"
#endif
#ifndef _glfw3_h_
#error "Must include glfw before using this file"
#endif
#ifndef _glfw3_native_h_
#error "Must include glfw native before using this file"
#endif

#ifdef GN_PLATFORM_MACOS
#ifndef GLFW_EXPOSE_NATIVE_COCOA
#error "Must define GLFW_EXPOSE_NATIVE_COCOA on macos"
#endif

gnReturnCode gnCreateGLFWWindowSurface(struct gnWindowSurface_t* windowSurface, struct gnInstance_t* instance, GLFWwindow* window) {
    gnMacOSWindowSurfaceInfo surfaceCreateInfo = {
        .window = (NSWindow*)glfwGetCocoaWindow(window)
    };
    return gnCreateMacOSWindowSurface(windowSurface, instance, surfaceCreateInfo);
}

#endif
