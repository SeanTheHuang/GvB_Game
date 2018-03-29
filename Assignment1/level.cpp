#include "level.h"

Level::Level()
{
	
}

Level::~Level()
{
	CleanUp();
}

void Level::Update()
{
	
}

void Level::Render()
{
	m_Camera.SendDataToShaders();
	// Render objects
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects.at(i)->DrawObject();
	}
}

void Level::CleanUp()
{
}
