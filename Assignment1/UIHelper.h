//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: UIHelper.h
// Description	: Contains all UI related functions
// Author		: Madeleine Day, Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#ifndef _UIHELPER_H__
#define _UIHELPER_H__

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//#include "TexLabel.h"
#include "shaderhelper.h"
#include "Square.h"

// Menu buttons
enum EButtonFunction
{
	
	NONE, // No button clicked

	// temporary enum value for testing until we have network implemented
	PLAYBTN, 
	HOSTBTN,
	SERVERLISTBTN,
	SERVERSELECTBTN,
	REFRESHSERVERS,
	HOMEBTN,
	HOSTNAMESELECT,
	CONTROLSBTN,
	QUITBTN
};

// Menu button structure 
struct Button
{
	// Graphical component
	CSquare* pButtonShape;

	// Attributes
	glm::vec3 Position;
	float fWidth;
	float fHeight;

	// Button functionality
	EButtonFunction EFunction;
	bool bDepressed;
	bool bHidden;

	~Button()
	{
		delete pButtonShape;
		pButtonShape = 0;
	}
};

class CGui
{
public:

	CGui();
	~CGui();

	// Draw GUI
	void Render();

	// Create button that's added to the button vector
	void CreateButton(glm::vec3 _position, float _width, float _height, EButtonFunction _function, std::string _strClickedTex, std::string _strUnclickedTex, bool _bHidden);

	// Check if a button has been clicked
	EButtonFunction CheckButtonClicked(POINT _mousePos, int _state, int& _iServerIndex);
	
	void CreateText(glm::vec2 _position, float _fScale, glm::vec3 _rgbColor, std::string _text, bool _bHidden);

	void ResetScreen(int _btnsToKeep, int _txtToKeep);

	void ChangeText(int _iTextIndex, std::string _strNewText, glm::vec3 _newColor);

	void HideText(int _iFromTextIdx, int _iToTextIdx, bool _bHidden);

	void HideButton(int _iFromBtnIdx, int _iToBtnIdx, bool _bHidden);


private:
	// Button vector
	std::vector<Button*> m_pButtons;

	// Text vector
//	std::vector<TextLabel*> m_pTextLabels;

	// Button shader (no camera)
	GLuint m_ButtonShader;
};

#endif //_UIHELPER_H__