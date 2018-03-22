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
	//Update Entities
	for (size_t i = 0; i < m_vecEntity.size(); i++)
	{
		m_vecEntity[i]->Update();
	}

	//Update Quads
	for (size_t i = 0; i < m_vecQuads.size(); i++)
	{
		m_vecQuads[i]->Update();
	}

	
}

void Level::Render()
{
	//Render Entities
	for (size_t i = 0; i < m_vecEntity.size(); i++)
	{
		m_vecEntity[i]->Render();
	}

	//Render transparent quads
	for (size_t i = 0; i < m_vecQuads.size(); i++)
	{
		m_vecQuads[i]->Render();
	}
}

void Level::CleanUp()
{
	if (m_pCamera)
		delete m_pCamera;

	//Delete Entities
	for (size_t i = 0; i < m_vecEntity.size(); i++)
	{
		delete m_vecEntity[i];
	}
	m_vecEntity.clear();

	//Delete Quads
	for (size_t i = 0; i < m_vecQuads.size(); i++)
	{
		delete m_vecQuads[i];
	}
	m_vecQuads.clear();
}

void Level::AddEntity(Entity* _newEntity)
{
	m_vecEntity.push_back(_newEntity);
}

void Level::AddQuad(Quad* _newQuad)
{
	m_vecQuads.push_back(_newQuad);
}
