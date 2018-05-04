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
	TO_MENU_BTN
};

class CButtonUI : public CUi
{
public:
	CButtonUI(std::string _buttonUpImage, std::string _buttonDownImage,
		glm::vec2 _position, glm::vec2 _dimensions, BUTTON_ACTION _action);
	~CButtonUI();

	virtual void Render();
	virtual bool Initialise();
	virtual void ProcessInteract();

private:
	BUTTON_ACTION m_eAction;
	void CreateAndLoadTexture();
	void CreateIndexBuffer();
	void CreateVertexBuffer();
	void CreateVAOwithVBOs();
	void CompileShaders();
	void getAddressofUniformLocation();

	bool MouseIsOverButton();

	std::string m_buttonUpPath;
	std::string m_buttonDownPath;
	Texture *m_textureUp;
	Texture *m_textureDown;

	GLuint m_EBO;

	glm::vec2 m_dimensions;

	GLuint gOrthoLocation, gSampler, gViewLocation;

};