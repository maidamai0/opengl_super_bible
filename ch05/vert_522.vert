#version 430 core

layout(location = 0) in vec4 position;

out VS_OUT {
    vec4 color;
}vs_out;

layout (location = 1) uniform mat4 model_view;
layout (location = 2) uniform mat4 perspective;

void main () {
    gl_Position = perspective * model_view *  position;
    vs_out.color = position * 2.0 + vec4(0.5, 0.5,0.5, 0.0);
}