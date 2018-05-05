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
	// Check with mouse clicks
	if (Input::Instance().GetMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS))
	{
		// Check all buttons
		for (size_t i = 0; i < m_buttons.size(); i++)
		{
			m_buttons[i]->ProcessInteract();
		}
	}

	for (size_t i = 0; i < m_vecPlayers.size(); ++i)
	{
		m_vecPlayers.at(i)->Update();
	}

	static const float32 timeStep = 1.0f / 60.0f;
	static const int32 velocityIterations = 6;
	static const int32 positionIterations = 2;

	if(m_world)
		m_world->Step(timeStep, velocityIterations, positionIterations);

	removeObjects();
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
	// Render UI stuff
	for (size_t i = 0; i < m_sprites.size(); i++)
	{
		m_sprites[i]->Render();
	}
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->Render();
	}
}

void Level::CleanUp()
{
	m_vecPlayers.clear();
	m_vecObjects.clear();
	m_objs.clear();
	m_killList.clear();

	for (size_t i = 0; i < m_sprites.size(); i++)
	{
		delete m_sprites[i];
	}
	m_sprites.clear();

	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		delete m_buttons[i];
	}
	m_buttons.clear();
}
