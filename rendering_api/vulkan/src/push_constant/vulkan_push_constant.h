#pragma once
#include <core/push_constant/gryphn_push_constant.h>
#include <vulkan/vulkan.h>
struct gnGraphicsPipeline;

struct gnPlatformPushConstant {
    VkPushConstantRange pushConstantRange;
    gnGraphicsPipeline* graphicsPipeline;
};
