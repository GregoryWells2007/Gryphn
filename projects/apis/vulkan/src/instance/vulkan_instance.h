#pragma once
#include <vulkan/vulkan.h>
#include "instance/gryphn_instance.h"
#include "utils/lists/gryphn_array_list.h"
#include "loader/src/gryphn_instance_functions.h"

typedef struct vkUserData {
    gnDebuggerCallback debuggerCallback;
    void* userData;
} vkUserData;

typedef struct gnPlatformInstance_t {
    VkInstance vk_instance;
    vkUserData userData;
} gnPlatformInstance;

gnReturnCode createVulkanInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, PFN_gnCreateInstance* next);
void destroyVulkanInstance(gnInstanceHandle instance, PFN_gnDestroyInstance* next);

typedef const char* vkString;
GN_ARRAY_LIST(vkString);
