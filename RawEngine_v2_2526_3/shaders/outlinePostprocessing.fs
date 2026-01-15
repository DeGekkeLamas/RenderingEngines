#version 400 core
out vec4 FragColor;
in vec3 fNor;
in vec2 uv;
uniform sampler2D text;
uniform vec4 outlineCol;

vec4 GetOutline()
{
    float offset = 0.003f;
    vec2 offsets[9] = vec2[ ](
        vec2(-offset, offset), vec2(0.0f, offset), vec2(offset, offset),
        vec2(-offset, 0.0f), vec2(0.0f, 0.0f), vec2( offset, 0.0f),
        vec2(-offset, -offset), vec2(0.0f, -offset), vec2( offset, -offset)
    );
    float kernel[9] = float[ ](
        1.0, 1.0, 1.0,
        1.0, -10.0, 1.0,
        1.0, 1.0, 1.0
    );
    vec4 col = vec4(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += texture(text, uv.st + offsets[i]) * kernel[i];
    }
    col.a = 1.0;

    return clamp(col,0,1);
}

void main()
{
//     uv += vec2(0.5f,0.5f);
    vec4 outline = GetOutline();
    if (length(outline.xyz) > 0.05f )
    {
        FragColor = outlineCol;
    }
    else
    {
        FragColor += texture(text, uv);
    }
}