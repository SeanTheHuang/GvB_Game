//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Pyramid.cpp
// Description	: this is the floor object with all relevant functions
// Author		: Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#include "player.h"
#include "level.h"
#include "gamemaster.h"

CPlayer::CPlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index) :
	m_iIndices(0),
	m_shaders(_shaders),
	pTexture(nullptr),
	m_model("Resources/Models/Player/Sphere.obj", _shaders),
	CObject(level)
{
	m_iPlayerIndex = _index;
	m_eModelType = FLOOR;
	m_position = _position;

	getUniformLocation();

	SetPhysics();
}

CPlayer::~CPlayer()
{
	if (pTexture != nullptr)
	{
		delete pTexture;
		pTexture = 0;
	}
}

void CPlayer::SetPhysics()
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(m_position.x, m_position.y);
	m_bodyDef.fixedRotation = true;
	m_body = m_rLevel.addObject(std::unique_ptr<CObject>(this));

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.3f;

	m_body->CreateFixture(&fixtureDef);
}

void CPlayer::DrawObject()
{
	glUseProgram(m_shaders);
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, m_position.z));
	currentTime = static_cast<float>(glfwGetTime());

	glUniformMatrix4fv(gScaleLocation, 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(gRotateLocation, 1, GL_FALSE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(gTranslateLocation, 1, GL_FALSE, glm::value_ptr(Translate));
	glUniform1f(currentTimeLocation, currentTime);

	m_model.Draw();
}

void CPlayer::Update()
{
	PlayerInput();
}

void CPlayer::PlayerInput()
{
	if (Input::Instance().GetPlayerLeft(m_iPlayerIndex))
	{
		m_chargeLeft = true;
		m_chargeAmount += Time::Instance().DeltaTime() * 2;
		m_angle = 45 * (1 + sin(m_chargeAmount));
		std::cout << m_angle << std::endl;
	}
	else if (Input::Instance().GetPlayerRight(m_iPlayerIndex))
	{
		m_chargeRight = true;
		m_chargeAmount += Time::Instance().DeltaTime() * 2;
		m_angle = 45 * (1 + sin(m_chargeAmount));
		std::cout << m_angle << std::endl;
	}
	else
	{
		if (m_chargeLeft && Input::Instance().GetKeyUp(GLFW_KEY_A))
		{
			m_body->ApplyLinearImpulse(b2Vec2(-cos(m_angle * glm::pi<float>() / 180.0f) * m_power, sin(m_angle * glm::pi<float>() / 180.0f)* m_power), m_body->GetPosition(), true);
			m_chargeLeft = false;
			m_angle = 0.0f;
			m_chargeAmount = (glm::pi<float>() * 3.0f) / 2.0f;
		}
		else if (m_chargeRight && Input::Instance().GetKeyUp(GLFW_KEY_D))
		{
			m_body->ApplyLinearImpulse(b2Vec2(cos(m_angle * glm::pi<float>() / 180.0f)* m_power, sin(m_angle * glm::pi<float>() / 180.0f)* m_power), m_body->GetPosition(), true);
			m_chargeRight = false;
			m_angle = 0.0f;
			m_chargeAmount = (glm::pi<float>() * 3.0f) / 2.0f;
		}
	}
}

CPlayer * CPlayer::CreatePlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index)
{
	CPlayer* player = new CPlayer(_shaders, _position, level, _index);
	return player;
}

void CPlayer::getUniformLocation()
{
	gScaleLocation = glGetUniformLocation(m_shaders, "gScale");
	assert(gScaleLocation != 0xFFFFFFFF);

	gRotateLocation = glGetUniformLocation(m_shaders, "gRotate");
	assert(gRotateLocation != 0xFFFFFFFF);

	gTranslateLocation = glGetUniformLocation(m_shaders, "gTranslate");
	assert(gTranslateLocation != 0xFFFFFFFF);

	currentTimeLocation = glGetUniformLocation(m_shaders, "currentTime");
	assert(currentTimeLocation != 0xFFFFFFFF);
}