#include <metal_stdlib>
using namespace metal;

struct VertexOut {
    float4 position [[position]];
    float2 uv;
};

vertex VertexOut vs_main(uint vertexID [[vertex_id]]) {
    float2 positions[4] = {
        {-1.0, -1.0},
        { 1.0, -1.0},
        {-1.0,  1.0},
        { 1.0,  1.0}
    };
    float2 uvs[4] = {
        {0.0, 1.0},
        {1.0, 1.0},
        {0.0, 0.0},
        {1.0, 0.0}
    };

    VertexOut out;
    out.position = float4(positions[vertexID], 0.0, 1.0);
    out.uv = uvs[vertexID];
    return out;
}

fragment float4 fs_main(VertexOut in [[stage_in]],
                        texture2d<float> colorTex [[texture(0)]],
                        sampler samp [[sampler(0)]]) {
    return colorTex.sample(samp, in.uv);
}
