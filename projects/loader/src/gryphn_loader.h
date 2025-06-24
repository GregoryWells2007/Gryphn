#pragma once
#include "gryphn_instance_functions.h"
#include "gryphn_device_functions.h"
#include "gryphn_command_functions.h"
#include "gryphn_loader_info.h"

gnInstanceFunctions loadInstanceFunctions(loaderInfo info);
gnDeviceFunctions loadDeviceFunctions(loaderInfo info);
gnCommandFunctions loadCommandFunctions(loaderInfo info);
