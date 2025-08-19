#pragma once
#include "utils/gryphn_cpp_function.h"
typedef struct openglCommandRunner_t* openglCommandRunner;

GN_CPP_FUNCTION openglCommandRunner openglCreateCommandRunner();
GN_CPP_FUNCTION void openglDestroyCommandRunner(openglCommandRunner runner);
