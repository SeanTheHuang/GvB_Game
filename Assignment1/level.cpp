#include "level.h"

const float Level::s_kPixelsPerMeter = 32.0f;
const float Level::s_kGravity = -10.0f; // adjust this to taste


Level::Level()
{
	for (size_t i = 0; i < m_buttons.size(); i++)
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
		if (Time::Instance().TotalTime() > m_inputDelayStamps[i] + m_delayLength && Input::Instance().GetControllerInputA(i))
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
	for (int i = m_highlights[_playerIdx] + _direction; (_direction > 0) ? i < (int)m_buttons.size() : i >= 0; i+= _direction)
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
		int axes = (int)Input::Instance().GetControllerAxes(i, 1) * -1;
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

void Level::CheckPause()
{
	if (Input::Instance().GetKeyDown(GLFW_KEY_ESCAPE) && m_vecPlayers.size() != 0)
	{
		SetIsPaused(!GetIsPaused());
		if (GetIsPaused())
		{
			CSprite* pbackground = new CSprite("Resources/Images/PauseScreenBackground.jpg", glm::vec2(0, 0), glm::vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
			m_sprites.push_back(pbackground);
			CButtonUI* QuitButton = new CButtonUI("Resources/Images/QuitButton_1.png", "Resources/Images/QuitButton_2.png",
				glm::vec2((WINDOW_WIDTH / 2) - 62.5f, (WINDOW_HEIGHT / 2) - 30.0f), glm::vec2(125, 60), QUIT_TO_MENU_BTN, 0);
			m_buttons.push_back(QuitButton);
		}
		else
		{
			m_sprites.clear();
			m_buttons.clear();
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
	CheckPause();

	if (!GetIsPaused())
	{
		for (size_t i = 0; i < m_vecPlayers.size(); ++i)
		{
			m_vecPlayers.at(i)->Update();
		}

		static float32 timeStep = 1.0f / 90.0f;
		static const int32 velocityIterations = 6;
		static const int32 positionIterations = 2;
		const int maxUpdatesPerFrame = 5;


		m_accumulator += Time::Instance().DeltaTime();
		if (m_accumulator > (maxUpdatesPerFrame * timeStep)) {
			m_accumulator = timeStep;
		}

		if (m_world)
		{
			while (m_accumulator >= timeStep)
			{
				m_world->Step(timeStep, velocityIterations, positionIterations);
				m_accumulator -= timeStep;
			}
		}
		removeObjects();
	}
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

bool Level::GetIsPaused()
{
	return m_isPaused;
}

void Level::SetIsPaused(bool _pause)
{
	m_isPaused = _pause;
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
