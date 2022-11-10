#version 330 core

// All in object space
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 color;

uniform mat4 model, view, projection;

out vec4 camSpace_pos;
out vec4 camSpace_norm;
out vec2 tex_coord;
out vec3 vertColor;

void main() {
    camSpace_pos = view*model*vec4(pos, 1.0);
    camSpace_norm = transpose(inverse(view*model))*vec4(norm, 0.0);
    tex_coord = uv;
    vertColor = color;

    gl_Position = projection*view*model*vec4(pos, 1.0);
}