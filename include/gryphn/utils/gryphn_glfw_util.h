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

static gnReturnCode gnCreateGLFWWindowSurface(struct gnWindowSurface_t* windowSurface, struct gnInstance_t* instance, GLFWwindow* window) {
    MTKView* view = gnCreateMTKView(glfwGetCocoaWindow(window));
    gnWindowSetMTKView(glfwGetCocoaWindow(window), view);
    CAMetalLayer* layer = gnGetCAMetalLayer(glfwGetCocoaWindow(window));

    gnMacOSWindowSurfaceInfo surfaceCreateInfo = {
        .layer = layer
    };

    return gnCreateMacOSWindowSurface(windowSurface, instance, surfaceCreateInfo);
}

// gnReturnCode gnCreateGLFWWindowSurface(struct gnWindowSurface_t* windowSurface, struct gnInstance_t* instance, GLFWwindow* window) {
//     gnMetalWindowSurfaceInfo surfaceCreateInfo = {
//         .layer = (CAMetalLayer*)glfwGetCocoaWindow(window).contentView.layer;
//     };
//     return gnCreateMetalWindowSurface(windowSurface, instance, surfaceCreateInfo);
// }

#endif
