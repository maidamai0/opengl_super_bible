#version 430 core

layout (triangles, equal_spacing, cw) in;
out VS_OUT {
  vec4 color;
} tese_out;

void main(void) {
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position+gl_TessCoord.y * gl_in[1].gl_Position+gl_TessCoord.z * gl_in[2].gl_Position);
    tese_out.color = vec4(0.2, 0.4, 0.5, 1.0);
}