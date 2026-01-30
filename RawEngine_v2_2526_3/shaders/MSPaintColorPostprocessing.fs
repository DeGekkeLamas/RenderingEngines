#version 400 core
out vec4 FragColor;
in vec3 fNor;
in vec2 uv;
uniform sampler2D text;
uniform sampler2D colorTexture;
uniform int colorQTY;

float max(float x, float y, float z)
{
    float xyMax = max(x, y);
    return max(xyMax, z);
}
float min(float x, float y, float z)
{
    float xyMin = min(x, y);
    return min(xyMin, z);
}
float getValue(vec4 color)
{
    return max(color.x, color.y, color.z);
}
float getSaturation(vec4 color)
{
    float cMax = getValue(color);
    float cMin = min(color.x, color.y, color.z);
    return (cMax - cMin) / cMax;
}
float getHue(vec4 color)
{
    float cMax = getValue(color);
    float cMin = min(color.x, color.y, color.z);
    float result = 0;
    if (cMax == color.x) {
        result = (color.y - color.z) / (cMax - cMin);
    } else if (cMax == color.y){
        result = (color.y - color.x) / (cMax - cMin);
    } else if (cMax == color.z){
        result = (color.x - color.y) / (cMax - cMin);
    }
    return result * 60;
}
vec3 getHSV(vec4 color){
    return vec3(getHue(color)/360, getSaturation(color), getValue(color));
}

vec4 RoundToColor(vec4 color, sampler2D colorTex)
{
    int closest = 0;
    float closestDst = 999999;

    vec4 exp = vec4(.5f,.5f,.5f,1);
    // Compensate for the registered colors mostly being high value colors
    vec4 usedCol = color;
//     usedCol = vec4(getHSV(usedCol), 1);
    usedCol = pow(usedCol, exp);
    for (int i = 0; i < colorQTY; i++)
    {
           float pos = (float(i) + 0.5f) / float(colorQTY);
           vec4 usedCompare = texture(colorTex, vec2(pos, 0.5));
//         usedCompare = vec4(getHSV(usedCompare), 1);
//         usedCompare = pow(usedCompare, exp);

        float currentDst = length(usedCol - usedCompare);
        if (currentDst < closestDst)
        {
            closestDst = currentDst;
            closest = i;
        }
    }
    float x = (float(closest) + 0.5) / float(colorQTY);
    return texture(colorTex, vec2(x, 0.5));
}

void main()
{
    vec4 texColor = texture(text, uv);
    texColor = RoundToColor(texColor, colorTexture);
    FragColor = texColor;
}