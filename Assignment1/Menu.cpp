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

	delete m_ServerListLayout;
	m_ServerListLayout = 0;

	delete m_ServerNameLayout;
	m_ServerNameLayout = 0;

	delete m_ControlLayout;
	m_ControlLayout = 0;

//	delete m_pClientName;
	//m_pClientName = 0;

//	delete m_pServerName;
	//m_pServerName = 0;
	
	delete m_GameOverLayout;
	m_GameOverLayout = 0;
}

void CMenu::Initialize()
{
	// Main menu GUI
	m_MainMenuLayout = new CGui;
	m_MainMenuLayout->CreateButton(glm::vec3(400, 500, 0), 300, 100, HOSTNAMESELECT, "Textures/HostBtnDown.png", "Textures/HostBtnUp.png", false);
	m_MainMenuLayout->CreateButton(glm::vec3(400, 400, 0), 300, 100, SERVERLISTBTN, "Textures/JoinBtnDown.png", "Textures/JoinBtnUp.png", false);
	m_MainMenuLayout->CreateButton(glm::vec3(400, 300, 0), 300, 100, CONTROLSBTN, "Textures/ControlsBtnDown.png", "Textures/ControlsBtnUp.png", false);
	m_MainMenuLayout->CreateButton(glm::vec3(400, 200, 0), 300, 100, QUITBTN, "Textures/QuitBtnDown.png", "Textures/QuitBtnUp.png", false);
	m_MainMenuLayout->CreateText(glm::vec2(225, 650), 2.0f, glm::vec3(1, 1, 1), "Tronic", false);
	m_MainMenuLayout->CreateText(glm::vec2(225, 50), 0.75f, glm::vec3(1, 1, 1), "By Axon Warriors", false);


	// Server list GUI
	m_ServerListLayout = new CGui;
	m_ServerListLayout->CreateButton(glm::vec3(600, 100, 0), 300, 100, REFRESHSERVERS, "Textures/RefreshBtnDown.png", "Textures/RefreshBtnUp.png", false);
	m_ServerListLayout->CreateButton(glm::vec3(200, 100, 0), 300, 100, HOMEBTN, "Textures/BackBtnDown.png", "Textures/BackBtnUp.png", false);

	m_ServerListLayout->CreateText(glm::vec2(50, 0), 1.0f, glm::vec3(1, 1, 1), "Name: ", false);
	m_ServerListLayout->CreateText(glm::vec2(0, 775), 0.5f, glm::vec3(1, 0, 0), "Username/connection not unique!", true);

	// Server name select gui
	m_ServerNameLayout = new CGui;
	m_ServerNameLayout->CreateText(glm::vec2(75, 700), 0.75f, glm::vec3(1, 1, 1), "Name", false);
	m_ServerNameLayout->CreateButton(glm::vec3(200, 100, 0), 300, 100, HOMEBTN, "Textures/BackBtnDown.png", "Textures/BackBtnUp.png", false);
	m_ServerNameLayout->CreateButton(glm::vec3(600, 100, 0), 300, 100, HOSTBTN, "Textures/CreateBtnDown.png", "Textures/CreateBtnUp.png", false);

	// Controls screen GUI
	m_ControlLayout = new CGui;
	m_ControlLayout->CreateText(glm::vec2(150, 650), 2.0f, glm::vec3(1, 1, 1), "CONTROLS", false);
	m_ControlLayout->CreateButton(glm::vec3(400, 400, 0), 700, 400, NONE, "Textures/KeyboardLayout.png", "Textures/KeyboardLayout.png", false);
	m_ControlLayout->CreateButton(glm::vec3(600, 100, 0), 300, 100, HOMEBTN, "Textures/BackBtnDown.png", "Textures/BackBtnUp.png", false);

	// Gameover GUI
	m_GameOverLayout = new CGui;
	m_GameOverLayout->CreateButton(glm::vec3(200, 100, 0), 300, 100, HOMEBTN, "Textures/BackBtnDown.png", "Textures/BackBtnUp.png", false);
	m_GameOverLayout->CreateText(glm::vec2(100, 650), 2.0f, glm::vec3(1, 1, 1), "GAME OVER!", false);
	m_GameOverLayout->CreateText(glm::vec2(225, 450), 1.0f, glm::vec3(1, 0, 0), "MVP: None, epic fail", false);
	m_GameOverLayout->CreateText(glm::vec2(225, 350), 1.0f, glm::vec3(1, 0, 0), "Score: Zilch", false);


	//// Client name
	//m_strClientName = "Anon";
	//m_pClientName = new TextLabel(m_strClientName, "Assets/Fonts/zorque.ttf");
	//m_pClientName->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	//m_pClientName->setPosition(glm::vec2(250, 0));	

	//// Server name
	//m_strServerName = "CoolServer";
	//m_pServerName = new TextLabel(m_strServerName, "Assets/Fonts/zorque.ttf");
	//m_pServerName->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	//m_pServerName->setPosition(glm::vec2(75, 600));
	//m_pServerName->setScale(2.0f);
}

