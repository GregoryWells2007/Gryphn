#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"
#include "extensions/synchronization/loader/sync_functions.h"
#include "extensions/queues/queues_functions.h"
#include "core/gryphn_extensions.h"

typedef struct gryphnInstanceFunctionLayers gryphnInstanceFunctionLayers;
gryphnInstanceFunctionLayers loadVulkanAPILayer(void);

gnInstanceFunctions loadVulkanInstanceFunctions(void);
gnDeviceFunctions loadVulkanDeviceFunctions(void);
gnCommandFunctions loadVulkanCommandFunctions(void);
gnSyncExtFunctions loadVulkanSyncFunctions(void);
gnQueueExtFunctions loadVulkanQueueFunctions(void);

gnBool vulkanIsExtensionSupported(gnExtension extension);
