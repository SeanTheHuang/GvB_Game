#version 420 core

in vec3 outColor;
in vec2 textureCord;

uniform sampler2D gSampler;

void main(void)
{
	gl_FragColor = vec4(0.1f.xxx, 1.0f);
}