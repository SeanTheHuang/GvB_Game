#include "Arrow.h"


CArrow::CArrow(GLuint _shaders, glm::vec3 _position, Level& level) :
	m_iIndices(0),
	m_shaders(_shaders),
	pTexture(nullptr),
	m_model("Resources/Models/Arrow/Arrow.obj", _shaders),
	CObject(level),
	m_fRotation(0.0f),
	m_fScale(1.0f)
{
	m_eModelType = FLOOR;
	m_position = _position;

	getUniformLocation();
}

CArrow::~CArrow()
{
	if (pTexture != nullptr)
	{
		delete pTexture;
		pTexture = 0;
	}
}

void CArrow::DrawObject()
{
	glUseProgram(m_shaders);
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, m_fScale, m_fScale));
	glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(m_fRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), m_position);
	glUniformMatrix4fv(gScaleLocation, 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(gRotateLocation, 1, GL_FALSE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(gTranslateLocation, 1, GL_FALSE, glm::value_ptr(Translate));

	m_model.Draw();
}

CArrow * CArrow::CreateArrow(GLuint _shaders, glm::vec3 _position, Level& level)
{
	CArrow* arrow = new CArrow(_shaders, _position, level);
	return arrow;
}

void CArrow::SetPosition(glm::vec3 _newPos)
{
	m_position = _newPos;
}

void CArrow::SetRotation(float _newRotation)
{
	m_fRotation = _newRotation;
}

void CArrow::SetScale(float _newScale)
{
	m_fScale = _newScale;
}

void CArrow::getUniformLocation()
{
	gScaleLocation = glGetUniformLocation(m_shaders, "gScale");
	assert(gScaleLocation != 0xFFFFFFFF);

	gRotateLocation = glGetUniformLocation(m_shaders, "gRotate");
	assert(gRotateLocation != 0xFFFFFFFF);

	gTranslateLocation = glGetUniformLocation(m_shaders, "gTranslate");
	assert(gTranslateLocation != 0xFFFFFFFF);
}