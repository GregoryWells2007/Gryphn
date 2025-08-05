#pragma once
#include <GL/gl.h>
#include "instance/gryphn_instance.h"

typedef struct gnPlatformInstance_t {} gnPlatformInstance;

gnReturnCode openglCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnInstanceFunctionLayers* next);
void openglDestroyInstance(gnInstanceHandle instance, gryphnInstanceFunctionLayers* next);
