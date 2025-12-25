#version 400 core
out vec4 FragColor;
in vec3 fNor;
in vec2 uv;
uniform sampler2D text;
uniform vec4 registeredColors[20] = {
vec4(1,1,1,1), // Black
vec4(0,0,0,1), // White
vec4(0.498, 0.506, 0.506,1), // Dgray
vec4(0.765, 0.765, 0.765,1), // Lgray
vec4(0.533, 0.09, 0.098,1), // Dred
vec4(0.733, 0.482, 0.345,1), // Brown
vec4(0.925, 0.122, 0.153,1), // Lred
vec4(0.965, 0.675, 0.788,1), // Pink
vec4(0.961, 0.494, 0.173,1), // Orange
vec4(1, 0.792, 0.063,1), // Yellow
vec4(0.973, 0.937, 0.133,1), // Hyellow
vec4(0.933, 0.902, 0.69,1), // Beige
vec4(0.169, 0.698, 0.298,1), // Dgreen
vec4(0.71, 0.827, 0.2,1), // Lime
vec4(0.137, 0.627, 0.855,1), // Blue
vec4(0.6, 0.855, 0.925,1), // Lblue
vec4(0.286, 0.333, 0.647,1), // Dblue
vec4(0.439, 0.573, 0.749,1), // Cyan
vec4(0.631, 0.294, 0.612,1), // Purple
vec4(0.784, 0.749, 0.871,1) // Lpurple
};

vec4 RoundToColor(vec4 color, vec4 compare[20])
{
    int closest = 0;
    float closestDst = 999999;
    for (int i = 0; i < compare.length(); i++)
    {
        float currentDst = length(color - compare[i]);
        if (currentDst < closestDst)
        {
            closestDst = currentDst;
            closest = i;
        }
    }
    return compare[closest];
}

void main()
{
    vec4 texColor = texture(text, uv);
    texColor = RoundToColor(texColor, registeredColors);
    FragColor = texColor;
}