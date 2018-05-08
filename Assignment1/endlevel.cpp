#include "endlevel.h"
#include "gamemaster.h"

void EndLevel::Initialize()
{
	// Set Up UI
	auto playerInfo = GameMaster::Instance().GetPlayerInfo();
	
	CTextui* Title = new CTextui(glm::vec3(400, 600, 0), glm::vec3(0.9f, 0.6f, 0.1f), "Final Scores! ", "Resources/Fonts/Arial.ttf");
	Title->setScale(2);
	m_texts.push_back(Title);

	glm::vec3 textPosition = glm::vec3(100, 500, 0);
	glm::vec3 offset = glm::vec3(300, 0, 0);

	// For each player. print out their info
	for (size_t i = 0; i < 4; i++)
	{
		// Title
		CTextui* playerNames = new CTextui(textPosition, glm::vec3(1, 1, 0), "Player " + std::to_string(i + 1), "Resources/Fonts/Arial.ttf");
		CTextui* score = new CTextui(textPosition + glm::vec3(35, -100, 0), glm::vec3(1, 1, 1), "1", "Resources/Fonts/Arial.ttf");
		score->setScale(2);
		m_texts.push_back(playerNames);
		m_texts.push_back(score);
		textPosition += offset;
	}

	// Exit Game Button
	CButtonUI* returnButton = new CButtonUI("Resources/Images/ReturnButton_1.png", "Resources/Images/ReturnButton_2.png",
		glm::vec2(50, 0), glm::vec2(200, 100), TO_LOBBY_BTN, 0);
	m_buttons.push_back(returnButton);

	CTextui* returnText = new CTextui(glm::vec3(110, 70, 0), glm::vec3(0.9f), "Back To Lobby", "Resources/Fonts/Arial.ttf");
	m_texts.push_back(returnText);

	m_highlights[0] = 0;
	m_buttons[0]->UpdateHighlight(true);
}

void EndLevel::CleanUp()
{
	Level::CleanUp();
}

void EndLevel::Update()
{
	Level::Update();
}
