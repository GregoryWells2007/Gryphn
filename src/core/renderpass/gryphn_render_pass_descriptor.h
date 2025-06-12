#pragma once
#include "stdint.h"
#include "utils/gryphn_image_format.h"
#include "utils/gryphn_error_code.h"
#include "core/gryphn_handles.h"

typedef enum gnRenderPassStage_e {
    GN_COLOR_ATTACHMENT_OUTPUT = 0x00000400
} gnRenderPassStage; // I stole these from vulkan to make that conversion easier

typedef enum gnRenderPassAccess_e {
    GN_COLOR_ATTACHMENT_WRITE = 0x00000100
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
    struct gnSubpassAttachmentInfo_t* colorAttachments;
} gnSubpassInfo;

#define GN_SUBPASS_EXTERNAL -1

typedef struct gnSubpassDependencyInfo_t {
    int source, destination;

    enum gnRenderPassStage_e soruceStageMask;
    enum gnRenderPassAccess_e sourceAccessMask;

    enum gnRenderPassStage_e destinationStageMask;
    enum gnRenderPassAccess_e destinationAccessMask;
} gnSubpassDependencyInfo;

typedef struct gnRenderPassDescriptorInfo_t {
    uint32_t attachmentCount;
    struct gnRenderPassAttachmentInfo_t* attachmentInfos;

    uint32_t subpassCount;
    struct gnSubpassInfo_t* subpassInfos;

    uint32_t dependencyCount;
    struct gnSubpassDependencyInfo_t* dependencies;
} gnRenderPassDescriptorInfo;

#ifdef GN_REVEAL_IMPL
struct gnRenderPassDescriptor_t {
    struct gnPlatformRenderPassDescriptor_t* renderPassDescriptor;
    struct gnRenderPassDescriptorInfo_t info;
    struct gnOutputDevice_t* device;
};
#endif

gnReturnCode gnCreateRenderPassDescriptor(gnRenderPassDescriptorHandle* renderPass, gnOutputDeviceHandle device, struct gnRenderPassDescriptorInfo_t info);
void gnDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass);
