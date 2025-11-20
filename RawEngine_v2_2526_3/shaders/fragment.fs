#version 400 core
out vec4 FragColor;
in vec3 fPos;
in vec3 fNor;
in vec2 uv;
uniform vec3 lightPos;

void main()
{
   vec3 dir = normalize(fPos - lightPos);
   float steepness = dot(dir,fNor);
   FragColor = vec4(steepness, steepness, steepness,1);
//    FragColor = vec4(fNor.x, fNor.y, fNor.z, 1);
//    FragColor = vec4(lightPos.x, lightPos.y, lightPos.z,1);
}