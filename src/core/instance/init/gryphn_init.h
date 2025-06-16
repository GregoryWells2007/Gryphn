#pragma once
#include <gryphn/gryphn_utils.h>
#include <core/gryphn_rendering_api.h>
#include "core/gryphn_platform_functions.h"
// #include "utils/gryphn_error_code.h"

gnBool gnIsAPISupported(gnRenderingAPI RenderingAPI);
struct gnDynamicLibrary_t* gnLoadRenderingDLL(gnRenderingAPI RenderingAPI);
gnInstanceFunctions* gnLoadFunctions(gnInstance instance);
void gnLoadDeviceFunctions(struct gnDynamicLibrary_t* lib, struct gnDeviceFunctions_t* functions);
void gnLoadCommandFunctions(struct gnDynamicLibrary_t* lib, struct gnCommandFunctions_t* function);
