#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_binding_description.h"
#include "gryphn_vertex_property.h"

struct gnPlatformVertexDescription;

struct gnVertexDescription {
ACCESS_LEVEL:
    gnPlatformVertexDescription* vertexDescription = nullptr;
    gnBindingDescription* bindingDescription;
public:
    gnVertexDescription() {}
};

inline void (*gnVertexDescriptionSetBindingDescription)(gnVertexDescription& vertexDescription, const gnBindingDescription& description);
inline void (*gnVertexDescriptionSetPropertiesCount)(gnVertexDescription& vertexDescription, int count);
inline void (*gnVertexDescriptionSetProperty)(gnVertexDescription& vertexDescription, int index, const gnVertexProperty& property);
