#pragma once

#include "include.h"
#include "level.h"
#include "audio.h"
#include "Menu.h"

#include <map>

//Entry point to game
//Controls transitions between levels
//GameMaster is a [Singleton class]
class GameMaster
{
//== Methods
public:
	~GameMaster();
	static GameMaster& Instance(); // Singleton stuff
	// Clear Memory. Calls Destroy on all Level objects
	static void Destroy();
	// Create & Initialize all the levels
	// First level in map will be the default map
	void Initialize();
	//== Helper functions of Game master intializtation
	static void GameMaster::framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void GameMaster::ApplicationCleanUp();
	void GameMaster::InitializeCallbacks();

	// Calls update on current Level object
	void Update();
	// Calls Render on current Level object
	void Render();
	// Sets current level to specified level
	void ChangeLevel(std::string _levelName);

	void StorePlayerInfo(std::vector<Player> _players);

	// Call to get game window
	GLFWwindow* Window() { return m_pWindow; }
	// Get current level
	Level* GetCurrentLevel();
private:
	GameMaster(); //Singleton stuff
	GameMaster(const GameMaster&) = delete;
	void operator=(GameMaster const&) = delete;

	void InitializeLevels();

//== Members
private:
	static GameMaster* s_instance;
	std::map<std::string, Level*> m_mapLevels;
	Level* m_pCurrentLevel;
	GLFWwindow* m_pWindow;
	CAudio* m_cAudio;
	CMenu m_menu;
	std::string m_sNextLevelName;
	std::vector<Player> m_connectedPlayers;
};