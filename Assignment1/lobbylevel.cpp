#include "lobbylevel.h"

void LobbyLevel::Initialize()
{
	CButtonUI* shit = new CButtonUI("Resources/Images/PlayButton_1.png", "Resources/Images/PlayButton_2.png",
		glm::vec2(100, 100), glm::vec2(200, 100), TO_MENU_BTN);
	m_buttons.push_back(shit);

	CButtonUI* fuck = new CButtonUI("Resources/Images/PlayButton_1.png", "Resources/Images/PlayButton_2.png",
		glm::vec2(700, 500), glm::vec2(200, 100), STARTGAME_BTN);
	m_buttons.push_back(fuck);

	m_highlightedButton = 0;
	m_buttons[0]->UpdateHighlight(true);
}

void LobbyLevel::CleanUp()
{
	Level::CleanUp();
}

void LobbyLevel::Update()
{
	Level::Update();
}
