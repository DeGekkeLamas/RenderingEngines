#version 400 core
out vec4 FragColor;
in vec3 fPos;
in vec3 fNor;
in vec2 uv;
uniform sampler2D text;
uniform vec4 lightColor;
uniform vec3 lightPos; // world space
uniform vec3 camPos; // world space
uniform float lightStrength;

// IF you add the string replacement code, you could do this:
//#include lighting.glsl

vec4 Ambient()
{
    return vec4(0, 0, 0.1, 0);
}

float Diffuse()
{
    vec3 lightPosRel = lightPos - fPos.xyz; // world space
    float diffuse = dot(normalize(fNor), normalize(lightPosRel)); // different spaces!
    diffuse = max(diffuse, 0);
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

float AddAttenuation(float diffuseAndSpecular)
{
    // Attenuation
    float distance = length(lightPos - fPos);
    float attenuation = diffuseAndSpecular / (.25f + .125f * distance +  pow(.125f * distance, 2));
    attenuation *= lightStrength;
    attenuation = min(attenuation, diffuseAndSpecular);
    diffuseAndSpecular *= attenuation;
    return diffuseAndSpecular;
}

void main()
{
    // Diffuse
    float diffuse = Diffuse();
    // Specular
    diffuse += Specular();
    // Attenuation
    diffuse = AddAttenuation(diffuse);
    FragColor = vec4(diffuse, diffuse, diffuse, 1) * lightColor;
    // ambient:
    FragColor += Ambient();
    vec4 texCol = texture(text, uv);
    FragColor += vec4(texCol.r, texCol.g, texCol.b, 0);
}