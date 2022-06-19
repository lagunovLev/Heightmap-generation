#version 330 core

in vec2 texPos;
in vec3 vertex;
in vec4 pos;

uniform sampler2D texture0;
uniform vec3 camera;
uniform vec3 fogColor;

float getFogFactorLinear(float d)
{
    const float FogMax = 300.0;
    const float FogMin = 250.0;

    if (d>=FogMax) return 1.0;
    if (d<=FogMin) return 0.0;

    return 1 - (FogMax - d) / (FogMax - FogMin);
}

void main()
{
    float d = distance(camera, vertex);
    float alpha = getFogFactorLinear(d);
    alpha -= 0.2;
    if (alpha > 1)
        alpha = 1;
    if (alpha < 0)
        alpha = 0;
	vec4 texColor = texture(texture0, texPos);
    gl_FragColor = mix(texColor, vec4(fogColor, 1), alpha);
}