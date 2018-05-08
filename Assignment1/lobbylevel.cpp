#include "lobbylevel.h"

void LobbyLevel::Initialize()
{
	m_totalPlayers.clear();

	for (int i = 0; i < 4; i++)
	{
		Player curPlayer;
		curPlayer.playerIndex = i;

		CButtonUI* globPortait = new CButtonUI((i == 0) ? "Resources/Images/BlobImage_1.png" : "Resources/Images/BlobImage_2.png", (i == 0) ? "Resources/Images/BlobImage_1.png" : "Resources/Images/BlobImage_2.png",
			glm::vec2((i * 300) + 300, WINDOW_HEIGHT - 100), glm::vec2(100, 100), (i == 0) ? PLAYER_PORTRAIT_BTN : ADD_PLAYER_BTN, i);
		curPlayer.playerPortrait = globPortait;

		CButtonUI* globReady =  new CButtonUI((i == 0) ? "Resources/Images/ReadyButton_1.png" : "Resources/Images/BlankButton_1.png", (i == 0) ? "Resources/Images/ReadyButton_2.png" : "Resources/Images/BlankButton_1.png",
			glm::vec2((i * 300) + 300, WINDOW_HEIGHT - 300), glm::vec2(200, 100), READY_PLAYER_BTN, i);
		curPlayer.readyBtn = globReady;

		curPlayer.active = false;
		curPlayer.readyState = false;

		m_highlights[i] = i * 2;

		m_buttons.push_back(globPortait);
		m_buttons.push_back(globReady);
		m_buttons[i * 2]->UpdateHighlight(true);

		m_totalPlayers.push_back(curPlayer);
	}

	m_totalPlayers[0].active = true;

	

	m_readyButton = nullptr;
	m_buttons.push_back(m_readyButton);

	CButtonUI* returnBtn = new CButtonUI("Resources/Images/ReturnButton_1.png", "Resources/Images/ReturnButton_2.png",
		glm::vec2(50, 0), glm::vec2(200, 100), TO_MENU_BTN, 0);
	m_buttons.push_back(returnBtn);
}

void LobbyLevel::CleanUp()
{
	Level::CleanUp();
}

void LobbyLevel::AddPlayer(int _playerIdx)
{
	m_totalPlayers[_playerIdx].playerPortrait->SetImage("Resources/Images/BlobImage_1.png", "Resources/Images/BlobImage_1.png");
	m_totalPlayers[_playerIdx].playerPortrait->ChangeAction(PLAYER_PORTRAIT_BTN);
	m_totalPlayers[_playerIdx].readyBtn->SetImage("Resources/Images/ReadyButton_1.png", "Resources/Images/ReadyButton_2.png");

	m_totalPlayers[_playerIdx].active = true;

	m_buttons[_playerIdx * 2] = m_totalPlayers[_playerIdx].playerPortrait;
	m_buttons[(_playerIdx * 2) + 1] = m_totalPlayers[_playerIdx].readyBtn;
}


void LobbyLevel::RemovePlayer(int _playerIdx)
{
	m_totalPlayers[_playerIdx].playerPortrait->SetImage("Resources/Images/BlobImage_2.png", "Resources/Images/BlobImage_2.png");
	m_totalPlayers[_playerIdx].playerPortrait->ChangeAction(ADD_PLAYER_BTN);
	m_totalPlayers[_playerIdx].readyBtn->SetImage("Resources/Images/BlankButton_1.png", "Resources/Images/BlankButton_1.png");;

	m_totalPlayers[_playerIdx].active = false;

	m_buttons[_playerIdx * 2] = m_totalPlayers[_playerIdx].playerPortrait;
	m_buttons[(_playerIdx * 2) + 1] = m_totalPlayers[_playerIdx].readyBtn;
}

void LobbyLevel::ReadyPlayer(int _playerIdx)
{
	if (m_totalPlayers[_playerIdx].active)
	{
		m_totalPlayers[_playerIdx].readyState = !m_totalPlayers[_playerIdx].readyState;

		m_totalPlayers[_playerIdx].readyBtn->SetImage((m_totalPlayers[_playerIdx].readyState) ? "Resources/Images/ReadyButton_3.png" : "Resources/Images/ReadyButton_1.png", 
			(m_totalPlayers[_playerIdx].readyState) ? "Resources/Images/ReadyButton_4.png" : "Resources/Images/ReadyButton_2.png");

		m_buttons[(_playerIdx * 2) + 1] = m_totalPlayers[_playerIdx].readyBtn;
	}
}

void LobbyLevel::ChangePlayerColor(int _playerIdx, glm::vec3 _color)
{
	m_totalPlayers[_playerIdx].color = _color;
}

void LobbyLevel::Update()
{
	bool allPlayersReady = true;
	bool playersConnected = false;
	for (int i = 0; i < m_totalPlayers.size(); i++)
	{
		if (Input::Instance().GetControllerInputDown(i, JOYSTICK_A) && !m_totalPlayers[i].active) {
			AddPlayer(i);
		}

		if (Input::Instance().GetControllerInputDown(i, JOYSTICK_B) && m_totalPlayers[i].active) {
			RemovePlayer(i);
		}

		if (m_totalPlayers[i].active) {
			playersConnected = true;
			if(!m_totalPlayers[i].readyState)
				allPlayersReady = false;
		}
	}
	
	if (allPlayersReady && playersConnected)
	{
		if (!m_readyButton)
		{
			m_readyButton = new CButtonUI("Resources/Images/PlayButton_1.png", "Resources/Images/PlayButton_2.png",
				glm::vec2(WINDOW_WIDTH - 200, 0), glm::vec2(200, 100), STARTGAME_BTN, 0);
			m_buttons[8] = m_readyButton;
		}
	}
	else
	{
		if (m_readyButton)
		{
			m_readyButton = nullptr;
			m_buttons[8] = m_readyButton;
		}
		
	}

	Level::Update();

}

std::vector<Player> LobbyLevel::GetPlayerData()
{
	for (int i = 0; i <m_totalPlayers.size(); i++)
	{
		if (!m_totalPlayers[i].active)
		{
			m_totalPlayers.erase(m_totalPlayers.begin() + i);
			i--;
		}
	}
	return m_totalPlayers;
}
