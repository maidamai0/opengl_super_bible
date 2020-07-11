# version 430 core

layout (triangles) in;
layout (points, max_vertices = 3) out;

out VS_OUT {
  vec4 color;
} gs_out;

void main ( )  {
    int i=0;
    for(int i=0; i<gl_in.length(); ++i) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }

    gs_out.color = vec4(0.2, 0.4, 0.5, 1.0);
}