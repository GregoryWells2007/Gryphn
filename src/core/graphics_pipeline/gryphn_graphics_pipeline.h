#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_dynamic_state.h"
#include "gryphn_render_pass.h"
#include "core/shaders/gryphn_shader.h"
#include "core/buffers/vertex_descriptions/gryphn_vertex_description.h"
#include "core/push_constant/gryphn_push_constant.h"
#include <core/uniform_descriptor/gryphn_uniform.h>

// things that are needed for compilation
struct gnOutputDevice;
struct gnBufferDescription;
struct gnUniformLayout;

// thse are some dumb things that I figured that would make code look nicer

typedef enum {
    GN_POINTS, GN_LINES, GN_LINE_STRIP, GN_TRIANGLES
} gnPrimative; // todo support more primative types

typedef enum {
    GN_POLYGON_FILLMODE_FILL, GN_POLYGON_FILLMODE_LINES, GN_POLYGON_FILLMODE_POINTS
} gnFillMode;

typedef enum {
    GN_CULL_NONE, GN_CULL_BACKFACE, GN_CULL_FRONTFACE
} gnCullMode; // idk why you would cull all but idk I added this

typedef enum {
    GN_CLOCKWISE, GN_COUNTER_CLOCKWISE
} gnFrontFaceDirection;

struct gnPlatformGraphicsPipeline;

struct gnGraphicsPipeline {
ACCESS_LEVEL:
    gnPlatformGraphicsPipeline* graphicsPipeline = nullptr;
    gnPrimative primative;
    gnRenderPass* renderPass;
    std::vector<gnUniformLayout*> uniformLayouts = {};
    std::vector<gnPushConstant*> pushConstants   = {};
public:
    gnGraphicsPipeline() {}
};

inline void (*gnGraphicsPipelineSetPrimative)(gnGraphicsPipeline& pipeline, gnPrimative primative);
inline void (*gnGraphicsPipelineEnableDynamicStates)(gnGraphicsPipeline& pipeline, const gnBool enable);
inline void (*gnGraphicsPipelineEnableDynamicState)(gnGraphicsPipeline& pipeline, const gnDynamicState state);
inline void (*_gnGraphicsPipelineSetViewport)(gnGraphicsPipeline& pipeline, gnUInt2 position, gnUInt2 size, gnFloat minDepth, gnFloat maxDepth);
inline static void gnGraphicsPipelineSetViewport(gnGraphicsPipeline& pipeline, gnUInt2 position, gnUInt2 size, gnFloat minDepth = 0.0f, gnFloat maxDepth = 1.0f) { _gnGraphicsPipelineSetViewport(pipeline, position, size, minDepth, maxDepth); }
inline void (*gnGraphicsPipelineSetCrop)(gnGraphicsPipeline& graphicsPipeline, gnInt2 position, gnUInt2 size);
inline void (*gnGraphicsPipelineSetDepthClamp)(gnGraphicsPipeline& graphicsPipeline, gnBool enableDepthClamp);
inline void (*gnGraphicsPipelineSetFillMode)(gnGraphicsPipeline& graphicsPipeline, gnFillMode fillMode);
inline void (*gnGraphicsPipelineSetLineWidth)(gnGraphicsPipeline& graphicsPipeline, gnFloat lineWidth);
inline void (*gnGraphicsPipelineSetCullMode)(gnGraphicsPipeline& graphicsPipeline, gnCullMode cullMode, gnFrontFaceDirection direction);
inline void (*gnGraphicsPipelineSetMultisampling)(gnGraphicsPipeline& graphicsPipeline, gnBool enableMultisampling);
inline void (*gnGraphicsPipelineEnableDepthTest)(gnGraphicsPipeline& graphicsPipeline, gnBool depthTest);
inline void (*gnGraphicsPipelineSetColorBlend)(gnGraphicsPipeline& graphicsPipeline, gnBool colorBlend);
inline void (*gnGraphicsPipelineSetVertexDescription)(gnGraphicsPipeline& graphicsPipeline, const gnVertexDescription& vertexDescription);
inline void (*gnGraphicsPipelineBindShader)(gnGraphicsPipeline& graphicsPipeline, const gnShader& shader);
inline void (*gnGraphicsPipelineSetRenderPass)(gnGraphicsPipeline& graphicsPipeline, gnRenderPass& renderpass);
inline void (*gnGraphicsPipelineAddUniformLayout)(gnGraphicsPipeline& graphicsPipeline, const gnUniformLayout& uniformLayout);
inline void (*gnGraphicsPipelineAddPushConstant)(gnGraphicsPipeline& graphicsPipeline, const gnPushConstant& pushConstant);
inline gnReturnCode (*gnCreateGraphicsPipeline)(gnGraphicsPipeline* graphicsPipeline, gnOutputDevice& outputDevice);
inline void (*gnDestroyGraphicsPipeline)(gnGraphicsPipeline& graphicsPipeline);