void CMenu::ProcessClick(unsigned char* _keyState, unsigned char* _mouseState, int _mouseX, int _mouseY)
{
	// Point of where mouse clicked
	POINT mousePos;
	mousePos.x = _mouseX;
	mousePos.y = _mouseY;
	

	if (m_EMenuState == MAINMENU)
	{
		// Check which button has been clicked on the main menu
		//EButtonFunction buttonClicked = m_MainMenuLayout->CheckButtonClicked(mousePos, (_mouseState[MOUSE_LEFT] == BUTTON_UP) ? BUTTON_UP : BUTTON_DOWN, m_iSelectedServer);

		
		//switch (buttonClicked)
		//{
		//case NONE:
		//	break;
		//case PLAYBTN:
		//{
		//	//m_bMenuActive = false;
		//}
		//	break;
		//case HOSTNAMESELECT:
		//{
		//	m_EMenuState = HOSTOPTIONS;

		//}
		//	break;
		//case CONTROLSBTN:
		//{
		//	m_EMenuState = CONTROLS;
		//	break;
		//}
		//case QUITBTN:
		//{
		//	//glutLeaveMainLoop();
		//	break;
		//}
		//
		//default:
		//	break;
		//}

		//if (buttonClicked != NONE)
		//{
		//	//CAudio::PlayMenuClick();
		//}
	}
	else if (m_EMenuState == SERVERLIST)
	{
		//EButtonFunction buttonClicked = m_ServerListLayout->CheckButtonClicked(mousePos, (_mouseState[MOUSE_LEFT] == BUTTON_UP) ? BUTTON_UP : BUTTON_DOWN, m_iSelectedServer);

		/*switch (buttonClicked){
		}*/

		/*if (buttonClicked != NONE)
		{
			CAudio::PlayMenuClick();
		}*/
	}
	else if (m_EMenuState == HOSTOPTIONS)
	{
		//EButtonFunction buttonClicked = m_ServerNameLayout->CheckButtonClicked(mousePos, (_mouseState[MOUSE_LEFT] == BUTTON_UP) ? BUTTON_UP : BUTTON_DOWN, m_iSelectedServer);

		//switch (buttonClicked)
		//{
		//case HOMEBTN:
		//{
		//	m_EMenuState = MAINMENU;
		//	break;
		//}
		//case HOSTBTN:
		//{
		//	m_bMenuActive = false;
		//	//m_bIsServer = true;
		//	break;
		//}
		//default:
		//	break;
		//}

		//if (buttonClicked != NONE)
		//{
		//	//CAudio::PlayMenuClick();
		//}
	}
	else if (m_EMenuState == CONTROLS)
	{
		//EButtonFunction buttonClicked = m_ControlLayout->CheckButtonClicked(mousePos, (_mouseState[MOUSE_LEFT] == BUTTON_UP) ? BUTTON_UP : BUTTON_DOWN, m_iSelectedServer);

		//if (buttonClicked == HOMEBTN)
		//{
		//	m_EMenuState = MAINMENU;
		//}

		//if (buttonClicked != NONE)
		//{
		//	//CAudio::PlayMenuClick();
		//}
	}
	else if (m_EMenuState == GAMEOVER)
	{
		//EButtonFunction buttonClicked = m_GameOverLayout->CheckButtonClicked(mousePos, (_mouseState[MOUSE_LEFT] == BUTTON_UP) ? BUTTON_UP : BUTTON_DOWN, m_iSelectedServer);

		//if (buttonClicked == HOMEBTN)
		//{
		//	m_EMenuState = MAINMENU;
		//}

		//if (buttonClicked != NONE)
		//{
		//	//CAudio::PlayMenuClick();
		//}
	}
	

}

void CMenu::ProcessKey(unsigned char key)
{
	if (key == 8 || key == 127)
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

	//if (m_EMenuState == SERVERLIST)
	//{
	//	m_pClientName->setText(m_strClientName);
	//}
	//else if (m_EMenuState == HOSTOPTIONS)
	//{
	//	m_pServerName->setText(m_strServerName);
	//}
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// If main menu, render main menu
	if (m_EMenuState == MAINMENU)
	{
		m_MainMenuLayout->Render();
	}
	else if (m_EMenuState == SERVERLIST)
	{
		m_ServerListLayout->Render();
		//m_pClientName->Render();
	}
	else if (m_EMenuState == HOSTOPTIONS)
	{
		m_ServerNameLayout->Render();
		//m_pServerName->Render();
	}
	else if (m_EMenuState == CONTROLS)
	{
		m_ControlLayout->Render();
	}
	else if (m_EMenuState == GAMEOVER)
	{
		m_GameOverLayout->Render();
	}
	
	
	//glutSwapBuffers();
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
	m_ServerListLayout->HideText(1, 1, _bDisplay);
}

void CMenu::ChangeState(EMenuScreen _newMenuState)
{
	m_EMenuState = _newMenuState;
}
