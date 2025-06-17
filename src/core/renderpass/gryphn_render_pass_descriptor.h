#pragma once
#include "stdint.h"
#include "utils/gryphn_image_format.h"
#include "utils/gryphn_error_code.h"
#include "core/gryphn_handles.h"

typedef enum gnRenderPassStage {
    GN_COLOR_ATTACHMENT_OUTPUT = 1,
    GN_EARLY_FRAGMENT_TEST = 2
} gnRenderPassStage; // I stole these from vulkan to make that conversion easier

typedef enum gnRenderPassAccess {
    GN_COLOR_ATTACHMENT_WRITE = 1,
    GN_DEPTH_STENCIL_WRITE = 2
} gnRenderPassAccess;

typedef enum gnLoadOperation_e {
    GN_LOAD_OPERATION_LOAD, GN_LOAD_OPERATION_CLEAR, GN_LOAD_OPERATION_DONT_CARE
} gnLoadOperation;

typedef enum gnStoreOperation_e {
    GN_STORE_OPERATION_STORE, GN_STORE_OPERATION_DONT_CARE
} gnStoreOperation;

typedef struct gnRenderPassAttachmentInfo_t {
    gnImageFormat format;
    gnLoadOperation loadOperation;
    gnStoreOperation storeOperation;

    gnLoadOperation stencilLoadOperation;
    gnStoreOperation stencilStoreOperation;

    gnImageLayout initialLayout;
    gnImageLayout finalLayout;
} gnRenderPassAttachmentInfo;

typedef struct gnSubpassAttachmentInfo_t {
    uint32_t index;
    gnImageLayout imageLayout;
} gnSubpassAttachmentInfo;

typedef struct gnSubpassInfo_t {
    uint32_t colorAttachmentCount;
    gnSubpassAttachmentInfo* colorAttachments;
    gnSubpassAttachmentInfo* depthAttachment;
} gnSubpassInfo;

#define GN_SUBPASS_EXTERNAL -1

typedef struct gnSubpassDependencyInfo_t {
    int source, destination;

    gnRenderPassStage soruceStageMask;
    gnRenderPassAccess sourceAccessMask;

    gnRenderPassStage destinationStageMask;
    gnRenderPassAccess destinationAccessMask;
} gnSubpassDependencyInfo;

typedef struct gnRenderPassDescriptorInfo {
    uint32_t attachmentCount;
    gnRenderPassAttachmentInfo* attachmentInfos;

    uint32_t subpassCount;
    gnSubpassInfo* subpassInfos;

    uint32_t dependencyCount;
    gnSubpassDependencyInfo* dependencies;
} gnRenderPassDescriptorInfo;

#ifdef GN_REVEAL_IMPL
struct gnRenderPassDescriptor_t {
    struct gnPlatformRenderPassDescriptor_t* renderPassDescriptor;
    gnRenderPassDescriptorInfo info;
    gnDeviceHandle device;
};
#endif

gnReturnCode gnCreateRenderPassDescriptor(gnRenderPassDescriptorHandle* renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info);
void gnDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass);
