#version 400 core
out vec4 FragColor;
in vec3 fPos;
in vec3 fNor;
in vec2 uv;
uniform vec3 lightPos;
uniform vec3 worldPos;

void main()
{
   vec3 usedPos = normalize(fPos) - worldPos;
   vec3 dir = usedPos - lightPos;
   float steepness = dot(fNor, dir);
   FragColor = vec4(steepness, steepness, steepness,1);
//    FragColor = vec4(fNor.x, fNor.y, fNor.z, 1);
//    FragColor = vec4(usedPos.x, usedPos.y, usedPos.z,1);
//    FragColor = vec4(dir.x, dir.y, dir.z,1);
}