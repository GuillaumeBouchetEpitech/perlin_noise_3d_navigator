#version 150

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelviewMatrix;
uniform mat3 u_normalMatrix;

uniform int u_lightEnabled;

uniform int u_perturbationEnabled;
uniform float u_advance;

in vec3 a_vertex;
in vec3 a_color;
in vec3 a_normal;

out vec3 v_color;
out vec3 v_normal;
out vec3 v_eye;

void	main()
{

    vec3 tmp_vertex = a_vertex;
    vec3 tmp_normal = a_normal;
    vec3 tmp_color = a_color;

    /**/
    if (u_perturbationEnabled != 0)
    {
        float   perturbation = cos( a_vertex.x + u_advance * 3.14 ) + sin( a_vertex.y + u_advance * 3.14 );

        //vec3 tmp_vertex = a_vertex + a_normal * perturbation;
        tmp_vertex = a_vertex + vec3(0.5, 0.5, 0.5) * perturbation - vec3(-0.25, -0.25, -0.25);

        //vec3 tmp_normal = a_normal - a_normal * perturbation;
        tmp_normal = a_normal - vec3(0.0, 0.3, 0.6) * perturbation;
        normalize( tmp_normal );

        tmp_color = a_color - vec3(1.0, 1.0, 1.0) * perturbation;
        normalize( tmp_color );
    }
    //*/

    if (u_lightEnabled == 0)
    {
        v_color = tmp_color;
        gl_Position = u_projectionMatrix * u_modelviewMatrix * vec4( tmp_vertex, 1);
        return;
    }

    vec4  vertex = u_modelviewMatrix * vec4( tmp_vertex, 1);

    v_color = a_color;

    v_eye = -vec3(vertex);

    v_normal = u_normalMatrix * tmp_normal;

    gl_Position = u_projectionMatrix * vertex;
}
