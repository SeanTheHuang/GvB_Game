#pragma once
#include "Includes\FMOD\fmod.hpp"

class CAudio
{

public:
	~CAudio();
	static void InitializeFMOD();
	static void LoadAudio();

	static void PlaySound();

private:
	CAudio();
	static FMOD::System* m_system;

	static FMOD::Sound* m_sAttack;
	static FMOD::Sound* m_sBounce;

	static FMOD::Channel* m_pMenuChannel;
	static FMOD::Channel* m_pGameChannel;
	static FMOD::Channel* m_pInGameChannel;
};