#include "lobbylevel.h"

void LobbyLevel::Initialize(std::vector<Player> _players)
{
	//CButtonUI* playButton = new CButtonUI("Resources/Images/PlayButton_1.png", "Resources/Images/PlayButton_2.png",
	//	glm::vec2(0, 0), glm::vec2(200, 100), TO_MENU_BTN, 0);
	//m_buttons.push_back(playButton);

	for (int i = 0; i < 4; i++)
	{
		Player player1;
		player1.playerIndex = i;
		m_totalPlayers.push_back(player1);

		CButtonUI* globPortait = new CButtonUI((i == 0) ? "Resources/Images/BlobImage_1.png" : "Resources/Images/BlobImage_2.png", (i == 0) ? "Resources/Images/BlobImage_1.png" : "Resources/Images/BlobImage_2.png",
			glm::vec2((i * 300) + 300, WINDOW_HEIGHT - 100), glm::vec2(100, 100), (i == 0) ? PLAYER_PORTRAIT_BTN : ADD_PLAYER_BTN, i);

		player1.playerPortrait = globPortait;

		m_buttons.push_back(globPortait);

		CButtonUI* globReady = (i==0) ? new CButtonUI("Resources/Images/ReadyButton_1.png", "Resources/Images/ReadyButton_2.png",
			glm::vec2((i * 300) + 300, WINDOW_HEIGHT - 300), glm::vec2(200, 100), READY_PLAYER_BTN, i) : nullptr;
		m_buttons.push_back(globReady);

		player1.readyBtn = globReady;
		m_totalPlayers[i].active = false;
		m_totalPlayers[i].readyState = false;
	}

	m_totalPlayers[0].active = true;

	m_highlights[0] = 0;
	m_buttons[0]->UpdateHighlight(true);

	m_readyButton = nullptr;
	m_buttons.push_back(m_readyButton);
}

void LobbyLevel::CleanUp()
{
	Level::CleanUp();
}

void LobbyLevel::AddPlayer(int _playerIdx)
{
	//delete m_activePlayers[_playerIdx].playerPortrait;
	m_totalPlayers[_playerIdx].playerPortrait = new CButtonUI("Resources/Images/BlobImage_1.png", "Resources/Images/BlobImage_1.png",
		glm::vec2((_playerIdx * 300) + 300, WINDOW_HEIGHT - 100), glm::vec2(100, 100), PLAYER_PORTRAIT_BTN, _playerIdx);
	m_buttons[_playerIdx * 2] = m_totalPlayers[_playerIdx].playerPortrait;

	m_totalPlayers[_playerIdx].readyBtn = new CButtonUI("Resources/Images/ReadyButton_1.png", "Resources/Images/ReadyButton_2.png",
		glm::vec2((_playerIdx * 300) + 300, WINDOW_HEIGHT - 300), glm::vec2(200, 100), READY_PLAYER_BTN, _playerIdx);
	m_buttons[(_playerIdx * 2)+1] = m_totalPlayers[_playerIdx].readyBtn;

	m_totalPlayers[_playerIdx].active = true;
}


void LobbyLevel::RemovePlayer(int _playerIdx)
{
	m_totalPlayers[_playerIdx].playerPortrait = new CButtonUI("Resources/Images/BlobImage_2.png", "Resources/Images/BlobImage_2.png",
		glm::vec2((_playerIdx * 300) + 300, WINDOW_HEIGHT - 100), glm::vec2(100, 100), ADD_PLAYER_BTN, _playerIdx);
	m_buttons[_playerIdx * 2] = m_totalPlayers[_playerIdx].playerPortrait;

	m_totalPlayers[_playerIdx].readyBtn = nullptr;
	m_buttons[(_playerIdx * 2) + 1] = m_totalPlayers[_playerIdx].readyBtn;

	m_totalPlayers[_playerIdx].active = false;
}

void LobbyLevel::ReadyPlayer(int _playerIdx)
{
	m_totalPlayers[_playerIdx].readyState = !m_totalPlayers[_playerIdx].readyState;
}

void LobbyLevel::ChangePlayerColor(int _playerIdx, glm::vec3 _color)
{
	m_totalPlayers[_playerIdx].color = _color;
}

void LobbyLevel::Update()
{
	bool allPlayersReady = true;
	bool playersConnected = false;
	for (int i = 0; i < 4; i++)
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
