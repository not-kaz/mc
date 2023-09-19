#version 330 core
out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D tex_1;

void main()
{
    frag_color = texture(tex_1, tex_coord);
}