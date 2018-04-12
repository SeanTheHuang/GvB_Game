#pragma once
#include "Includes\FMOD\fmod.hpp"
#include <string>
#include <vector>
#include<unordered_map>
#include<sstream>

class CAudio
{

public:
	~CAudio();
	static void InitializeFMOD();
	static void LoadAudio();

	static void PlaySound(std::string _sSound, bool _bCallRecursive);

private:
	CAudio();
	static FMOD::System* m_system;

	static std::unordered_map<std::string, FMOD::Sound*> m_fmodSounds;
	static FMOD::Sound* m_sAttack;
	static FMOD::Sound* m_sBounce;

	static FMOD::Channel* m_pMenuChannel;
	static FMOD::Channel* m_pGameChannel;
	static FMOD::Channel* m_pInGameChannel;

	static int m_iAttackSounds;
	static int m_iBounceSounds;
};