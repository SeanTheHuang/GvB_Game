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

CPlayer::CPlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index, glm::vec3 _color) :
	m_iIndices(0),
	m_shaders(_shaders),
	pTexture(nullptr),
	m_model("Resources/Models/Player/Sphere.obj", _shaders),
	CObject(level),
	m_iHealth(3),
	m_fRadius(1.0f),
	m_isAlive(true),
	m_power(0.35f),
	m_baseColor(_color),
	m_hitCooldown(0.0f)
{
	m_creviceColor = glm::vec3(0, 0, 0);
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
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.4f;

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
	glUniform3f(baseColorLocation, m_baseColor.x, m_baseColor.y, m_baseColor.z);
	glUniform3f(creviceColorLocation, m_creviceColor.x, m_creviceColor.y, m_creviceColor.z);
	glUniform2f(velocityLocation, m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);


	m_model.Draw();

	if (m_chargeLeft || m_chargeRight)
	{
		arrow->DrawObject();
	}
}

void CPlayer::Update()
{
	m_hitCooldown -= Time::Instance().DeltaTime();
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
	if (Input::Instance().GetPlayerLeft(m_iPlayerIndex) && m_body->GetLinearVelocity().Length() == 0.0f)
	{
		if (m_angle == 0.0f)
			CAudio::PlaySound("charge",true);

		m_chargeLeft = true;
		m_chargeAmount += Time::Instance().DeltaTime() * 3;
		m_angle = 10 + 40 * (1 + sin(m_chargeAmount));
		std::cout << m_angle << std::endl;
	}
	else if (Input::Instance().GetPlayerRight(m_iPlayerIndex) && m_body->GetLinearVelocity().Length() == 0.0f)
	{
		if (m_angle == 0.0f)
			CAudio::PlaySound("charge",true);

		m_chargeRight = true;
		m_chargeAmount += Time::Instance().DeltaTime() * 3;
		m_angle = 10 + 40 * (1 + sin(m_chargeAmount));
		std::cout << m_angle << std::endl;
	}
	else
	{
		if (m_chargeLeft && !Input::Instance().GetPlayerLeft(m_iPlayerIndex))
		{
			CAudio::PlaySound("jump",true);

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
			CAudio::PlaySound("jump",true);

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

CPlayer * CPlayer::CreatePlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index, glm::vec3 _color)
{
	CPlayer* player = new CPlayer(_shaders, _position, level, _index, _color);
	return player;
}

void CPlayer::Collide(b2Body & otherPlayerBody)
{
	if (otherPlayerBody.GetPosition().y > m_body->GetPosition().y + m_body->GetFixtureList()[0].GetShape()->m_radius/3.0f && m_hitCooldown <= 0.0f)
	{
		ReduceHealth();
		CAudio::PlaySound("hit",true);
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

int CPlayer::GetIndex()
{
	return m_iPlayerIndex;
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

	baseColorLocation = glGetUniformLocation(m_shaders, "baseColor");
	assert(baseColorLocation != 0xFFFFFFFF);

	creviceColorLocation = glGetUniformLocation(m_shaders, "creviceColor");
	assert(creviceColorLocation != 0xFFFFFFFF);

	velocityLocation = glGetUniformLocation(m_shaders, "velocity");
	assert(velocityLocation != 0xFFFFFFFF);
}

void CPlayer::ReduceHealth()
{
	m_hitCooldown = 0.5f;
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
