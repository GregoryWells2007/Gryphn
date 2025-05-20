#pragma once
// theoretically you could have multible gryphn instances running in one application,
// why I dont know
#include "utils/gryphn_error_code.h"
#include "instance/gryphn_instance.h"

typedef struct gnFunctions_t {
    gnReturnCode (*_gnCreateInstance)(gnInstance* instance, struct gnInstanceInfo_t info);
    void (*_gnDestroyInstance)(gnInstance* instance);
} gnFunctions;
