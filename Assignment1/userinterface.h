#pragma once
#include "include.h"

class CUi
{
public:
	CUi();
	~CUi();
	virtual void Render() = 0;
	virtual void setPosition(glm::vec3 _position);
	virtual bool Initialise() = 0;
	virtual void ProcessInteract();

	void setScale(GLfloat _scale);

	bool IsInteractive();

	static glm::vec2 PixelToScreenPosition(glm::vec2 _position);

protected:
	glm::vec3 m_position;
	glm::vec2 m_width_height;
	GLfloat m_scale;
	GLuint m_program;
	GLuint m_VBO;
	GLuint m_VAO;

	bool m_isInteractive;
};