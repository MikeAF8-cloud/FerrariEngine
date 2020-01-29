#pragma once

#include <iostream>
#include <string>

#include "../utils/fileutils.h"

#include <FMOD\fmod.hpp>
#include <FMOD\fmod_common.h>
#include <FMOD\fmod_errors.h>

namespace ferrari {
	namespace audio {
		
#define MAX_CHANNELS	512
		class Sound
		{
		private:
			std::string m_Name;
			const char* m_FilePath;
			
			static FMOD::System *m_SoundSystem;
			FMOD::Sound *m_Sound;
			FMOD_RESULT m_Error; 
			unsigned int m_ChannelNum;
			static FMOD::Channel* m_Channels[512];

			bool m_Play = false;
			bool m_Pause = false;

		public:
			Sound(const std::string& name, const char* filepath);
			~Sound();
			void Play();
			void Stop();
			void Pause();
			void Loop();

			static bool Sound::Init();
			static void Sound::Update();
			
			inline const std::string& getName() const { return m_Name; }
			inline const std::string& getFilePath() const { return m_FilePath; }
		
		};
	}
}