#pragma once
#include <gryphn/gryphn_utils.h>
#include "vector"

struct gnPlatformCommandBuffer;
struct gnOutputDevice;

struct gnCommandBuffer {
ACCESS_LEVEL:
    gnPlatformCommandBuffer* commandBuffer = nullptr;
public:
    gnCommandBuffer() {}
};

inline gnReturnCode (*gnCreateCommandBuffer)(gnCommandBuffer* commandBuffer, const gnOutputDevice& outputDevice);
inline gnReturnCode (*_gnCreateCommandBuffers)(gnCommandBuffer* commandBuffers, gnUInt commandBufferCount, const gnOutputDevice& outputDevice);
inline void (*gnCommandBufferReset)(const gnCommandBuffer& commandBuffer);
inline void (*gnDestroyCommandBuffer)(const gnCommandBuffer& commandBuffer);

// because C doesnt support overloading this is how I am going to support overloading, fuck you
static inline gnReturnCode gnCreateCommandBuffers(gnList<gnCommandBuffer> *commandBuffers, const gnOutputDevice& outputDevice) { return _gnCreateCommandBuffers(gnListData(*commandBuffers), gnListLength(*commandBuffers), outputDevice); }
static inline gnReturnCode gnCreateCommandBuffers(std::vector<gnCommandBuffer>* commandBuffers, const gnOutputDevice &outputDevice) { return _gnCreateCommandBuffers(commandBuffers->data(), commandBuffers->size(), outputDevice); }
