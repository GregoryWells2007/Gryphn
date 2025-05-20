#pragma once
#include <gryphn/gryphn_utils.h>
#include <core/gryphn_rendering_api.h>
#include "core/gryphn_platform_functions.h"
// #include "utils/gryphn_error_code.h"

gnBool gnIsAPISupported(gnRenderingAPI RenderingAPI);
struct gnDynamicLibrary_t* gnLoadRenderingDLL(gnRenderingAPI RenderingAPI);
void gnLoadFunctions(struct gnDynamicLibrary_t* lib, struct gnFunctions_t* functions);

// #ifdef GN_REVEAL_IMPL
// gnErrorCode gnInit(gnRenderingAPI RenderingAPI);
// void gnDestroy();
// void* gnLoadFunction(gnString name);
// #endif
