#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform sampler2D texture;

uniform mat4 mvpt;

varying vec2 vert_tc[];
varying vec3 vert_L[];
varying vec3 vert_V[];
varying vec3 vert_N[];
varying vec4 vert_vertex[];

varying vec2 geom_tc;
varying vec3 geom_L;
varying vec3 geom_V;
varying vec3 geom_N;
varying vec3 geom_Color;

void main()
{

    vec3 N = normalize(cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz,
            gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz));

    for(int i = 0; i < 3; i++)
    {
        geom_tc = vert_tc[i];
        geom_L  = vert_L[i];
        geom_V  = vert_V[i];
        geom_N  = vert_N[i];

        //geom_N  = N;

        geom_Color = vec3((gl_PrimitiveIDIn + 1) / 65536,
                          int(mod(gl_PrimitiveIDIn + 1, 65536)) / 256,
                          mod(gl_PrimitiveIDIn + 1, 256)) / 255.0;

        gl_Position = mvpt * (vert_vertex[i]);

        // gl_Position = gl_in[i].gl_Position;

        EmitVertex();
    }
    EndPrimitive();
}
