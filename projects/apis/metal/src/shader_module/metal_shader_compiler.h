#pragma once
#include "stdint.h"
#include "stdlib.h"

typedef struct mtlShaderOptions {

} mtlShaderOptions;

const char* mtlCompileShader(uint32_t* code, size_t size, mtlShaderOptions* options);
