#include "gryphn/gryphn_utils.h"
#include "vector"
#include "vulkan_instance.h"
#include "debugger/vulkan_debugger.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL vk_debuggerDebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    gnMessageSeverity severity;
    gnMessageType type;
    gnMessageData data = {
        .message = gnCreateString(pCallbackData->pMessage)
    };

    switch (messageSeverity) {
    default: break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: severity = GN_MESSAGE_VERBOSE; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: severity = GN_MESSAGE_INFO; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: severity = GN_MESSAGE_WARNING; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: severity = GN_MESSAGE_ERROR; break;
    }

    switch (messageType) {
    default: break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: type = GN_DEBUG_MESSAGE_GENERAL; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: type = GN_DEBUG_MESSAGE_VALIDATION; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: type = GN_DEBUG_MESSAGE_PERFORMANCE; break;
    }

    gnInstance* instance = (gnInstance*)pUserData;
    instance->instance->instanceMessages.push_back({
        .data = data,
        .severity = severity,
        .type = type
    });

    return VK_FALSE;
}

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

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };
    createInfo.enabledLayerCount = 1;
    createInfo.ppEnabledLayerNames = validation_layers;

    populateDebugMessengerCreateInfo(debugCreateInfo);
    debugCreateInfo.pfnUserCallback = vk_debuggerDebugCallback;
    debugCreateInfo.pUserData = instance;
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;

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
