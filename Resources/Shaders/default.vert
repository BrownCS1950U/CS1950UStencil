#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 color;

out vec3 mcol;

void main(){
    gl_Position = vec4(pos, 1.0);
    mcol = color;
}