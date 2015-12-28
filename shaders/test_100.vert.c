#version 140

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelviewMatrix;

uniform int u_lightEnabled;

in vec3 a_vertex;
in vec3 a_color;
in vec3 a_normal;

out vec3 v_color;
out vec3 normalInterp;
out vec3 vertPos;

void	main()
{
    v_color = a_color;

    if (u_lightEnabled == 0)
    {
        gl_Position = u_projectionMatrix * u_modelviewMatrix * vec4( a_vertex, 1);
    }
    else
    {
        vec4  vertex4 = u_modelviewMatrix * vec4( a_vertex, 1);
        vertPos = vec3(vertex4) / vertex4.w;
        normalInterp = vec3(u_modelviewMatrix * vec4(a_normal, 0));

        gl_Position = u_projectionMatrix * vertex4;
    }
}
