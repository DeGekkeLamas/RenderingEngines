#version 400 core
out vec4 FragColor;
in vec3 fPos;
in vec3 fNor;
in vec2 uv;
uniform vec3 lightPos;
uniform mat4 modelMatrix;

void main()
{
   vec4 usedPos = modelMatrix * normalize(vec4(fPos,0));
   vec4 dir = usedPos - vec4(lightPos,0);
//    float steepness = dot(fNor, dir);
//    FragColor = vec4(steepness, steepness, steepness,1);
//    FragColor = vec4(fNor.x, fNor.y, fNor.z, 1);
   FragColor = vec4(usedPos.x, usedPos.y, usedPos.z,1);
//    FragColor = vec4(dir.x, dir.y, dir.z,1);
}