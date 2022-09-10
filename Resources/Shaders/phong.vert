#version 330 core

layout (location = 0) in vec3 objSpace_pos;
layout (location = 1) in vec3 objSpace_norm;
layout (location = 2) in vec2 uv_coords;
layout (location = 3) in vec3 obj_color;

uniform mat4 model, view, projection;

out vec4 camSpace_pos;
out vec4 camSpace_norm;
out vec2 uv;
out vec3 vertColor;

void main() {
    camSpace_pos = view*model*vec4(objSpace_pos, 1.0);
    camSpace_norm = transpose(inverse(view*model))*vec4(objSpace_norm, 0.0);
    uv = uv_coords;
    vertColor = obj_color;

    gl_Position = projection*view*model*vec4(objSpace_pos, 1.0);
}