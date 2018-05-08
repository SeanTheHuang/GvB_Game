#version 420 core


in vec2 textureCord;
in vec3 outColor;

uniform sampler2D gSampler;
uniform vec3 gColor;


void main(void)
{
	vec4 colour = texture(gSampler, textureCord.st) * vec4(gColor, 1);

	if (colour.a <= 0.5)
		discard;

	gl_FragColor = colour;
}