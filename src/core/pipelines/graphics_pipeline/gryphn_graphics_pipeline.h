#pragma once
#include <core/output_device/gryphn_output_device.h>
#include <core/uniforms/gryphn_uniform_layout.h>
#include <core/renderpass/gryphn_render_pass_descriptor.h>
#include <core/shader_module/gryphn_shader_module.h>
#include "utils/math/gryphn_vec2.h"
#include "core/gryphn_handles.h"
#include "core/shader_input/gryphn_shader_layout.h"

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

    uint32_t subpassIndex;
    gnRenderPassDescriptorHandle renderPassDescriptor;

    uint32_t shaderModuleCount;
    gnShaderModuleHandle* shaderModules;
    gnShaderInputLayout shaderInputLayout;

    gnUniformLayout uniformLayout;
} gnGraphicsPipelineInfo;

#ifdef GN_REVEAL_IMPL
struct gnGraphicsPipeline_t {
    struct gnPlatformGraphicsPipeline_t* graphicsPipeline;
    gnOutputDeviceHandle device;
    gnGraphicsPipelineInfo info;
};
#endif

gnReturnCode gnCreateGraphicsPipeline(gnGraphicsPipelineHandle* graphicsPipeline, gnOutputDeviceHandle device, struct gnGraphicsPipelineInfo_t info);
void gnDestroyGraphicsPipeline(gnGraphicsPipelineHandle graphicsPipeline);
