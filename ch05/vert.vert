#version 430 core

layout(location = 0) in vec4 vertices;

void main () {
    gl_Position = vec4(vertices[gl_VertexID]);
}