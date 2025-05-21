#include "vulkan_debugger.h"
#include "instance/vulkan_instance.h"
#include "iostream"

bool checkValidationLayerSupport(std::vector<std::string> layers_to_validate) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (int i = 0; i < layers_to_validate.size(); i++) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layers_to_validate[i].c_str(), layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

typedef struct vk_userData_t {
    gnDebuggerCallback debuggerCallback;
    void* userData;
} vkUserData;

static VKAPI_ATTR VkBool32 VKAPI_CALL vk_debuggerDebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    vk_userData_t userData = *(struct vk_userData_t*)pUserData;

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

    gnDebuggerCallback callback = *userData.debuggerCallback;
    gnBool result = callback(severity, type, data, userData.userData);
    if (result == gnFalse) return VK_FALSE;
    else if (result == gnTrue) return VK_TRUE;
    return VK_FALSE;
}

VkResult vk_createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (vkCreateDebugUtilsMessengerEXT != nullptr)
        return vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
}

void vk_destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (vkDestroyDebugUtilsMessengerEXT != nullptr) {
        vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, pAllocator);
    }
}

GN_EXPORT gnReturnCode gnCreateDebuggerFn(gnDebugger* debugger, gnInstance* instance, const gnDebuggerInfo_t info) {
    debugger->debugger = new gnPlatformDebugger();

    if (!checkValidationLayerSupport({"VK_LAYER_KHRONOS_validation"}))
        return GN_FAILED_TO_CREATE_DEBUGGER;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;

    vk_userData_t* userData = (vk_userData_t*)malloc(sizeof(vk_userData_t));
    userData->debuggerCallback = info.callback;
    userData->userData = info.userData;

    populateDebugMessengerCreateInfo(createInfo);
    createInfo.pUserData = (void*)userData;
    createInfo.pfnUserCallback = vk_debuggerDebugCallback;

    for (int i = 0; i < instance->instance->instanceMessages.size(); i++) {
        info.callback(
            instance->instance->instanceMessages[i].severity,
            instance->instance->instanceMessages[i].type,
            instance->instance->instanceMessages[i].data,
            info.userData
        );
    }

    if (vk_createDebugUtilsMessengerEXT(instance->instance->vk_instance, &createInfo, nullptr, &debugger->debugger->debugMessenger) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_DEBUGGER;
    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyDebuggerFn(gnDebugger& debugger) {
    vk_destroyDebugUtilsMessengerEXT(*debugger.debugger->instance, debugger.debugger->debugMessenger, nullptr);
}
