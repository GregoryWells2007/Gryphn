const char * vertex_shader_source =
    "#version 450 core"
    ""
    "layout(location = 0) in vec2 inPosition;"
    "layout(location = 1) in vec2 inTexcoord;"
    ""
    "out vec2 texcoord;"
    ""
    "void main() {"
    "    gl_Position = vec4(inPosition, 0.0, 1.0);"
    "    texcoord = inTexcoord;"
    "}" ;
const char * fragment_shader_source =
    "#version 450 core"
    ""
    "out vec4 FragColor;"
    "layout(binding = 0) uniform sampler2D tex;"
    "in vec2 texcoord;"
    ""
    "void main() {"
    "    FragColor = texture(tex, texcoord);"
    "}" ;
