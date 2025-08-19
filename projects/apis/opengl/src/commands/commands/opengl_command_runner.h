#pragma once
#include "utils/gryphn_cpp_function.h"
typedef struct openglCommandRunner_t* openglCommandRunner;

GN_CPP_FUNCTION openglCommandRunner openglCreateCommandRunner();
GN_CPP_FUNCTION void openglResetCommandRunner(openglCommandRunner runner);
GN_CPP_FUNCTION void openglRunCommandRunner(openglCommandRunner runner);
GN_CPP_FUNCTION void openglDestroyCommandRunner(openglCommandRunner* runner);

#ifdef __cplusplus
#include "functional"
#define openglBindFunction(expr) std::function<void()>([=]{ expr; })
void openglCommandRunnerBindFunction(openglCommandRunner runner, std::function<void()> function);
#endif
