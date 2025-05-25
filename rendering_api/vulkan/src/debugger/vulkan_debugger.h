#pragma once
#include <vulkan/vulkan.h>
#include <core/debugger/gryphn_debugger.h>

typedef struct gnPlatformDebugger_t {
    VkDebugUtilsMessengerEXT debugMessenger;
} gnPlatformDebugger;

#ifdef __cplusplus
extern "C" {
#endif
void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo);
#ifdef __cplusplus
}
#endif
