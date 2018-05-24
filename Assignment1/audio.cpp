#include "audio.h"

using namespace FMOD;

std::unordered_map<std::string, FMOD::Sound*> CAudio::m_fmodSounds;

int CAudio::m_iJumpSounds = 3;
int CAudio::m_iHitSounds = 3;
int CAudio::m_iChargeSounds = 3;
int CAudio::m_iUiSounds = 3;
int CAudio::m_iImpactSounds = 3;

System* CAudio::m_system = nullptr;

Sound* CAudio::m_sJump = nullptr;
Sound* CAudio::m_sHit = nullptr;
Sound* CAudio::m_sImpact = nullptr;
Sound* CAudio::m_sCharge = nullptr;
Sound* CAudio::m_sUIResponse = nullptr;

Channel* CAudio::m_pMenuChannel = nullptr;
Channel* CAudio::m_pGameChannel = nullptr;
Channel* CAudio::m_pInGameChannel = nullptr;


void CAudio::InitializeFMOD()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_system);

	m_fmodSounds["hit0.wav"] = m_sHit;
	m_fmodSounds["hit1.wav"] = m_sHit;
	m_fmodSounds["hit2.wav"] = m_sHit;

	m_fmodSounds["jump0.wav"] = m_sJump;
	m_fmodSounds["jump1.wav"] = m_sJump;
	m_fmodSounds["jump2.wav"] = m_sJump;

	m_fmodSounds["landing0.wav"] = m_sImpact;
	m_fmodSounds["landing1.wav"] = m_sImpact;
	m_fmodSounds["landing2.wav"] = m_sImpact;

	m_fmodSounds["charge0.wav"] = m_sCharge;
	m_fmodSounds["charge1.wav"] = m_sCharge;
	m_fmodSounds["charge2.wav"] = m_sCharge;

	m_fmodSounds["buttonpress0.wav"] = m_sUIResponse;
	m_fmodSounds["buttonpress1.wav"] = m_sUIResponse;
	m_fmodSounds["buttonpress2.wav"] = m_sUIResponse;

	result = m_system->init(50, FMOD_INIT_NORMAL, 0);
}

void CAudio::LoadAudio()
{
	FMOD_RESULT result;

	for (auto & x : m_fmodSounds)
	{
		std::string filn = "Resources/Audio/";
		filn += x.first;
		result = m_system->createSound(filn.c_str(), FMOD_LOOP_NORMAL, 0, &x.second);
		x.second->setMode(FMOD_LOOP_OFF);
	}

	//result = m_system->createSound("Resources/Sounds/attack0.mp3", FMOD_LOOP_OFF, 0, &m_sAttack);
	//result = m_system->createSound("Resources/Sounds/bounce.mp3", FMOD_LOOP_OFF, 0, &m_sBounce);
}

void CAudio::PlaySound(std::string _sSound, bool _bCallRecursive)
{
	switch (_bCallRecursive)
	{
		case true:
		{

			if (_sSound == "jump")
			{
				std::stringstream ss;
				ss << rand() % m_iJumpSounds;

				_sSound += ss.str();
				PlaySound(_sSound, false);
			}
			else if (_sSound == "hit")
			{
				std::stringstream ss;
				ss << rand() % m_iHitSounds;

				_sSound += ss.str();
				PlaySound(_sSound, false);
			}
			else if (_sSound == "charge")
			{
				std::stringstream ss;
				ss << rand() % m_iChargeSounds;

				_sSound += ss.str();
				PlaySound(_sSound, false);
			}
			else if (_sSound == "buttonpress")
			{
				std::stringstream ss;
				ss << rand() % m_iUiSounds; 

				_sSound += ss.str();
				PlaySound(_sSound, false);
			}
			else if (_sSound == "landing")
			{
				std::stringstream ss;
				ss << rand() % m_iImpactSounds;

				_sSound += ss.str();
				PlaySound(_sSound, false);
			}
			break;
		}
		case false:
		{
			_sSound += ".wav";
			m_system->playSound(m_fmodSounds[_sSound], 0, false, &m_pInGameChannel);
			break;
		}
	}
}
