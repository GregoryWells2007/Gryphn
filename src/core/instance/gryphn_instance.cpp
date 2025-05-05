#include "gryphn_instance.h"

void gnInstanceSetDebugger(gnInstance& instance, gnDebugger& debugger) {
    instance.debugger = &debugger;
}

void gnInstanceSetAppInfo(gnInstance& instance, const gnAppInfo info) {
    instance.AppInfo = info;
}
