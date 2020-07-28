#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 fs_color;

void main () {
    gl_Position = position;
    fs_color = color;
}