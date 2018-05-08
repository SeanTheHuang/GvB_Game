#include "AboutLevel.h"

void AboutLevel::Initialize()
{
	// Add input delay
	for (int i = 0; i < m_buttons.size(); i++)
		m_inputDelayStamps[i] = Time::Instance().TotalTime();

	CSprite* background = new CSprite("Resources/Images/AboutMenuBackground.jpg", glm::vec2(0, 0), glm::vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	m_sprites.push_back(background);

	CButtonUI* returnButton = new CButtonUI("Resources/Images/ReturnButton_1.png", "Resources/Images/ReturnButton_2.png",
		glm::vec2(50, 0), glm::vec2(200, 100), TO_MENU_BTN, 0);
	m_buttons.push_back(returnButton);

	CTextui* returnText = new CTextui(glm::vec3(110, 70, 0), glm::vec3(0.9f), "Return", "Resources/Fonts/Arial.ttf");
	m_texts.push_back(returnText);

	CSprite* logo = new CSprite("Resources/Images/LogoImage.png", glm::vec2(1000, 100), glm::vec2(300, 300));
	m_sprites.push_back(logo);

	CTextui* testText = new CTextui(glm::vec3(100, 620, 0), glm::vec3(1), "In an alternate timeline, after the great Battle of Snake Racers 2025, Globs and Blobs have"
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText);

	CTextui* testText2 = new CTextui(glm::vec3(100, 560, 0), glm::vec3(1), "slammed everything out of existence. There is nothing else to slam, therefore they resort"
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText2);

	CTextui* testText3 = new CTextui(glm::vec3(100, 500, 0), glm::vec3(1), "to slamming each other. Some Globs do not wish to slam, but are forced to by their instinct"
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText3);

	CTextui* testText4 = new CTextui(glm::vec3(100, 440, 0), glm::vec3(1), "to survive. The eternal fight rages on until there is only one Glob left in existence."
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText4);

	CTextui* testText6 = new CTextui(glm::vec3(100, 300, 0), glm::vec3(1), "A game by Team Peppery, based on a true story."
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText6);

	m_highlights[0] = 0;
	m_buttons[0]->UpdateHighlight(true);
}

void AboutLevel::CleanUp()
{
	Level::CleanUp();
}

void AboutLevel::Update()
{
	Level::Update();
}