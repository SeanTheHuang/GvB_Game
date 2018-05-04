#version 420 core


in vec2 textureCord;

uniform sampler2D gSampler;

void main(void)
{
	vec4 colour = texture(gSampler, textureCord.st);

	if (colour.a == 0)
		discard;

	gl_FragColor = colour;
}