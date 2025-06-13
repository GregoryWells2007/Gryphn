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
static gnReturnCode gnCreateGLFWWindowSurface(gnWindowSurfaceHandle* windowSurface, struct gnInstance_t* instance, GLFWwindow* window) {
    gnMacOSWindowSurfaceInfo surfaceCreateInfo = {
        .layer = gnCreateCAMetalLayer(glfwGetCocoaWindow(window))
    };

    return gnCreateMacOSWindowSurface(windowSurface, instance, surfaceCreateInfo);
}
#endif
#ifdef GN_PLATFORM_LINUX
#ifndef GLFW_EXPOSE_NATIVE_X11
#error "Must define GLFW_EXPOSE_NATIVE_X11 on linux"
#endif
static gnReturnCode gnCreateGLFWWindowSurface(gnWindowSurfaceHandle* windowSurface, struct gnInstance_t* instance, GLFWwindow* window) {
    gnX11WindowSurfaceInfo surfaceCreateInfo = {
        .window = glfwGetX11Window(window),
        .display = glfwGetX11Display()
    };

    return gnCreateX11WindowSurface(windowSurface, instance, surfaceCreateInfo);
}
#endif
