#pragma once
#include <vulkan/vulkan.h>
#include <core/debugger/gryphn_debugger.h>

typedef struct gnPlatformDebugger_t {
    VkDebugUtilsMessengerEXT debugMessenger;
} gnPlatformDebugger;

void vkPopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo);
