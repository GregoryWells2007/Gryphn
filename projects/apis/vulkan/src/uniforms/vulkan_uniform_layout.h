#pragma once
#include <vulkan/vulkan.h>
#include <uniforms/gryphn_uniform_layout.h>

VkDescriptorSetLayout vkGryphnCreateSetLayouts(const gnUniformSet* set, VkDevice device);
VkDescriptorType vkGryphnUniformType(gnUniformType type);
