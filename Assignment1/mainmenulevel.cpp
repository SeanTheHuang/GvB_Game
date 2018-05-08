#include "mainmenulevel.h"

void MainMenuLevel::Initialize()
{
	// Add input delay
	for (int i = 0; i < m_buttons.size(); i++)
		m_inputDelayStamps[i] = Time::Instance().TotalTime();

	// Set Up UI
	CButtonUI* playButton = new CButtonUI("Resources/Images/PlayButton_1.png", "Resources/Images/PlayButton_2.png",
										glm::vec2(300, 500), glm::vec2(200, 100), TO_LOBBY_BTN, 0);
	m_buttons.push_back(playButton);

	CButtonUI* HTPButton = new CButtonUI("Resources/Images/HTPButton_1.png", "Resources/Images/HTPButton_2.png",
		glm::vec2(285, 400), glm::vec2(500, 80), TO_HOWTOPLAY_BTN, 0);
	m_buttons.push_back(HTPButton);

	CButtonUI* QuitButton = new CButtonUI("Resources/Images/QuitButton_1.png", "Resources/Images/QuitButton_2.png",
		glm::vec2(50, 50), glm::vec2(125, 60), QUIT_BTN, 0);
	m_buttons.push_back(QuitButton);

	CSprite* background = new CSprite("Resources/Images/MainMenuBackground.jpg", glm::vec2(0, 0), glm::vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	m_sprites.push_back(background);

	m_highlights[0] = 0;
	m_buttons[0]->UpdateHighlight(true);
}

void MainMenuLevel::CleanUp()
{
	Level::CleanUp();
}

void MainMenuLevel::Update()
{
	Level::Update();
}
