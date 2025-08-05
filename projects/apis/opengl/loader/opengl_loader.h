#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"
#include "gryphn_extensions.h"

gnInstanceFunctions loadOpenGLInstanceFunctions();
gnDeviceFunctions loadOpenGLDeviceFunctions();
gnCommandFunctions loadOpenGLCommandFunctions();

gryphnInstanceFunctionLayers loadOpenGLAPILayer();
gnBool openglIsExtensionSupported(gnExtension extension);
