#pragma once

#include "include.h"
#include "level.h"

class LobbyLevel : public Level
{
	// Member Functions
public:
	void Initialize(std::vector<Player> _players);
	void CleanUp();
	void AddPlayer(int _playerIdx);
	void RemovePlayer(int _playerIdx);
	void ReadyPlayer(int _playerIdx);
	void ChangePlayerColor(int _playerIdx, glm::vec3 _color);
	void Update();
	std::vector<Player> GetPlayerData();

protected:
	std::vector<Player> m_totalPlayers;
	int activePlayers = 0;
	CButtonUI* m_readyButton;
	// Member Variables
protected:

};