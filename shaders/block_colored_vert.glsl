#version 330 core

layout (location = 0) in vec3 pos_attr;
layout (location = 1) in vec2 tex_coord_attr;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 block_pos;

void main()
{ 
    gl_Position = projection * view * model * vec4(pos_attr + block_pos, 1);
}