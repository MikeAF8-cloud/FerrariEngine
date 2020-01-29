#include "Sound_Manager.h"

namespace ferrari {
	namespace audio {

		std::vector<Sound*> SoundManager::m_Sounds;

		void SoundManager::Add(Sound* sound)
		{
			m_Sounds.push_back(sound);
		}

		Sound* SoundManager::Get(const std::string& name)
		{
			for (Sound* sound : m_Sounds)
			{
				if (sound->getName() == name)
					return sound;
			}
			return nullptr;
		}

		void SoundManager::Clean()
		{
			for (int i = 0; i < m_Sounds.size(); i++)
				delete m_Sounds[i];
		}

	}
}
