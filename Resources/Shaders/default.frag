#version 330 core

out vec4 fragColor;

in vec3 mcol;

void main(){
    fragColor = vec4(mcol, 1);
}