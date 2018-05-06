#pragma once

#include "level.h"
#include "Box2D\Box2D.h"

class GameLevel1 : public Level
{
public:
	//Fill level with objects. Initialize all objects
	void Initialize(std::vector<Player> _players);
	//Update all objects. Apply level logic
	void Update();
};