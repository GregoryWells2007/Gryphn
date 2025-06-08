#pragma once
#include <vulkan/vulkan.h>
#include <core/uniforms/gryphn_uniform_layout.h>

VkDescriptorSetLayout* vkGryphnCreateSetLayouts(const gnUniformLayout* layout, uint32_t* setCount, VkDevice device);
