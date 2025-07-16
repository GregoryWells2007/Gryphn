#pragma once
#include <vulkan/vulkan.h>

#include <output_device/vulkan_physical_device.h>
#include <extensions/queues/gryphn_physcial_device_queue.h>

gnReturnCode vulkanPhysicalDeviceQueueProperties(gnPhysicalOutputDeviceHandle device, uint32_t queueFamilyCount, gnQueueFamilyProperties* queues);
