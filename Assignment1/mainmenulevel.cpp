#include "mainmenulevel.h"

void MainMenuLevel::Initialize()
{
	CButtonUI* playButton = new CButtonUI("Resources/Images/PlayButton_1.jpg", "Resources/Images/PlayButton_2.jpg",
										glm::vec2(300, 300), glm::vec2(200, 100), TO_LOBBY_BTN);
	m_buttons.push_back(playButton);

	CSprite* weebSprite = new CSprite("Resources/Images/weebLove.png", glm::vec2(150, 50), glm::vec2(500, 500));
	m_sprites.push_back(weebSprite);
}

void MainMenuLevel::CleanUp()
{
	Level::CleanUp();
}

void MainMenuLevel::Update()
{
	Level::Update();
}
