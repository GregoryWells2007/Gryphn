#include <core/graphics_pipeline/gryphn_graphics_pipeline.h>
#include <Metal/Metal.hpp>

struct mtlShaderRepresentation {
    gnShaderModuleStage module;
    int uniformBufferBinding, pushConstantBinding;
    std::unordered_map<gnUInt2, gnUInt> textureBindings;
};

struct gnPlatformGraphicsPipeline {
    MTL::RenderPipelineState* renderPipelineState = nullptr;
    MTL::RenderPipelineDescriptor* renderPipelineDescriptor = nullptr;
    MTL::DepthStencilDescriptor* depthStateDescriptor = nullptr;
    gnOutputDevice* outputDevice;
    std::vector<mtlShaderRepresentation> shaders = {};
    MTL::DepthStencilState* depthStencilState;

    gnBool dynamicStatesEnabled = false;
    std::vector<gnDynamicState> dynamicStates = {};

    // for the viewport
    gnUInt2 position = { 0, 0 };
    gnUInt2 size = { 100, 100 };
    gnFloat minDepth = 0.0f, maxDepth = 1.0f;

    // for the stencil
    gnInt2 stencil_position;
    gnUInt2 stencil_size;

    gnBool enableDepthClamp;
    gnFillMode fillMode;
    gnFloat lineWidth;

    gnCullMode cullMode;
    gnFrontFaceDirection direction;
    gnBool colorBlending;
};
