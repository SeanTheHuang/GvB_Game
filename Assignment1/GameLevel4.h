#pragma once

#include "level.h"
#include "Box2D\Box2D.h"

class GameLevel4 : public Level
{
public:
	//Fill level with objects. Initialize all objects
	void Initialize();
	//Update all objects. Apply level logic
	void Update();
};