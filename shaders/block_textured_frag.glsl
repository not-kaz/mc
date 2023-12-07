#version 330 core

out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D tex_1;
uniform vec2 offset;
uniform vec2 size;

void main()
{
    vec2 position = vec2(offset.x/16.0, offset.y/16.0);
    vec2 tex_size =  vec2(1.0/size.x, 1.0/size.y);
    vec2 coord = position + tex_size * fract(tex_coord);
    frag_color = texture(tex_1, coord);
}