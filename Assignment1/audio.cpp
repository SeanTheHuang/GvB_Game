#include "audio.h"

using namespace FMOD;

System* CAudio::m_system = nullptr;

Sound* CAudio::m_sAttack = nullptr;
Sound* CAudio::m_sBounce = nullptr;

Channel* CAudio::m_pMenuChannel = nullptr;
Channel* CAudio::m_pGameChannel = nullptr;
Channel* CAudio::m_pInGameChannel = nullptr;


void CAudio::InitializeFMOD()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_system);

	result = m_system->init(50, FMOD_INIT_NORMAL, 0);
}

void CAudio::LoadAudio()
{
	FMOD_RESULT result;

	result = m_system->createSound("Resources/Sounds/attack.mp3", FMOD_LOOP_OFF, 0, &m_sAttack);
	result = m_system->createSound("Resources/Sounds/bounce.mp3", FMOD_LOOP_OFF, 0, &m_sBounce);
}

void CAudio::PlaySound()
{
	m_system->playSound(m_sAttack, 0, false, &m_pInGameChannel);
}
