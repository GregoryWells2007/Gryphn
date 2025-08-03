#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"
#include "extensions/synchronization/loader/sync_functions.h"
#include "extensions/queues/queues_functions.h"
#include "core/gryphn_extensions.h"

typedef struct gryphnInstanceFunctionLayers gryphnInstanceFunctionLayers;
gryphnInstanceFunctionLayers loadVulkanAPILayer();

gnInstanceFunctions loadVulkanInstanceFunctions();
gnDeviceFunctions loadVulkanDeviceFunctions();
gnCommandFunctions loadVulkanCommandFunctions();
gnSyncExtFunctions loadVulkanSyncFunctions();
gnQueueExtFunctions loadVulkanQueueFunctions();

gnBool vulkanIsExtensionSupported(gnExtension extension);
