//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Model.h
// Description	: this is a factory class that creates several types of models
// Author		: Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <assert.h>

#include "include.h"
#include "texture.h"

class Level;

class CObject
{
public:
	virtual ~CObject();

	// Creates a model based on the input
	// Takes what type of model to create, what shaders the object shuld use and its position in world space
	// Returns the created model
	static CObject* CreateObject(ModelType _modelType, GLuint _shaders, glm::vec3 _position, Level& level);
	// Sends the necessary data to the shaders for them to draw the model
	virtual void DrawObject() = 0;
	virtual void Update();
	ModelType GetModelType();
	// A get function for the models position
	// Returns the position in the form of a glm::vec3
	glm::vec3 GetPosition();
	const b2BodyDef& getBodyDef() const;
	b2Body& getBody();

protected:
	CObject(Level& level);

	glm::vec3 m_position;
	glm::vec3 m_rotation;

	ModelType m_eModelType;

	b2Body* m_body;
	b2BodyDef m_bodyDef;
	Level& m_rLevel;
};

#endif //__MODEL_H__