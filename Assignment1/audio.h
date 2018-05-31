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

	static void PlaySound(std::string _sSound, bool _bCallRecursive = true);

private:
	CAudio();
	static FMOD::System* m_system;

	static std::unordered_map<std::string, FMOD::Sound*> m_fmodSounds;
	static FMOD::Sound* m_sJump;
	static FMOD::Sound* m_sImpact; // Landing impact
	static FMOD::Sound* m_sHit;
	static FMOD::Sound* m_sCharge;
	static FMOD::Sound* m_sUIResponse;

	static FMOD::Channel* m_pMenuChannel;
	static FMOD::Channel* m_pGameChannel;
	static FMOD::Channel* m_pInGameChannel;

	static int m_iJumpSounds;
	static int m_iHitSounds;
	static int m_iChargeSounds;
	static int m_iUiSounds;
	static int m_iImpactSounds;
};