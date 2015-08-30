#version 150

struct LightProperties
{
    vec3 direction;
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};

struct MaterialProperties
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    float specularExponent;
};

uniform	LightProperties     u_light;
uniform	MaterialProperties  u_material;
uniform vec4 u_mode;

uniform int u_lightEnabled;

in vec3 v_color;
in vec3 v_normal;
in vec3 v_eye;

out vec4 fragColor;

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

    // Note: All calculations are in camera space.

    vec4  color = u_light.ambientColor * u_material.ambientColor * vec4(v_color, 1);

    vec3  normal = normalize(v_normal);

    float nDotL = max(dot(u_light.direction, normal), 0.0);

    if (nDotL > 0.0)
    {
        vec3  eye = normalize(v_eye);

        // Incident vector is opposite light direction vector.
        vec3  reflection = reflect(-u_light.direction, normal);

        float eDotR = max(dot(eye, reflection), 0.0);

        color += u_light.diffuseColor * u_material.diffuseColor * nDotL;

        float specularIntensity = 0.0;

        if (eDotR > 0.0)
            specularIntensity = pow(eDotR, u_material.specularExponent);

        color += u_light.specularColor * u_material.specularColor * specularIntensity;
    }

    fragColor = color;
}

//*/
