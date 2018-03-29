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

CObject::~CObject()
{
}

glm::vec3 CObject::GetPosition()
{
	return m_position;
}

CObject::CObject()
{

}

CObject* CObject::CreateObject(ModelType _modelType, GLuint _shaders, glm::vec3 _position)
{
	CObject* model;
	switch (_modelType)
	{
	case SKYBOX:
		model = CSkybox::CreateSkybox(_shaders, _position);
		return model;
		break;
	case FLOOR:
		model = CFloor::CreateFloor(_shaders, _position);
		return model;
		break;
	case CUBOID:
		model = CCuboid::CreateCuboid(_shaders, _position);
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
