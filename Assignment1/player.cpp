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
#include <iostream>

#include "player.h"
#include "level.h"
#include "gamemaster.h"
#include "audio.h"
#include "Arrow.h"

CPlayer::CPlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index) :
	m_iIndices(0),
	m_shaders(_shaders),
	pTexture(nullptr),
	m_model("Resources/Models/Player/Sphere.obj", _shaders),
	CObject(level),
	m_iHealth(3),
	m_fRadius(1.0f),
	m_isAlive(true)
{
	m_iPlayerIndex = _index;
	m_eModelType = PLAYER;
	m_position = _position;

	getUniformLocation();

	SetPhysics();

	Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

CPlayer::~CPlayer()
{
	if (pTexture != nullptr)
	{
		delete pTexture;
		pTexture = 0;
	}
	if (arrow != nullptr)
	{
		delete arrow;
		arrow = 0;
	}
}

void CPlayer::SetPhysics()
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(m_position.x/ Level::s_kPixelsPerMeter, m_position.y/ Level::s_kPixelsPerMeter);
	m_bodyDef.fixedRotation = true;
	m_body = m_rLevel.addObject(std::unique_ptr<CObject>(this));

	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = m_fRadius / Level::s_kPixelsPerMeter;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 1.1666666f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.6f;

	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}

void CPlayer::DrawObject()
{
	glUseProgram(m_shaders);
	glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(m_fRadius* Level::s_kPixelsPerMeter, m_fRadius* Level::s_kPixelsPerMeter, m_fRadius* Level::s_kPixelsPerMeter));
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x * Level::s_kPixelsPerMeter, m_position.y * Level::s_kPixelsPerMeter, m_position.z));
	currentTime = static_cast<float>(glfwGetTime());

	glUniformMatrix4fv(gScaleLocation, 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(gRotateLocation, 1, GL_FALSE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(gTranslateLocation, 1, GL_FALSE, glm::value_ptr(Translate));
	glUniform1f(currentTimeLocation, currentTime);

	m_model.Draw();

	if (m_chargeLeft || m_chargeRight)
	{
		arrow->DrawObject();
	}
}

void CPlayer::Update()
{
	PlayerInput();
	m_position = glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, m_position.z);

	arrow->SetPosition(glm::vec3(m_position.x * Level::s_kPixelsPerMeter, m_position.y * Level::s_kPixelsPerMeter, m_position.z));
	if (m_chargeRight)
	{
		arrow->SetRotation(m_angle);
	}
	else if (m_chargeLeft)
	{
		arrow->SetRotation(180.0f - m_angle);
	}
}

void CPlayer::PlayerInput()
{
	if (Input::Instance().GetPlayerLeft(m_iPlayerIndex))
	{
		if (m_angle == 0.0f)
			CAudio::PlaySound("charge");

		m_chargeLeft = true;
		m_chargeAmount += Time::Instance().DeltaTime() * 2;
		m_angle = 45 * (1 + sin(m_chargeAmount));
		std::cout << m_angle << std::endl;
	}
	else if (Input::Instance().GetPlayerRight(m_iPlayerIndex))
	{
		if (m_angle == 0.0f)
			CAudio::PlaySound("charge");

		m_chargeRight = true;
		m_chargeAmount += Time::Instance().DeltaTime() * 2;
		m_angle = 45 * (1 + sin(m_chargeAmount));
		std::cout << m_angle << std::endl;
	}
	else
	{
		if (m_chargeLeft && !Input::Instance().GetPlayerLeft(m_iPlayerIndex))
		{
			CAudio::PlaySound("jump");

			m_body->ApplyLinearImpulse(b2Vec2(
				(-cos(m_angle * glm::pi<float>() / 180.0f) * m_power) / Level::s_kPixelsPerMeter,
				(sin(m_angle * glm::pi<float>() / 180.0f)* m_power) / Level::s_kPixelsPerMeter), 
				m_body->GetPosition(), true);
			m_chargeLeft = false;
			m_angle = 0.0f;
			m_chargeAmount = (glm::pi<float>() * 3.0f) / 2.0f;
		}
		else if (m_chargeRight && !Input::Instance().GetPlayerRight(m_iPlayerIndex))
		{
			CAudio::PlaySound("jump");

			m_body->ApplyLinearImpulse(b2Vec2(
				(cos(m_angle * glm::pi<float>() / 180.0f) * m_power) / Level::s_kPixelsPerMeter,
				(sin(m_angle * glm::pi<float>() / 180.0f)* m_power) / Level::s_kPixelsPerMeter),
				m_body->GetPosition(), true);
			m_chargeRight = false;
			m_angle = 0.0f;
			m_chargeAmount = (glm::pi<float>() * 3.0f) / 2.0f;
		}
	}
}

bool CPlayer::GetIsAlive()
{
	return m_isAlive;
}

CPlayer * CPlayer::CreatePlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index)
{
	CPlayer* player = new CPlayer(_shaders, _position, level, _index);
	return player;
}

void CPlayer::Collide(b2Body & otherPlayerBody)
{
	if (otherPlayerBody.GetPosition().y > m_body->GetPosition().y + m_body->GetFixtureList()[0].GetShape()->m_radius/3.0f)
	{
		ReduceHealth();
		CAudio::PlaySound("hit");
	}
	else
	{
		m_body->ApplyLinearImpulse(b2Vec2(0.0f, -m_body->GetLinearVelocity().y / 120.0f), m_body->GetWorldCenter(), true);
	}
}

void CPlayer::SetPosition(glm::vec3 newPos)
{
	m_position = newPos;
	m_body->SetTransform(b2Vec2(newPos.x, newPos.y), m_body->GetAngle());
}

void CPlayer::SetArrow(CArrow * _arrow)
{
	arrow = _arrow;
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

void CPlayer::ReduceHealth()
{
	m_iHealth--;

	m_body->GetFixtureList()[0].GetShape()->m_radius = (static_cast<float>(m_iHealth) / 3.0f) * (m_fRadius / Level::s_kPixelsPerMeter);
	float newScale = static_cast<float>(m_iHealth) / 3.0f;
	Scale = glm::scale(glm::mat4(1.0f), glm::vec3(newScale, newScale, newScale));
	arrow->SetScale(newScale);
	std::cout << "Player: " << m_iPlayerIndex << "I got damaged and my health is " << m_iHealth << std::endl;

	if (m_iHealth <= 0)
	{
		m_isAlive = false;
	}
}
