#pragma once

#include "include.h"
#include "level.h"

class MainMenuLevel : public Level
{
	// Member Functions
public:
	void Initialize(std::vector<Player> _players);
	void CleanUp();
	void Update();

protected:


	// Member Variables
protected:

};