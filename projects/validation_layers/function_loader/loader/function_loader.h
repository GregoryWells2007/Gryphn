#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"

gnInstanceFunctions loadFunctionLoaderInstanceFunctions(gnInstanceFunctions* callbacks);
gnDeviceFunctions loadFunctionLoaderDeviceFunctions(gnDeviceFunctions* callbacks);
gnCommandFunctions loadFunctionLoaderCommandFunctions(gnCommandFunctions* callbacks);
