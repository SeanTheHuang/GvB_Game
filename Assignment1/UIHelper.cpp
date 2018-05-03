#include "UIHelper.h"

CGui::CGui()
{
	ShaderHelper::CompileAndLinkShaders("vertex_shader.glsl", "fragment_shader.glsl", m_ButtonShader);
}

CGui::~CGui()
{
	
	while (m_pButtons.size() != 0)
	{
		Button* tempButton = m_pButtons.back();
		m_pButtons.pop_back();
		delete tempButton;
		tempButton = 0;
	}

	
	//while (m_pTextLabels.size() != 0)
	//{
	//	TextLabel* tempText = m_pTextLabels.back();
	//	m_pTextLabels.pop_back();
	//	delete tempText;
	//	tempText = 0;
	//}
}

void CGui::Render()
{
	// Draws buttons in button vector
	for (auto &button : m_pButtons) // access by reference to avoid copying
	{
		if(!button->bHidden)
			button->pButtonShape->DrawModel();
	}

	//// Draws buttons in button vector
	//for (auto &text : m_pTextLabels) // access by reference to avoid copying
	//{
	//	if(!text->GetHidden())
	//		text->Render();
	//}
}

void CGui::CreateButton(glm::vec3 _position, float _width, float _height , EButtonFunction _function, std::string _strClickedTex, std::string _strUnclickedTex, bool _bHidden)
{
	// Create new button
	Button* UIButton = new Button;

	// Set function of button
	UIButton->EFunction = _function;

	// Set width/height
	UIButton->fWidth = _width;
	UIButton->fHeight = _height;
	UIButton->Position = glm::vec3(_position.x, _position.y, 0);

	// Set position and scale of the button
	glm::vec3 Position = glm::vec3(((_position.x - 1)/(WINDOW_WIDTH / 2) - 1), ((_position.y - 1)/(WINDOW_HEIGHT / 2) - 1), 1.0f);
	glm::vec3 scale = glm::vec3(_width / WINDOW_WIDTH, _height / WINDOW_HEIGHT, 1.0f);

	// Create square plane to represent button
	UIButton->pButtonShape = CSquare::CreateSquare(m_ButtonShader, Position, scale, _strClickedTex, _strUnclickedTex);

	UIButton->bDepressed = false;
	UIButton->bHidden = _bHidden;

	// Add button to vector
	m_pButtons.push_back(UIButton);


}

EButtonFunction CGui::CheckButtonClicked(POINT _mousePos, int _state, int& _iServerIndex)
{
	// Server index
	int iServerIndex = 0;

	// Cycles through buttons
	for (auto &button : m_pButtons) 
	{
		glm::vec3 buttonPos = button->Position;

		// Define clickable rectangle where button lies
		RECT* clickableRect = new RECT;

		// Set clickable area of button
		clickableRect->left = static_cast<LONG>(buttonPos.x - button->fWidth / 2);
		clickableRect->top = static_cast<LONG>(WINDOW_HEIGHT - buttonPos.y - button->fHeight/2);
		clickableRect->right = static_cast<LONG>(buttonPos.x + button->fWidth/2);
		clickableRect->bottom = static_cast<LONG>(WINDOW_HEIGHT - buttonPos.y + button->fHeight/2);

		// Check if mouse point is in clickable rect
		if (PtInRect(clickableRect, _mousePos))
		{
			// If button is released on a depressed button, it is considered activated
			if (_state == BUTTON_UP && button->bDepressed == true)
			{
				// Swap button texture
				button->pButtonShape->SwapButtonTexture(false);

				// Release button
				button->bDepressed = false;

				if (button->EFunction == SERVERSELECTBTN) {
					_iServerIndex = iServerIndex;
				}

				delete clickableRect;
				clickableRect = 0;

				// Return function of button
				return button->EFunction;
			}
			// If button is left clicked on a normal button
			else if (_state == BUTTON_DOWN && button->bDepressed == false)
			{
				// Swap texture
				button->pButtonShape->SwapButtonTexture(true);

				// Depress button
				button->bDepressed = true;
			}
			
		}
		else
		{
			// If mouse up while not on the button, the button is released without activation
			if (_state == BUTTON_UP)
			{
				button->pButtonShape->SwapButtonTexture(false);
				button->bDepressed = false;
			}
		}

		if (button->EFunction == SERVERSELECTBTN) {
			iServerIndex++;
		}

		delete clickableRect;
		clickableRect = 0;
	}

	// Nothing clicked
	return NONE;
}

void CGui::CreateText(glm::vec2 _position, float _fScale, glm::vec3 _rgbColor, std::string _text, bool _bHidden)
{
	//TextLabel* UIText = new TextLabel(_text, "Assets/Fonts/zorque.ttf");
	//UIText->setColor(glm::vec3(0, 0, 0));
	//UIText->setPosition(_position);
	//UIText->setColor(_rgbColor);
	//UIText->SetHidden(_bHidden);
	//UIText->setScale(_fScale);

	//m_pTextLabels.push_back(UIText);
}

void CGui::ResetScreen(int _btnsToKeep, int _txtToKeep)
{
	while (m_pButtons.size() != _btnsToKeep)
	{
		Button* tempButton = m_pButtons.back();
		m_pButtons.pop_back();
		delete tempButton;
	}

	//while (m_pTextLabels.size() != _txtToKeep)
	//{
	//	TextLabel* tempText = m_pTextLabels.back();
	//	m_pTextLabels.pop_back();
	//	delete tempText;
	//}
}

void CGui::ChangeText(int _iTextIndex, std::string _strNewText, glm::vec3 _newColor)
{
	//m_pTextLabels[_iTextIndex]->setText(_strNewText);
	//m_pTextLabels[_iTextIndex]->setColor(_newColor);

}

void CGui::HideText(int _iFromTextIdx, int _iToTextIdx, bool _bHidden) 
{
	//for (int i = _iFromTextIdx; i < _iToTextIdx + 1; i++)
	//{
	//	m_pTextLabels[i]->SetHidden(_bHidden);
	//}
	
}

void CGui::HideButton(int _iFromBtnIdx, int _iToBtnIdx, bool _bHidden)
{
	for (int i = _iFromBtnIdx; i < _iToBtnIdx + 1; i++)
	{
		m_pButtons[i]->bHidden = _bHidden;
	}
}

