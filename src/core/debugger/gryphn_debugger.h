#pragma once
#include <gryphn/gryphn_utils.h>
#include <iostream>
#include "gryphn_layers.h"

struct gnPlatformDebugger;
struct gnDebugger;

static gnDebugger* gnDebuggerInstance = nullptr;
inline void gnDebugError(gnString error);

struct gnDebugger {
ACCESS_LEVEL:
    gnPlatformDebugger* debugger;
    gnList<gnString> debug_layers = gnCreateList<gnString>();
public:
    gnDebugger() {
        if (debugger) gnDebugError("Debugger instance already created (you can only have one debugger)");
        gnDebuggerInstance = this;
    }
};

inline void gnDebugError(gnString error) { std::cout << gnToCString(error) << "\n"; }
void gnAddDebugLayer(gnDebugger& debugger, const gnString& layer);
const gnList<gnString>& gnDebuggerGetDebugLayers(gnDebugger& debugger);

inline gnReturnCode (*gnCreateDebugger)(gnDebugger* instance);
inline void (*gnDestroyDebugger)(gnDebugger& instance);
