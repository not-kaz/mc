#version 330 core

out vec4 frag_color;

uniform vec4 custom_color;

void main()
{
    frag_color = custom_color;
}