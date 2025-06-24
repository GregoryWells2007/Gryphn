#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"
#include "loader/src/gryphn_loader_info.h"

gnInstanceFunctions loadVulkanInstanceFunctions(loaderInfo info);
gnDeviceFunctions loadVulkanDeviceFunctions(loaderInfo info);
gnCommandFunctions loadVulkanCommandFunctions(loaderInfo info);
