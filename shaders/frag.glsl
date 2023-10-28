#version 330 core
out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D tex_1;

uniform vec2 sprite_idx;
uniform vec2 sprite_px_size;

void main()
{
    vec2 position = vec2(sprite_idx.x/16.0, sprite_idx.y/16.0);
    vec2 tex_size =  vec2(1.0/sprite_px_size.x, 1.0/sprite_px_size.y);

    vec2 coord = position + tex_size * fract(tex_coord);
    frag_color = texture(tex_1, coord);
}