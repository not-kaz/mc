#version 330 core

layout (location = 0) in vec3 pos_attr;
layout (location = 1) in vec2 tex_coord_attr;

out vec2 tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    float tex_scale = 1.0 / 16.0;
    float ioffset = 1 * tex_scale;
    float joffset = 1 * tex_scale; 
    gl_Position = projection * view * model * vec4(pos_attr, 1);
    tex_coord = vec2(tex_coord_attr.x, tex_coord_attr.y);
}