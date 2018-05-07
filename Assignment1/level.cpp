#include "level.h"

const float Level::s_kPixelsPerMeter = 32.0f;
const float Level::s_kGravity = -10.0f; // adjust this to taste


Level::Level()
{
	for (int i = 0; i < m_buttons.size(); i++)
		m_inputDelayStamps[i] = Time::Instance().TotalTime();
}

Level::~Level()
{
	CleanUp();
}

void Level::CheckControllerSelect()
{
	for (int i = 0; i < 4; i++)
	{
		if (Time::Instance().TotalTime() > m_inputDelayStamps[i] + m_delayLength && Input::Instance().GetControllerInputDown(i, JOYSTICK_A))
		{
			// Check all buttons
			for (size_t j = 0;j < m_buttons.size(); j++)
			{
				if (m_buttons[j] && i == m_buttons[j]->GetPlayerUsedBy())
				{
					m_buttons[j]->ProcessInteract();

				}
			}

			m_inputDelayStamps[i] = Time::Instance().TotalTime();
		}
	}
}

void Level::CheckMouseSelect()
{
	if (Time::Instance().TotalTime() > m_inputDelayStamps[0] + m_delayLength && (Input::Instance().GetMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) || Input::Instance().GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS)))
	{
		// Check all buttons
		for (size_t j = 0; j < m_buttons.size(); j++)
		{
			if (m_buttons[j])
			{
				m_buttons[j]->ProcessInteract();
			}

		}

		m_inputDelayStamps[0] = Time::Instance().TotalTime();
	}
}

void Level::FindNextButton(int _playerIdx, int _direction)
{
	for (int i = m_highlights[_playerIdx] + _direction; (_direction > 0) ? i < m_buttons.size() : i >= 0; i+= _direction)
	{
		if (m_buttons[i] && m_buttons[i]->GetPlayerUsedBy() == _playerIdx)
		{
			m_highlights[_playerIdx] = i;
			return;
		}
	}
}

void Level::CheckControllerScroll()
{
	for (int i = 0; i < 4; i++)
	{
		int axes = Input::Instance().GetControllerAxes(i, 1) * -1;
		if (m_buttons.size() > 0 && Time::Instance().TotalTime() > m_inputDelayStamps[i] + m_delayLength && (axes > 0.25f || axes < -0.25f))
		{
			if (m_buttons[m_highlights[i]])
				m_buttons[m_highlights[i]]->UpdateHighlight(false);

			FindNextButton(i, axes);

			if (m_buttons[m_highlights[i]])
				m_buttons[m_highlights[i]]->UpdateHighlight(true);

			m_inputDelayStamps[i] = Time::Instance().TotalTime();
		}
	}
}


void Level::Update()
{
	// Check with mouse clicks
	CheckControllerSelect();
	CheckMouseSelect();
	CheckControllerScroll();
	// Player 1 can only control menu (prevent trolling here)
	

	for (size_t i = 0; i < m_vecPlayers.size(); ++i)
	{
		m_vecPlayers.at(i)->Update();
	}

	static const float32 timeStep = 1.0f / 90.0f;
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
		if (m_sprites[i])
			m_sprites[i]->Render();
	}
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		if(m_buttons[i])
			m_buttons[i]->Render();
	}

	for (size_t i = 0; i < m_texts.size(); i++)
	{
		if (m_texts[i])
			m_texts[i]->Render();
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

	for (size_t i = 0; i < m_texts.size(); i++)
	{
		delete m_texts[i];
	}
	m_texts.clear();
}
