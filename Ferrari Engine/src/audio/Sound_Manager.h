#pragma once

#include <vector>
#include "Sound.h"

namespace ferrari {
	namespace audio {

		class SoundManager
		{
		private:
			static std::vector<Sound*> m_Sounds;

		public:
			static void Add(Sound* sound);
			static Sound* Get(const std::string& name);
			static void Clean();
		private:
			SoundManager();
		};
	}
}