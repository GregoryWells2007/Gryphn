const char * vertex_shader_source =
    "#version 450 core\n"
    "\n"
    "layout(location = 0) in vec2 inPosition;\n"
    "layout(location = 1) in vec2 inTexcoord;\n"
    "\n"
    "out vec2 texcoord;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = vec4(inPosition, 0.0, 1.0);\n"
    "    texcoord = inTexcoord;\n"
    "}\n" ;
const char * fragment_shader_source =
    "#version 450 core\n"
    "\n"
    "out vec4 FragColor;\n"
    "layout(binding = 0) uniform sampler2D tex;\n"
    "in vec2 texcoord;\n"
    "\n"
    "void main() {\n"
    "   FragColor = texture(tex, texcoord);\n"
    "   //FragColor = vec4(texcoord, 0.0, 1.0);\n"
    "}\n" ;
