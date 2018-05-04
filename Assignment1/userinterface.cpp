#include "userinterface.h"

CUi::CUi()
{
	m_scale = 1.0f;
}

CUi::~CUi()
{

}

void CUi::setPosition(glm::vec3 _position)
{
	m_position = _position;
}

void CUi::ProcessInteract()
{
}

void CUi::setScale(GLfloat _scale)
{
	m_scale = _scale;
}

bool CUi::IsInteractive()
{
	return m_isInteractive;
}

glm::vec2 CUi::PixelToScreenPosition(glm::vec2 _position)
{
	glm::vec2 result;

	result.x = ((_position.x / WINDOW_WIDTH) * 2) - 1;
	result.y = ((_position.y / WINDOW_HEIGHT) * 2) - 1;

	return result;
}
