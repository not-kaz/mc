#version 330 core

out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D tex_1;

void main()
{
    float tex_scale = 1.0 / 16.0;
    frag_color = texture(tex_1, vec2(tex_coord.x * tex_scale, tex_coord.y * tex_scale));
}