#include "howtoplaylevel.h"

void HowToPlayLevel::Initialize()
{
	CButtonUI* playButton = new CButtonUI("Resources/Images/PlayButton_1.png", "Resources/Images/PlayButton_2.png",
		glm::vec2(500, 100), glm::vec2(200, 100), TO_MENU_BTN);
	m_buttons.push_back(playButton);
}

void HowToPlayLevel::CleanUp()
{
	Level::CleanUp();
}

void HowToPlayLevel::Update()
{
	Level::Update();
}