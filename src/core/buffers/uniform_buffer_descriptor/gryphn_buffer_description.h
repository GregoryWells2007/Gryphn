#pragma once
#include <gryphn/gryphn_utils.h>

struct gnPlatformBufferDescription;
struct gnGraphicsPipeline;

// I have zero fucking clue what this class does?????
// I know I wrote it but there are zero references to it so i think that its some black magic thing I wrote
// Imma pretend that I doesnt exist for now and just not write a metal implementation for it
// This is going to end horribly but who fucking cares
struct gnBufferDescription {
ACCESS_LEVEL:
    gnPlatformBufferDescription* bufferDescription;
public:
    gnBufferDescription();
};

inline gnReturnCode (*gnCreateBufferDescription)(gnBufferDescription* bufferDescription, const gnGraphicsPipeline& graphicsPipeline);
