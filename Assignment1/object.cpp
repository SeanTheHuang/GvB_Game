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
	default:
		break;
	}

	return nullptr;
}

ModelType CObject::GetModelType()
{
	return m_eModelType;
}
