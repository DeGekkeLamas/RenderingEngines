#version 400 core
out vec4 FragColor;
in vec3 fPos; // world
in vec3 fNor; // world
in vec2 uv;
uniform vec3 lightPos; // probably world space

// IF you add the string replacement code, you could do this:
//#include lighting.glsl

void main()
{
    // issues:
   // usedPos is in world space
    vec3 dir = lightPos - fPos.xyz; // world space
    float steepness = dot(normalize(fNor), normalize(dir)); // different spaces!
    steepness = max(steepness, 0);
    FragColor = vec4(steepness, steepness, steepness,1);
    // hard coded ambient:
    FragColor += vec4(0,0,0.3,0);
}