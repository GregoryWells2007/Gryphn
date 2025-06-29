#pragma once
#include <output_device/gryphn_output_device.h>
#include <uniforms/gryphn_uniform_layout.h>
#include <renderpass/gryphn_render_pass_descriptor.h>
#include <shader_module/gryphn_shader_module.h>
#include "utils/math/gryphn_vec2.h"
#include "gryphn_handles.h"
#include "shader_module/gryphn_shader_layout.h"

typedef enum gnDynamicState {
    GN_DYNAMIC_VIEWPORT,
    GN_DYNAMIC_SCISSOR,

    GN_DYNAMIC_STATE_MAX
} gnDynamicState;

typedef struct gnDynamicStateInfo {
    uint32_t dynamicStateCount;
    gnDynamicState* dynamicStates;
} gnDynamicStateInfo;

typedef enum gnPrimitiveType {
    GN_PRIMITIVE_POINTS, GN_PRIMITIVE_LINES, GN_PRIMITIVE_LINE_STRIP, GN_PRIMITIVE_TRIANGLES, GN_PRIMITIVE_TRIANGLE_STRIP
} gnPrimitiveType;

typedef enum gnBlendFactor {
    GN_BLEND_FACTOR_ZERO,
    GN_BLEND_FACTOR_ONE,
    GN_BLEND_FACTOR_SRC_ALPHA,
    GN_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA
} gnBlendFactor;

typedef enum gnBlendOperation {
    GN_OPERATION_ADD
} gnBlendOperation;

typedef struct gnViewport {
    gnVec2 position;
    gnVec2 size;
    float minDepth;
    float maxDepth;
} gnViewport;

typedef struct gnScissor {
    gnInt2 position;
    gnUInt2 size;
} gnScissor;

typedef enum gnFillMode {
    GN_FILL_MODE_FILL, GN_FILL_MODE_LINE, GN_FILL_MODE_POINT
} gnFillMode;

typedef enum gnCullFace {
    GN_CULL_FACE_NONE, GN_CULL_FACE_BACK, GN_CULL_FACE_FRONT
} gnCullFace;

typedef enum gnCullDirection {
    GN_DIRECTION_CLOCK_WISE, GN_DIRECTION_COUNTER_CLOCK_WISE
} gnCullDirection;

typedef enum gnCompareOperation {
    GN_COMPARE_NEVER, GN_COMPARE_LESS, GN_COMPARE_EQUAL,
    GN_COMPARE_LESS_OR_EQUAL, GN_COMPARE_GREATER, GN_COMPARE_NOT_EQUAL,
    GN_COMPARE_GREATER_OR_EQUAL, GN_COMPARE_ALWAYS
} gnCompareOperation;

typedef enum gnStencilOperation {
    GN_STENCIL_KEEP, GN_STENCIL_ZERO, GN_STENCIL_REPLACE,
    GN_STENCIL_INCREMENT_AND_CLAMP, GN_STENCIL_DECREMENT_AND_CLAMP,
    GN_STENCIL_INVERT, GN_STENCIL_INCREMENT_AND_WRAP,
    GN_STENCIL_DECREMENT_AND_WRAP,
} gnStencilOperation;

typedef struct gnCullMode_t {
    gnCullFace face;
    gnCullDirection direction;
} gnCullMode;

typedef struct gnColorBlending {
    gnBool enable;
    gnBlendFactor sourceColorBlendFactor;
    gnBlendFactor sourceAlphaBlendFactor;
    gnBlendFactor destinationColorBlendFactor;
    gnBlendFactor destinationAlphaBlendFactor;

    gnBlendOperation colorBlendOperation;
    gnBlendOperation alphaBlendOperation;
} gnColorBlending;

typedef struct gnStencilState {
    gnStencilOperation failOperation, passOperation, depthFailOperation;
    gnCompareOperation compareOperation;
    uint32_t compareMask, writeMask, reference;
} gnStencilState;

typedef struct gnDepthStencilState {
    gnBool depthTestEnable, depthWriteEnable;
    gnCompareOperation operation;
    gnBool stencilTestEnable;
    gnStencilState front, back;
} gnDepthStencilState;

typedef struct gnGraphicsPipelineInfo {
    gnDynamicStateInfo dynamicState;
    gnPrimitiveType primitiveType;
    gnViewport viewport;
    gnScissor scissor;
    gnFillMode fillMode;
    gnCullMode cullMode;
    gnColorBlending colorBlending;
    gnDepthStencilState depthStencil;

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

gnReturnCode gnCreateGraphicsPipeline(gnGraphicsPipelineHandle* graphicsPipeline, gnOutputDeviceHandle device, gnGraphicsPipelineInfo info);
void gnDestroyGraphicsPipeline(gnGraphicsPipelineHandle graphicsPipeline);
