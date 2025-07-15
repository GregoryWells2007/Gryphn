#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"
#include "extensions/synchronization/loader/sync_functions.h"
#include "core/gryphn_extensions.h"

gnInstanceFunctions loadMetalInstanceFunctions();
gnDeviceFunctions loadMetalDeviceFunctions();
gnCommandFunctions loadMetalCommandFunctions();
gnSyncExtFunctions loadMetalSyncFunctions();

gnBool metalIsExtensionSupported(gnExtension extension);
