//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Model.cpp
// Description	: this is a factory class that creates ceveral types of models
// Author		: Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#include "Object.h"
#include "Skybox.h"
#include "Floor.h"
#include "Cuboid.h"
#include "level.h"
#include "player.h"
#include "Arrow.h"
#include "Platform.h"
#include "Pillar.h"
#include "Ground.h"
#include "Wall.h"

CObject::~CObject()
{
}

glm::vec3 CObject::GetPosition()
{
	return m_position;
}

const b2BodyDef & CObject::getBodyDef() const
{
	return m_bodyDef;
}

b2Body & CObject::getBody()
{
	return *m_body;
}

CObject::CObject(Level& level)
	:
	m_rLevel(level)
{

}

CObject* CObject::CreateObject(ModelType _modelType, GLuint _shaders, glm::vec3 _position, Level& level)
{
	CObject* model;
	switch (_modelType)
	{
	case SKYBOX:
		model = CSkybox::CreateSkybox(_shaders, _position, level);
		return model;
		break;
	case FLOOR:
		model = CFloor::CreateFloor(_shaders, _position, level);
		return model;
		break;
	case CUBOID:
		model = CCuboid::CreateCuboid(_shaders, _position, level);
		return model;
		break;
	case PLAYER:
		model = CPlayer::CreatePlayer(_shaders, _position, level, 0, glm::vec3(1,1,1));
		return model;
		break;
	case ARROW:
		model = CArrow::CreateArrow(_shaders, _position, level);
		return model;
	case PLATFORM:
		model = CPlatform::CreatePlatform(_shaders, _position, level);
		return model;
	case PILLAR:
		model = CPillar::CreatePillar(_shaders, _position, level);
		return model;
		break;
	case GROUND:
		model = CGround::CreateGround(_shaders, _position, level);
		return model;
	case WALL:
		model = CWall::CreateWall(_shaders, _position, level);
		return model;
		break;
	default:
		break;
	}

	return nullptr;
}

void CObject::Update()
{
}

ModelType CObject::GetModelType()
{
	return m_eModelType;
}
