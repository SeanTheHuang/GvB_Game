#pragma once

#include "userinterface.h"
#include "texture.h"
#include "include.h"

enum BUTTON_ACTION
{
	TO_LOBBY_BTN,
	TO_HOWTOPLAY_BTN,
	STARTGAME_BTN,
	QUIT_BTN,
	TO_MENU_BTN,
	ADD_PLAYER_BTN,
	PLAYER_PORTRAIT_BTN,
	READY_PLAYER_BTN,
	QUIT_TO_MENU_BTN,
	ABOUT_BTN
};

class CButtonUI : public CUi
{
public:
	CButtonUI(std::string _buttonUpImage, std::string _buttonDownImage,
		glm::vec2 _position, glm::vec2 _dimensions, BUTTON_ACTION _action, int _controlledByPlayer);
	~CButtonUI();

	virtual void Render();
	virtual bool Initialise();
	virtual void ProcessInteract();
	virtual void UpdateHighlight(bool _highlighted);
	virtual int GetPlayerUsedBy();
	virtual void ChangeAction(BUTTON_ACTION _newAction);

	// Set button image
	void SetImage(std::string _buttonUpImage, std::string _buttonDownImage);

private:
	BUTTON_ACTION m_eAction;
	void CreateAndLoadTexture();
	void CreateIndexBuffer();
	void CreateVertexBuffer();
	void CreateVAOwithVBOs();
	void CompileShaders();
	void getAddressofUniformLocation();

	bool MouseIsOverButton();
	bool m_highlighted = false;

	std::string m_buttonUpPath;
	std::string m_buttonDownPath;
	Texture *m_textureUp;
	Texture *m_textureDown;

	glm::vec3 m_color;

	GLuint m_EBO;

	glm::vec2 m_dimensions;

	GLuint gOrthoLocation, gSampler, gViewLocation, colorLocation;
	int m_playerUsedBy;
};