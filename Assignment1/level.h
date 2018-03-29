#pragma once

#include "include.h"
#include "camera.h"
#include "entity.h"
#include "quad.h"
#include "shaderhelper.h"
#include "object.h"
#include "Utils.h"

class Level
{
//== Methods
public:
	Level();
	~Level();

	//Fill level with objects. Initialize all objects
	virtual void Initialize() = 0;
	//Destroy all objects
	virtual void CleanUp();
	//Update all objects. Apply level logic
	virtual void Update();
	//Render all objects
	virtual void Render();

protected:
	Level(const Level&) = delete;
	void operator=(Level const&) = delete;

//== Members
protected:
	CCamera m_Camera;
	std::vector<GLuint> m_vecShaders;
	std::vector<CObject*> m_vecObjects;
};