#include "opengl_command_runner.h"

typedef struct openglCommandRunner_t {

} glCommandRunner;

GN_CPP_FUNCTION openglCommandRunner openglCreateCommandRunner() { return new glCommandRunner(); }
GN_CPP_FUNCTION void openglDestroyCommandRunner(openglCommandRunner runner) { delete runner; }
