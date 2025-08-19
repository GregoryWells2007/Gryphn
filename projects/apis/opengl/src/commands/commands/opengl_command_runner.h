#pragma once
#include "utils/gryphn_cpp_function.h"
typedef struct openglCommandRunner_t* openglCommandRunner;
typedef void (*openglFunctionBinding)();

GN_CPP_FUNCTION openglCommandRunner openglCreateCommandRunner();
GN_CPP_FUNCTION void openglResetCommandRunner(openglCommandRunner runner);
GN_CPP_FUNCTION void openglDestroyCommandRunner(openglCommandRunner* runner);

void openglCommandRunnerBindFunction(openglCommandRunner runner, openglFunctionBinding binding);
