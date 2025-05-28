#pragma once
#include "utils/types/gryphn_image_format.h"
#include "stdint.h"
#include "core/output_device/gryphn_output_device.h"

typedef enum gnLoadOperation_e {
    GN_LOAD_OPERATION_LOAD, GN_LOAD_OPERATION_CLEAR, GN_LOAD_OPERATION_DONT_CARE
} gnLoadOperation;

typedef enum gnStoreOperation_e {
    GN_STORE_OPERATION_STORE, GN_STORE_OPERATION_DONT_CARE
} gnStoreOperation;

typedef struct gnRenderPassAttachmentInfo_t {
    enum gnImageFormat_e format;
    enum gnLoadOperation_e loadOperation;
    enum gnStoreOperation_e storeOperation;

    enum gnLoadOperation_e stencilLoadOperation;
    enum gnStoreOperation_e stencilStoreOperation;

    enum gnImageLayout_e initialLayout;
    enum gnImageLayout_e finalLayout;
} gnRenderPassAttachmentInfo;

typedef struct gnSubpassAttachmentInfo_t {
    uint32_t index;
    enum gnImageLayout_e imageLayout;
} gnSubpassAttachmentInfo;

typedef struct gnSubpassInfo_t {
    uint32_t colorAttachmentCount;
    struct gnSubpassAttachmentInfo_t* colorAttachments;
} gnSubpassInfo;

typedef struct gnRenderPassDescriptorInfo_t {
    uint32_t attachmentCount;
    struct gnRenderPassAttachmentInfo_t* attachmentInfos;

    uint32_t subpassCount;
    struct gnSubpassInfo_t* subpassInfos;
} gnRenderPassDescriptorInfo;

struct gnPlatformRenderPassDescriptor_t;

typedef struct gnRenderPassDescriptor_t {
    struct gnPlatformRenderPassDescriptor_t* renderPassDescriptor;
    struct gnOutputDevice_t* device;
} gnRenderPassDescriptor;

gnReturnCode gnCreateRenderPassDescriptor(struct gnRenderPassDescriptor_t* renderPass, struct gnOutputDevice_t* device, struct gnRenderPassDescriptorInfo_t info);
void gnDestroyRenderPassDescriptor(struct gnRenderPassDescriptor_t* renderPass);
