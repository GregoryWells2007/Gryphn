#include <gryphn/gryphn.h>
#include <gryphn/gryphn_utils.h>
#include "bridge/metal_bridge.h"
#include "metal_instance.h"

GN_EXPORT gnReturnCode gnCreateInstanceFn(gnInstance* instance) {
    if (instance->instance == nullptr) instance->instance = new gnPlatformInstanceData();

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyInstanceFn(gnInstance& instance) {

}

GN_EXPORT gnReturnCode gnCreateMacOSWindowSurfaceFn(gnInstance& instance, NS::Window* window, NS::View* view) {
    if (instance.instance == nullptr) instance.instance = new gnPlatformInstanceData();

    instance.instance->metalContentView = view;
    return GN_SUCCESS;

}

// GN_EXPORT gnReturnCode gnInstanceSetWindowFn(gnInstance& instance, GLFWwindow* window) {
//     if (instance.instance == nullptr) instance.instance = new gnPlatformInstanceData();
//     instance.instance->window = window;

//     int width, height;
//     glfwGetFramebufferSize(instance.instance->window, &width, &height);

//     instance.instance->metalWindow = reinterpret_cast<NS::Window*>(glfwGetCocoaWindow(window));
//     instance.instance->metalContentView = reinterpret_cast<NS::View*>(glfwGetCocoaView(window));
//     return GN_SUCCESS;
// }
