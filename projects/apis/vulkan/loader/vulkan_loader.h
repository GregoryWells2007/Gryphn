#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"

gnInstanceFunctions loadVulkanInstanceFunctions();
gnDeviceFunctions loadVulkanDeviceFunctions();
gnCommandFunctions loadVulkanCommandFunctions();
