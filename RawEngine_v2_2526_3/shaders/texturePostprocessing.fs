#version 400 core
out vec4 FragColor;
in vec3 fNor;
in vec2 uv;
uniform sampler2D text;
uniform vec4 outlineCol;

vec4 GetOutline()
{
    float offset = 0.001f;
    vec2 offsets[9] = vec2[ ](
        vec2(-offset, offset), vec2(0.0f, offset), vec2(offset, offset),
        vec2(-offset, 0.0f), vec2(0.0f, 0.0f), vec2( offset, 0.0f),
        vec2(-offset, -offset), vec2(0.0f, -offset), vec2( offset, -offset)
    );
    float kernel[9] = float[ ](
        1.0, 1.0, 1.0,
        1.0, -8.0, 1.0,
        1.0, 1.0, 1.0
    );
    vec4 col = vec4(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += texture(text, uv.st + offsets[i]) * kernel[i];
    }
    col.a = 1.0;
    if (length(clamp(col,0,1).xyz) > 0.05f) {vec4(1,1,1,1);}
    else {return vec4(0,0,0,1);}
//     return col;
}

void main()
{
    FragColor = GetOutline();
    vec4 diffuse = texture(text, uv/* + vec2(0.5f,0.5f)*/);
//  FragColor = vec4(-FragColor.x,-FragColor.y,-FragColor.z, 1);
    FragColor += diffuse;
//  FragColor = vec4(1-diffuse.r, 1-diffuse.g, 1-diffuse.b, 1);
}