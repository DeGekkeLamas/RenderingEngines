#version 400 core
out vec4 FragColor;
in vec3 fPos; // world
in vec3 fNor; // world
in vec2 uv;
uniform vec3 lightPos; // world space
uniform vec3 camPos; // world space
uniform float lightStrength;

// IF you add the string replacement code, you could do this:
//#include lighting.glsl

vec4 Ambient()
{
    return vec4(0, 0, 0.3, 0);
}

float Diffuse()
{
    vec3 lightPosRel = lightPos - fPos.xyz; // world space
    float diffuse = dot(normalize(fNor), normalize(lightPosRel)); // different spaces!
    diffuse = max(diffuse, 0);
    // Attenuation
    float distance = length(lightPosRel);
    float attenuation = diffuse / (lightStrength + lightStrength * distance +  pow(lightStrength * distance, 2));
    attenuation = min(attenuation, diffuse);
    diffuse *= attenuation;
    return diffuse;
}

float Specular()
{
    vec3 lightPosRel = lightPos - fPos; // To object
    vec3 camPosRel = camPos - fPos; // To object

    vec3 reflection = reflect(-normalize(camPosRel), normalize(fNor));
    float specular = dot(reflection, normalize(lightPosRel));
    specular = pow(specular, 8);
    specular = clamp(specular, 0, 1);

    return specular;
}

void main()
{
    // Diffuse
    float diffuse = 0;//Diffuse();
    diffuse += Specular();
    FragColor = vec4(diffuse, diffuse, diffuse,1);
    // hard coded ambient:
    FragColor += Ambient();
}