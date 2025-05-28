#pragma once
#include <core/output_device/gryphn_output_device.h>
#include <core/pipelines/gryphn_uniform_layout.h>

typedef enum gnDynamicState_e {
    GN_DYNAMIC_VIEWPORT,
    GN_DYNAMIC_SCISSOR,

    GN_DYNAMIC_STATE_MAX
} gnDynamicState;

typedef struct gnDynamicStateInfo_t {
    uint32_t dynamicStateCount;
    enum gnDynamicState_e* dynamicStates;
} gnDynamicStateInfo;

typedef enum gnPrimitiveType_e {
    GN_PRIMITIVE_POINTS, GN_PRIMITIVE_LINES, GN_PRIMITIVE_LINE_STRIP, GN_PRIMITIVE_TRIANGLES, GN_PRIMITIVE_TRIANGLE_STRIP
} gnPrimativeType;

typedef struct gnViewport_t {
    gnVec2 position;
    gnVec2 size;
    float minDepth;
    float maxDepth;
} gnViewport;

typedef struct gnScissor_t {
    gnInt2 position;
    gnUInt2 size;
} gnScissor;

typedef enum gnFillMode_e {
    GN_FILL_MODE_FILL, GN_FILL_MODE_LINE, GN_FILL_MODE_POINT
} gnFillMode;

typedef enum gnCullFace_e {
    GN_CULL_FACE_NONE, GN_CULL_FACE_BACK, GN_CULL_FACE_FRONT
} gnCullFace;

typedef enum gnCullDirection_e {
    GN_DIRECTION_CLOCK_WISE, GN_DIRECTION_COUNTER_CLOCK_WISE
} gnCullDirection;

typedef struct gnCullMode_t {
    enum gnCullFace_e face;
    enum gnCullDirection_e direction;
} gnCullMode;

typedef enum gnBlendFactor_e {
    GN_BLEND_FACTOR_ZERO,
    GN_BLEND_FACTOR_ONE,
    GN_BLEND_FACTOR_SRC_ALPHA,
    GN_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA
} gnBlendFactor;

typedef enum gnBlendOperation_e {
    GN_OPERATION_ADD
} gnBlendOperation;

typedef struct gnColorBlending_t {
    gnBool enable;
    enum gnBlendFactor_e sourceColorBlendFactor;
    enum gnBlendFactor_e sourceAlphaBlendFactor;
    enum gnBlendFactor_e destinationColorBlendFactor;
    enum gnBlendFactor_e destinationAlphaBlendFactor;

    enum gnBlendOperation_e colorBlendOperation;
    enum gnBlendOperation_e alphaBlendOperation;
} gnColorBlending;

typedef struct gnGraphicsPipelineInfo_t {
    struct gnDynamicStateInfo_t dynamicState;
    enum gnPrimitiveType_e primitiveType;
    struct gnViewport_t viewport;
    struct gnScissor_t scissor;
    enum gnFillMode_e fillMode;
    struct gnCullMode_t cullMode;
    struct gnColorBlending_t colorBlending;

    struct gnUniformLayout_t* uniformLayout;
} gnGraphicsPipelineInfo;

struct gnPlatformGraphicsPipeline_t;

typedef struct gnGraphicsPipeline_t {
    struct gnPlatformGraphicsPipeline_t* graphicsPipeline;
    struct gnOutputDevice_t* device;
} gnGraphicsPipeline;

gnReturnCode gnCreateGraphicsPipeline(struct gnGraphicsPipeline_t* graphicsPipeline, struct gnOutputDevice_t* device, struct gnGraphicsPipelineInfo_t info);
void gnDestroyGraphicsPipeline(struct gnGraphicsPipeline_t* graphicsPipeline);
