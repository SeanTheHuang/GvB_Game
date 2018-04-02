#ifndef _SHADER_HELPER__
#define _SHADER_HELPER__

#include <glad\glad.h>

#include <cstring>
#include <string>

class ShaderHelper {
private:
	//static const std::string TAG;

public:
	ShaderHelper();
	static std::string ReadShaderFileFromResource(const char* pFileName);
	static GLuint CompileVertexShader(const char* shaderCode);
	static GLuint CompileFragmentShader(const char* shaderCode);
	static GLuint CompileShader(GLenum ShaderType, const char* shaderCode);
	static GLuint LinkProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
	static GLint ValidateProgram(GLuint programObjectId);
	static void CompileAndLinkShaders(std::string vertex_shader, std::string fragment_shader, GLuint& program);
};

//std::string TAG = "ShaderHelper";
#endif