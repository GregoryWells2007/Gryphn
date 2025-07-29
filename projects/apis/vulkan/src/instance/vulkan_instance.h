#pragma once
#include <vulkan/vulkan.h>
#include "instance/gryphn_instance.h"
#include "utils/lists/gryphn_array_list.h"

typedef struct vkUserData {
    gnDebuggerCallback debuggerCallback;
    void* userData;
} vkUserData;

typedef struct gnPlatformInstance_t {
    VkInstance vk_instance;
    vkUserData userData;
} gnPlatformInstance;

gnReturnCode createInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo);
void destroyInstance(gnInstanceHandle instance);

typedef const char* vkString;

GN_ARRAY_LIST(vkString);
