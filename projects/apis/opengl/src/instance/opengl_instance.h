#pragma once
#include <GL/gl.h>
#include "instance/gryphn_instance.h"

typedef struct gnPlatformInstance_t {} gnPlatformInstance;

gnReturnCode createOpenGLInstance(gnInstanceHandle instance, gnInstanceInfo instanceInfo);
void destroyOpenGLInstance(gnInstanceHandle instance);
