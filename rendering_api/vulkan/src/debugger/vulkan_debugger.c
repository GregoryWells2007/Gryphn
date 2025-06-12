#include "vulkan_debugger.h"
#include <instance/vulkan_instance.h>
#include "core/instance/gryphn_instance.h"
#include "stdio.h"

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo) {
    createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
}


gnBool checkValidationLayerSupport(uint32_t count, const char** layers) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    if (layerCount == 0) return gnFalse;

    VkLayerProperties* properties = malloc(sizeof(VkLayerProperties) * layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, properties);

    for (int i = 0; i < count; i++) {
        gnBool layerFound = gnFalse;

        for (int c = 0; c < layerCount; c++) {
            if (strcmp(layers[i], properties[c].layerName) == 0) {
                layerFound = gnTrue;
                break;
            }
        }

        if (layerFound == gnFalse)
            return gnFalse;
    }

    return gnTrue;
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

    printf("Debuggger: %s\n", pCallbackData->pMessage);

    // struct vk_userData_t userData = *(struct vk_userData_t*)pUserData;

    // gnMessageSeverity severity;
    // gnMessageType type;
    // gnMessageData data = {
    //     .message = gnCreateString(pCallbackData->pMessage)
    // };

    // switch (messageSeverity) {
    // default: break;
    // case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: severity = GN_MESSAGE_VERBOSE; break;
    // case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: severity = GN_MESSAGE_INFO; break;
    // case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: severity = GN_MESSAGE_WARNING; break;
    // case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: severity = GN_MESSAGE_ERROR; break;
    // }

    // switch (messageType) {
    // default: break;
    // case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: type = GN_DEBUG_MESSAGE_GENERAL; break;
    // case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: type = GN_DEBUG_MESSAGE_VALIDATION; break;
    // case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: type = GN_DEBUG_MESSAGE_PERFORMANCE; break;
    // }

    // gnDebuggerCallback callback = *userData.debuggerCallback;
    // gnBool result = callback(severity, type, data, userData.userData);
    // if (result == gnFalse) return VK_FALSE;
    // else if (result == gnTrue) return VK_TRUE;
    return VK_FALSE;
}

VkResult vk_createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (vkCreateDebugUtilsMessengerEXT != NULL) {
        return vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, NULL, pDebugMessenger);
    }else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    return VK_SUCCESS;
}

void vk_destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (vkDestroyDebugUtilsMessengerEXT != NULL) {
        vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, pAllocator);
    }
}

gnReturnCode gnCreateDebuggerFn(gnDebuggerHandle debugger, gnInstanceHandle instance, const struct gnDebuggerInfo_t info) {
    debugger->debugger = malloc(sizeof(gnPlatformDebugger));

    if (instance->valid == gnFalse) {
        for (int i = 0; i < instance->instance->instanceMessageCount; i++) {
            info.callback(
                instance->instance->instanceMessages[i].severity,
                instance->instance->instanceMessages[i].type,
                instance->instance->instanceMessages[i].data,
                info.userData
            );
        }
        return GN_INVALID_INSTANCE;
    } else {
        for (int i = 0; i < instance->instance->instanceMessageCount; i++) {
            info.callback(
                instance->instance->instanceMessages[i].severity,
                instance->instance->instanceMessages[i].type,
                instance->instance->instanceMessages[i].data,
                info.userData
            );
        }
    }

    if (instance->instance->instanceMessageCount > 0) free(instance->instance->instanceMessages);
    instance->instance->instanceMessageCount = 0;

    const char* layers[] = {
        "VK_LAYER_KHRONOS_validation"
    };
    if (!checkValidationLayerSupport(1, layers))
        return GN_FAILED_TO_CREATE_DEBUGGER;


    struct vk_userData_t* userData = (struct vk_userData_t*)malloc(sizeof(struct vk_userData_t));
    userData->debuggerCallback = info.callback;
    userData->userData = info.userData;

    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pUserData = (void*)userData;
    createInfo.pfnUserCallback = vk_debuggerDebugCallback;

    VkResult result = vk_createDebugUtilsMessengerEXT(instance->instance->vk_instance, &createInfo, NULL, &debugger->debugger->debugMessenger);    if (result != VK_SUCCESS) {
        gnMessageSeverity severity = GN_MESSAGE_ERROR;
        gnMessageType type = GN_DEBUG_MESSAGE_VALIDATION;
        gnMessageData data = {
            .message = gnCombineStrings(
                gnCreateString("Failed to create gnDebuggerObject with api vulkan\n"),
                gnCombineStrings(gnCreateString("Returned with a vulkan error code of: (please do this)"), "")
            )
        };
        info.callback(
            severity,
            type,
            data,
            info.userData
        );

        return GN_FAILED_TO_CREATE_DEBUGGER;
    }
    return GN_SUCCESS;
}

void gnDestroyDebuggerFn(gnDebuggerHandle debugger) {
    vk_destroyDebugUtilsMessengerEXT(debugger->instance->instance->vk_instance, debugger->debugger->debugMessenger, NULL);
}
