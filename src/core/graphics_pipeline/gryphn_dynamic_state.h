#pragma once
#include <gryphn/gryphn_utils.h>

// this shit is lowkey only supported in vulkan, I think, I know for sure that OpenGL does not support this
// - me in 2024
//
//  Now that ive become a little more knowledgable I know that OpenGL automatically works with a dynamic pipeline and vulkan does not
// so im going to change this list of dynamic states and how all this shit works

typedef enum gnDynamicState {
    GN_DYNAMIC_STATE_VIEWPORT = 0,
    GN_DYNAMIC_STATE_SCISSOR = 1,
    // GN_DYNAMIC_STATE_LINE_WIDTH = 2,
    // GN_DYNAMIC_STATE_DEPTH_BIAS = 3,
    // GN_DYNAMIC_STATE_BLEND_CONSTANTS = 4,
    // GN_DYNAMIC_STATE_DEPTH_BOUNDS = 5,
    // GN_DYNAMIC_STATE_STENCIL_COMPARE_MASK = 6,
    // GN_DYNAMIC_STATE_STENCIL_WRITE_MASK = 7,
    // GN_DYNAMIC_STATE_STENCIL_REFERENCE = 8,
    // GN_DYNAMIC_STATE_CULL_MODE = 9,
    // GN_DYNAMIC_STATE_FRONT_FACE = 10,
    // GN_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY = 11,
    // GN_DYNAMIC_STATE_VIEWPORT_WITH_COUNT = 12,
    // GN_DYNAMIC_STATE_SCISSOR_WITH_COUNT = 13,
    // GN_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE = 14,
    // GN_DYNAMIC_STATE_DEPTH_TEST_ENABLE = 15,
    // GN_DYNAMIC_STATE_DEPTH_WRITE_ENABLE = 16,
    // GN_DYNAMIC_STATE_DEPTH_COMPARE_OP = 17,
    // GN_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE = 18,
    // GN_DYNAMIC_STATE_STENCIL_TEST_ENABLE = 19,
    // GN_DYNAMIC_STATE_STENCIL_OP = 20,
    // GN_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE = 21,
    // GN_DYNAMIC_STATE_DEPTH_BIAS_ENABLE = 22,
    // GN_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE = 23
} gnDynamicState;
