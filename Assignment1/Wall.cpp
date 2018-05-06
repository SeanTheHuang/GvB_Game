#include "Wall.h"


CWall::CWall(GLuint _shaders, glm::vec3 _position, Level& level) :
	m_iIndices(0),
	m_shaders(_shaders),
	pTexture(nullptr),
	m_model("Resources/Models/Pillar/Pillar.obj", _shaders),
	CObject(level)
{
	m_eModelType = FLOOR;
	m_position = _position;

	getUniformLocation();

	SetPhysics();
}

CWall::~CWall()
{
	if (pTexture != nullptr)
	{
		delete pTexture;
		pTexture = 0;
	}
}

void CWall::SetPhysics()
{
	m_bodyDef.type = b2_kinematicBody;
	m_bodyDef.position.Set(m_position.x / Level::s_kPixelsPerMeter, m_position.y / Level::s_kPixelsPerMeter);
	m_body = m_rLevel.addObject(std::unique_ptr<CObject>(this));

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f / Level::s_kPixelsPerMeter, 16.0f / Level::s_kPixelsPerMeter);	// The pillars dimentions are 2 by 4 units

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.5f;

	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

void CWall::DrawObject()
{
	glUseProgram(m_shaders);
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 8.0f, 1.0f));
	glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f* Level::s_kPixelsPerMeter, 1.0f* Level::s_kPixelsPerMeter, 1.0f* Level::s_kPixelsPerMeter));
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_body->GetPosition().x * Level::s_kPixelsPerMeter, m_body->GetPosition().y * Level::s_kPixelsPerMeter, m_position.z));
	glUniformMatrix4fv(gScaleLocation, 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(gRotateLocation, 1, GL_FALSE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(gTranslateLocation, 1, GL_FALSE, glm::value_ptr(Translate));

	m_model.Draw();
}

CWall * CWall::CreateWall(GLuint _shaders, glm::vec3 _position, Level& level)
{
	CWall* wall = new CWall(_shaders, _position, level);
	return wall;
}

void CWall::getUniformLocation()
{
	gScaleLocation = glGetUniformLocation(m_shaders, "gScale");
	assert(gScaleLocation != 0xFFFFFFFF);

	gRotateLocation = glGetUniformLocation(m_shaders, "gRotate");
	assert(gRotateLocation != 0xFFFFFFFF);

	gTranslateLocation = glGetUniformLocation(m_shaders, "gTranslate");
	assert(gTranslateLocation != 0xFFFFFFFF);
}
