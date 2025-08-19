#include "opengl_command_runner.h"
#include "vector"

typedef struct openglCommandRunner_t {
    std::vector<openglFunctionBinding> commands = {};
} glCommandRunner;

GN_CPP_FUNCTION openglCommandRunner openglCreateCommandRunner() { return new glCommandRunner(); }
GN_CPP_FUNCTION void openglRunCommandRunner(openglCommandRunner runner) {
    for (int i = 0; i < runner->commands.size(); i++)
        runner->commands[i]();
}
GN_CPP_FUNCTION void openglResetCommandRunner(openglCommandRunner runner) { runner->commands.clear(); }
GN_CPP_FUNCTION void openglDestroyCommandRunner(openglCommandRunner* runner) {
    *runner = NULL;
    delete runner;
}

void openglCommandRunnerBindFunction(openglCommandRunner runner, openglFunctionBinding binding) { runner->commands.push_back(binding); }
