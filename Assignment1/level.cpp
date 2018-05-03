#include "level.h"

const float Level::s_kPixelsPerMeter = 32.0f;
const float Level::s_kGravity = -10.0f; // adjust this to taste


Level::Level()
{
	
}

Level::~Level()
{
	CleanUp();
}

void Level::Update()
{
	for (size_t i = 0; i < m_vecPlayers.size(); ++i)
	{
		m_vecPlayers.at(i)->Update();
	}

	static const float32 timeStep = 1.0f / 60.0f;
	static const int32 velocityIterations = 6;
	static const int32 positionIterations = 2;

	m_world->Step(timeStep, velocityIterations, positionIterations);
}

b2Body* Level::addObject(std::unique_ptr<CObject> obj)
{
	b2Body* body = m_world->CreateBody(&obj->getBodyDef());
	m_objs.push_back(std::move(obj));

	return body;
}

void Level::removeObjects()
{
	if (m_killList.size() != 0)
	{
		for (auto& kill : m_killList)
		{
			m_world->DestroyBody(&kill->getBody());
			m_objs.erase(std::remove_if(m_objs.begin(), m_objs.end(),
				[kill](std::unique_ptr<CObject> &obj) {return obj.get() == kill; }),
				m_objs.end());

			kill = nullptr;
		}

		m_killList.clear();
	}
}

void Level::addToKillList(CObject* toKill)
{
	m_killList.push_back(toKill);
}

void Level::Render()
{
	m_Camera.SendDataToShaders();
	// Render objects
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects.at(i)->DrawObject();
	}
	for (size_t i = 0; i < m_vecPlayers.size(); ++i)
	{
		m_vecPlayers.at(i)->DrawObject();
	}
}

void Level::CleanUp()
{
}
