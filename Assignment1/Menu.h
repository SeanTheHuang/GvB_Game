//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Menu.h
// Description	: Contains the logic of the buttons
// Author		: Madeleine Day, Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#ifndef __MENU_H__
#define __MENU_H__

// System includes
#include "include.h"
// Local includes
#include "TexLabel.h"
#include "UIHelper.h"

// Sub screens of the menu system
enum EMenuScreen
{
	MAINMENU,
	HOSTOPTIONS, 
	SERVERLIST,
	LOBBY,
	CONTROLS,
	GAMEOVER
};

class CMenu
{
public:
	CMenu();
	~CMenu();

	// Init layouts of menu screens
	void Initialize();
	// Process click in the menu screen
	void ProcessClick(unsigned char* _keyState, unsigned char* _mouseState, int _mouseX, int _mouseY);

	// Process key stroke in menu screen
	void ProcessKey(unsigned char key);

	void SetBestPlayer(std::string _name, int _score);

	// Render screen
	void RenderScene();

	// Check if menu is the active state
	bool GetActiveState();

	void SetActiveState(bool _active);

	void HideError(bool _bDisplay);

	void ChangeState(EMenuScreen _newMenuState);

	

private:
	// State of menu
	EMenuScreen m_EMenuState;
	// Flag of menu activity
	bool m_bMenuActive;

	// Main menu layout
	CGui* m_MainMenuLayout;

	// Server list layout
	CGui* m_ServerListLayout;
	std::vector<std::string> m_vecServerList;

	// Server name select screen
	CGui* m_ServerNameLayout;

	// Control screen layout
	CGui* m_ControlLayout;

	CGui* m_GameOverLayout;

	//bool m_bClientNameSet;
//	TextLabel* m_pClientName;
	std::string m_strClientName;

	//TextLabel* m_pServerName;
	std::string m_strServerName;

	// Client
	bool m_bLevelLoaded;

	std::string m_strBestPlayer;
	int m_iBestScore;
};

#endif //__MENU_H__