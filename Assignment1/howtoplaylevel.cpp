#include "howtoplaylevel.h"

void HowToPlayLevel::Initialize()
{
	// Add input delay
	for (int i = 0; i < m_buttons.size(); i++)
		m_inputDelayStamps[i] = Time::Instance().TotalTime();

	CButtonUI* returnButton = new CButtonUI("Resources/Images/ReturnButton_1.png", "Resources/Images/ReturnButton_2.png",
		glm::vec2(50, 0), glm::vec2(200, 100), TO_MENU_BTN, 0);
	m_buttons.push_back(returnButton);

	CTextui* returnText = new CTextui(glm::vec3(110, 70, 0), glm::vec3(0.9f), "Return", "Resources/Fonts/Arial.ttf");
	m_texts.push_back(returnText);

	CSprite* background = new CSprite("Resources/Images/HTPBackground.jpg", glm::vec2(0, 0), glm::vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	m_sprites.push_back(background);


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