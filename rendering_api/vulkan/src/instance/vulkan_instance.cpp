#include "gryphn/gryphn_utils.h"
#include "vector"
#include "vulkan_instance.h"

GN_EXPORT gnReturnCode gnCreateInstanceFn(gnInstance* instance, gnInstanceInfo instanceInfo) {
    instance->instance = new gnPlatformInstance();

    instance->valid = true;

    #ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
    instance->instance->extensions.push_back("VK_KHR_xlib_surface");
    #endif
    #ifdef GN_WINFDOW_WAYLAND
    instance->instance->extensions.push_back("VK_KHR_wayland_surface");
    #endif
    #endif
    #ifdef GN_PLATFORM_WINDOWS
    instance->instance->extensions.push_back("VK_MVK_macos_surface");
    #endif
    #ifdef GN_PLATFORM_MACOS
    instance->instance->extensions.push_back("VK_MVK_macos_surface");
    instance->instance->extensions.push_back("VK_KHR_portability_enumeration");
    instance->instance->extensions.push_back("VK_EXT_metal_surface");
    #endif


    instance->instance->extensions.push_back("VK_KHR_surface");
    instance->instance->extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = gnToCString(instanceInfo.applicationName),
        .applicationVersion = instanceInfo.applicationVersion,
        .pEngineName = gnToCString(instanceInfo.engineName),
        .engineVersion = instanceInfo.engineVersion,
        .apiVersion = VK_API_VERSION_1_3,
    };

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instance->instance->extensions.size());;
    createInfo.ppEnabledExtensionNames = instance->instance->extensions.data();

    if (vkCreateInstance(&createInfo, nullptr, &instance->instance->vk_instance) != VK_SUCCESS) {
        return GN_FAILED_CREATE_INSTANCE;
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyInstanceFn(gnInstance& instance) {
    instance.valid = false;
    vkDestroySurfaceKHR(instance.instance->vk_instance, instance.instance->window_surface, nullptr);
    vkDestroyInstance(instance.instance->vk_instance, nullptr);
}
