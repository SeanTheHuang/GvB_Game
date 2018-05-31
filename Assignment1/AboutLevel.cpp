#include "AboutLevel.h"

void AboutLevel::Initialize()
{
	// Add input delay
	for (size_t i = 0; i < m_buttons.size(); i++)
		m_inputDelayStamps[i] = Time::Instance().TotalTime();

	CSprite* background = new CSprite("Resources/Images/AboutBackground.jpg", glm::vec2(0, 0), glm::vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	m_sprites.push_back(background);

	CButtonUI* returnButton = new CButtonUI("Resources/Images/ReturnButton_1.png", "Resources/Images/ReturnButton_2.png",
		glm::vec2(50, 0), glm::vec2(200, 100), TO_MENU_BTN, 0);
	m_buttons.push_back(returnButton);

	CSprite* logo = new CSprite("Resources/Images/LogoImage.png", glm::vec2(1000, 120), glm::vec2(120, 120));
	m_sprites.push_back(logo);

	CTextui* testText = new CTextui(glm::vec3(100, 570, 0), glm::vec3(glm::vec3(0.9f, 0.1f, 0.8f)), 
		"In an alternate timeline, after the great Battle of Snake Racers 2025,", "Resources/Fonts/VT323-Regular.ttf");
	m_texts.push_back(testText);

	CTextui* testText2 = new CTextui(glm::vec3(100, 510, 0), glm::vec3(glm::vec3(0.9f, 0.1f, 0.8f)), 
		"Globs and Blobs have slammed everything out of existence."
		, "Resources/Fonts/VT323-Regular.ttf");
	m_texts.push_back(testText2);

	CTextui* testText3 = new CTextui(glm::vec3(100, 450, 0), glm::vec3(glm::vec3(0.9f, 0.1f, 0.8f)), 
		"There is nothing else to slam, therefore they resort to slamming each other."
		, "Resources/Fonts/VT323-Regular.ttf");
	m_texts.push_back(testText3);

	CTextui* testText4 = new CTextui(glm::vec3(100, 390, 0), glm::vec3(glm::vec3(0.9f, 0.1f, 0.8f)), 
		"Some Globs do not wish to slam, but are forced to by their instinct to survive."
		, "Resources/Fonts/VT323-Regular.ttf");
	m_texts.push_back(testText4);

	CTextui* testText5 = new CTextui(glm::vec3(100, 330, 0), glm::vec3(glm::vec3(0.9f, 0.1f, 0.8f)),
		"The eternal fight rages on until there is only one Glob left in existence."
		, "Resources/Fonts/VT323-Regular.ttf");
	m_texts.push_back(testText5);

	CTextui* testText6 = new CTextui(glm::vec3(100, 120, 0), glm::vec3(1), 
		"A game by Team Peppery, based on a true story."
		, "Resources/Fonts/VT323-Regular.ttf");
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