#include "Menu.h"


CMenu::CMenu()
{
	// Set menu to active by default
	m_bMenuActive = true;

	// Temporary set to host
	m_EMenuState = MAINMENU;

	m_bLevelLoaded = false;
}


CMenu::~CMenu()
{
	delete m_MainMenuLayout;
	m_MainMenuLayout = 0;

	delete m_LobbyLayout;
	m_LobbyLayout = 0;

	delete m_HowToPlayLayout;
	m_HowToPlayLayout = 0;

	delete m_InGameLayout;
	m_InGameLayout = 0;
	
}

void CMenu::Initialize()
{
	// Main menu GUI
	m_MainMenuLayout = new CGui;
	m_MainMenuLayout->CreateButton(glm::vec3(100, 500, 0), 200, 100, PLAYBTN, "Resources/Images/PlayButton_1.jpg", "Resources/Images/PlayButton_2.jpg", false);
	
	
	// Lobby GUI
	m_LobbyLayout = new CGui;

	// How To Play GUI
	m_HowToPlayLayout = new CGui;

	// How To Play GUI
	//m_AboutLayout = new CGui;

	// InGame GUI
	m_InGameLayout = new CGui;

}

void CMenu::ProcessClick(unsigned char* _keyState, unsigned char* _mouseState, int _mouseX, int _mouseY)
{
	// Point of where mouse clicked
	POINT mousePos;
	mousePos.x = _mouseX;
	mousePos.y = _mouseY;
	
	switch (m_EMenuState)
	{
	case MAINMENU:
		{
			break;
		}
	case LOBBY:
		{
			break;
		}
	case HOW_TO_PLAY:
		{
			break;
		}
	case INGAME:
		{
			break;
		}
	default:
		{
			break;
		}
	}
}

void CMenu::ProcessKey(unsigned char key)
{
	/*if (key == 8 || key == 127)
	{
		if (m_EMenuState == SERVERLIST)
		{
			if (m_strClientName.size() > 0)
			{
				m_strClientName.erase(m_strClientName.end() - 1);
			}
		}
		else if (m_EMenuState == HOSTOPTIONS)
		{
			if (m_strServerName.size() > 0)
			{
				m_strServerName.erase(m_strServerName.end() - 1);
			}
		}
	}
	else
	{
		if (m_EMenuState == SERVERLIST)
		{
			if (m_strClientName.size() < 10)
			{
				m_strClientName += key;
			}
		}
		else if (m_EMenuState == HOSTOPTIONS)
		{
			if (m_strServerName.size() < 10)
			{
				m_strServerName += key;
			}
		}
	}

	if (m_EMenuState == SERVERLIST)
	{
		m_pClientName->setText(m_strClientName);
	}
	else if (m_EMenuState == HOSTOPTIONS)
	{
		m_pServerName->setText(m_strServerName);
	}*/
}

void CMenu::SetBestPlayer(std::string _name, int _score)
{
	/*m_strBestPlayer = _name;
	m_iBestScore = _score;

	if (m_strBestPlayer != "")
	{
		m_GameOverLayout->ChangeText(1, "MVP: " + m_strBestPlayer, glm::vec3(1, 0, 0));
		m_GameOverLayout->ChangeText(2, "Score: " + to_string(m_iBestScore), glm::vec3(1, 0, 0));
	}*/
}

void CMenu::RenderScene()
{

	switch (m_EMenuState)
	{
	case MAINMENU:
	{
		m_MainMenuLayout->Render();
		break;
	}
	case LOBBY:
	{
		m_LobbyLayout->Render();
		break;
	}
	case HOW_TO_PLAY:
	{
		m_HowToPlayLayout->Render();
		break;
	}
	case INGAME:
	{
		m_InGameLayout->Render();
		break;
	}
	default:
	{
		break;
	}
	}
}

bool CMenu::GetActiveState()
{
	return m_bMenuActive;
}

void CMenu::SetActiveState(bool _active)
{
	m_bMenuActive = _active;
}

void CMenu::HideError(bool _bDisplay)
{
	
}

void CMenu::ChangeState(EMenuScreen _newMenuState)
{
	m_EMenuState = _newMenuState;
}
