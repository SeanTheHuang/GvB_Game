#include "audio.h"

using namespace FMOD;

std::unordered_map<std::string, FMOD::Sound*> CAudio::m_fmodSounds;

int CAudio::m_iAttackSounds = 0;
int CAudio::m_iBounceSounds = 0;

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
	m_fmodSounds["attack1.mp3"] = m_sAttack;
	m_iAttackSounds += 1;
	m_fmodSounds["bounce1.mp3"] = m_sBounce;

	result = m_system->init(50, FMOD_INIT_NORMAL, 0);
}

void CAudio::LoadAudio()
{
	FMOD_RESULT result;

	for (auto & x : m_fmodSounds)
	{
		std::string filn = "Resources/Audio/";
		filn + x.first;
		result = m_system->createSound(filn.c_str(), FMOD_LOOP_NORMAL, 0, &x.second);
	}

	//result = m_system->createSound("Resources/Sounds/attack.mp3", FMOD_LOOP_OFF, 0, &m_sAttack);
	//result = m_system->createSound("Resources/Sounds/bounce.mp3", FMOD_LOOP_OFF, 0, &m_sBounce);
}

void CAudio::PlaySound(std::string _sSound, bool _bCallRecursive)
{
	switch (_bCallRecursive)
	{
		case true:
		{
			if (_sSound == "attack") 
			{
				_sSound += rand() % m_iAttackSounds;
				PlaySound(_sSound, false);
			}
			break;
		}
		case false:
		{
			_sSound += ".mp3";
			m_system->playSound(m_fmodSounds[_sSound], 0, false, &m_pInGameChannel);
			break;
		}
	}
}
