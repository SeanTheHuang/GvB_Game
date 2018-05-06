#include "howtoplaylevel.h"

void HowToPlayLevel::Initialize(std::vector<Player> _players)
{
	CButtonUI* playButton = new CButtonUI("Resources/Images/PlayButton_1.png", "Resources/Images/PlayButton_2.png",
		glm::vec2(500, 100), glm::vec2(200, 100), TO_MENU_BTN, 0);
	m_buttons.push_back(playButton);

	m_highlights[0] = 0;
	m_buttons[0]->UpdateHighlight(true);
}

void HowToPlayLevel::CleanUp()
{
	Level::CleanUp();
}

void HowToPlayLevel::Update()
{
	Level::Update();
}