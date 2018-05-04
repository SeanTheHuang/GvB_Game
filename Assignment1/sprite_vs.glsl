#version 420 core

layout(location = 0) in vec3 a_position;

layout(location = 1) in vec2 a_textureCord;


uniform mat4 gView;
uniform mat4 gOrtho;

out vec2 textureCord;


void main(void)
{
	gl_Position = gOrtho * gView * vec4(a_position, 1.0f);

	textureCord = a_textureCord;

}