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
	REMOVE_PLAYER_BTN,
	READY_PLAYER_BTN
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
	int GetPlayerUsedBy();

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

	GLuint m_EBO;

	glm::vec2 m_dimensions;

	GLuint gOrthoLocation, gSampler, gViewLocation;
	int m_playerUsedBy;
};