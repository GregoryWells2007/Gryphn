#pragma once
#include <gryphn/gryphn_utils.h>
#include "application_information/gryphn_app_info.h"
#include "core/debugger/gryphn_debugger.h"
#include <core/output_device/gryphn_output_device.h>

class GLFWwindow;

struct gnPlatformInstanceData;

struct gnInstance {
ACCESS_LEVEL:
    bool valid = false;
    gnPlatformInstanceData* instance = nullptr;
    gnAppInfo AppInfo;
    gnDebugger* debugger;
public:
    gnInstance() {}
};

void gnInstanceSetAppInfo(gnInstance& instance, const gnAppInfo info);
void gnInstanceSetDebugger(gnInstance& instance, gnDebugger& debugger);

inline gnReturnCode (*gnCreateInstance)(gnInstance* instance);
inline void (*gnDestroyInstance)(gnInstance& instance);
inline gnReturnCode (*gnInstanceSetWindow)(gnInstance& instance, GLFWwindow* window);

// TODO: if instance creation fails add in a query to why the instance creation failed
// Lowkey thats a lot of work tho and I dont really want to do alllllll that
