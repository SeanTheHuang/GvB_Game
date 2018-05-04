#version 420 core


in vec2 textureCord;

uniform sampler2D gSampler;

void main(void)
{
	gl_FragColor = texture(gSampler, textureCord.st);

}