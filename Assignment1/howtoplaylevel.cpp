#include "howtoplaylevel.h"

void HowToPlayLevel::Initialize()
{
	// Add input delay
	for (int i = 0; i < m_buttons.size(); i++)
		m_inputDelayStamps[i] = Time::Instance().TotalTime();

	CButtonUI* playButton = new CButtonUI("Resources/Images/ReturnButton_1.png", "Resources/Images/ReturnButton_2.png",
		glm::vec2(50, 0), glm::vec2(200, 100), TO_MENU_BTN, 0);
	m_buttons.push_back(playButton);


	CSprite* background = new CSprite("Resources/Images/GVB_HOWTOPLAYMENU.jpg", glm::vec2(0, 0), glm::vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
	m_sprites.push_back(background);

	CTextui* testText = new CTextui(glm::vec3(100, 680, 0), glm::vec3(1), "Glob vs. Blob consists of a maximum of four players and a minimum of two."
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText);

	CTextui* testText2 = new CTextui(glm::vec3(100, 630, 0), glm::vec3(1), "The objective of Glob VS Blob is too project your character onto an opponents within the arena"
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText2);

	CTextui* testText3 = new CTextui(glm::vec3(100, 580, 0), glm::vec3(1), "This is achievable depending on which device is controlling your character."
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText3);

	CTextui* testText4 = new CTextui(glm::vec3(100, 520, 0), glm::vec3(1), "Firstly, and probably the most important factor is how to alter the direction of your character..."
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText4);

	CTextui* testText5 = new CTextui(glm::vec3(100, 470, 0), glm::vec3(1), "If you are using a controller, the 'x' and 'b' key's will help to alter your direction.."
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText5);

	CTextui* testText6 = new CTextui(glm::vec3(100, 420, 0), glm::vec3(1), "If you're using a keyboard, then the [A, S], [O, P], [Arrow Left, Arrow Right], [Numpad 8, Numpad 9]."
		, "Resources/Fonts/Arial.ttf");
	m_texts.push_back(testText6);


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