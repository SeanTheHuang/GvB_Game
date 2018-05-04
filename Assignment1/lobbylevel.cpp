#include "lobbylevel.h"

void LobbyLevel::Initialize()
{
	CButtonUI* playButton = new CButtonUI("Resources/Images/PlayButton_1.jpg", "Resources/Images/PlayButton_2.jpg",
		glm::vec2(100, 100), glm::vec2(200, 100), TO_MENU_BTN);
	m_buttons.push_back(playButton);
}

void LobbyLevel::CleanUp()
{
	Level::CleanUp();
}

void LobbyLevel::Update()
{
	Level::Update();
}
