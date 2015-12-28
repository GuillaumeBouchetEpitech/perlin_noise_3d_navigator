#version 140

uniform vec4 u_mode;

uniform int u_lightEnabled;

in vec3 v_color;
in vec3 normalInterp;
in vec3 vertPos;

out vec4 fragColor;

const vec3 lightPos = vec3(0);

void	main()
{

    if (u_mode.w > 0)
    {
        fragColor = u_mode;
        return;
    }

    if (u_lightEnabled == 0)
    {
        fragColor = vec4( v_color, 1 );
        return;
    }

    vec3  normal = normalize(normalInterp);
    vec3 lightDir = normalize(lightPos - vertPos);

    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;

    if (lambertian > 0.0)
    {
        // Incident vector is opposite light direction vector.
        vec3  reflectDir = reflect(-lightDir, normal);
        vec3  viewDir = normalize(-vertPos);

        float specAngle = max(dot(reflectDir, viewDir), 0.0);

        if (specAngle > 0.0)
            specular = pow(specAngle, 20);
    }

    fragColor = vec4( v_color.xyz * 0.2 + v_color.xyz * lambertian + vec3(1) * specular, 1.0);
}
