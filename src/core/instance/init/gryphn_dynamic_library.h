#pragma once
#include "utils/gryphn_string.h"
#include "utils/gryphn_bool.h"

typedef struct gnDynamicLibrary_t {
    void* dllPtr;
    gnBool isValid;
} gnDynamicLibrary;

struct gnDynamicLibrary_t* gnLoadDynamicLibrary(const gnString path);
void gnUnloadDynamicLibrary(struct gnDynamicLibrary_t* dll);
void* gnLoadFunctionPtr(struct gnDynamicLibrary_t* dll, const char* name);

#define gnLoadDLLFunction(dll, function, name) function = (typeof(function))gnLoadFunctionPtr(dll, name)
