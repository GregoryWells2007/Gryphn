#include "vulkan_instance.h"
#include <debugger/vulkan_debugger.h>
#include <stdio.h>

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

    if (instance->debugger) {
        instance->debugger->info.callback(
          severity, type, data, instance->debugger->info.userData
        );
    } else {
        instance->instance->instanceMessageCount++;
        if (instance->instance->instanceMessageCount == 1) {
            instance->instance->instanceMessages = malloc(sizeof(struct gnInstanceMessage) * instance->instance->instanceMessageCount);
        }
        else {
        instance->instance->instanceMessages = realloc(instance->instance->instanceMessages, sizeof(struct gnInstanceMessage) * instance->instance->instanceMessageCount);
        }
            instance->instance->instanceMessages[instance->instance->instanceMessageCount - 1] = (struct gnInstanceMessage){
                .data = data,
                .severity = severity,
                .type = type
            };
    }

    return VK_FALSE;
}

gnReturnCode gnCreateInstanceFn(gnInstance* instance, gnInstanceInfo instanceInfo) {
    instance->instance = malloc(sizeof(gnPlatformInstance));

    #ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
    uint32_t extensionCount = 3;
    const char* extensions[] = {
        "VK_KHR_xlib_surface",
        "VK_KHR_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };
    #endif
    #ifdef GN_WINFDOW_WAYLAND
    uint32_t extensionCount = 3;
    const char* extensions[] = {
        "VK_KHR_wayland_surface",
        "VK_KHR_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };
    #endif
    #endif
    #ifdef GN_PLATFORM_WINDOWS
    uint32_t extensionCount = 3;
    const char* extensions[] = {
        "VK_KHR_win32_surface",
        "VK_KHR_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };
    #endif
    #ifdef GN_PLATFORM_MACOS
    uint32_t extensionCount = 4;
    const char* extensions[] = {
        "VK_KHR_portability_enumeration",
        "VK_EXT_metal_surface",
        "VK_KHR_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };
    #endif

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

    const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };
    createInfo.enabledLayerCount = 1;
    createInfo.ppEnabledLayerNames = validation_layers;

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
    populateDebugMessengerCreateInfo(&debugCreateInfo);
    debugCreateInfo.pfnUserCallback = vk_debuggerDebugCallback;
    debugCreateInfo.pUserData = instance;
    createInfo.pNext = &debugCreateInfo;

    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;

    VkResult result = vkCreateInstance(&createInfo, NULL, &instance->instance->vk_instance);
    if (result != VK_SUCCESS)
        return GN_FAILED_CREATE_INSTANCE;
    instance->valid = gnTrue;

    return GN_SUCCESS;
}

void gnDestroyInstanceFn(gnInstance* instance) {
    instance->valid = gnFalse;
    vkDestroyInstance(instance->instance->vk_instance, NULL);
}
