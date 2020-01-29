#include "Sound.h"

namespace ferrari {
	namespace audio {
		
		FMOD::System *Sound::m_SoundSystem = NULL;
		FMOD::Channel* Sound::m_Channels[512];
		bool errorCheck(FMOD_RESULT result)
		{
			if (result != FMOD_OK)
			{
				std::cout << "FMOD Error: (" << result << ") " << FMOD_ErrorString(result) << std::endl;
				return false;
			}
			return true;
		}

		Sound::Sound(const std::string& name, const char* filepath)
			: m_Name(name), m_FilePath(filepath)
		{
			m_Error = m_SoundSystem->createSound(filepath, FMOD_DEFAULT, 0, &m_Sound);
			errorCheck(m_Error);
		}

		Sound::~Sound()
		{
			m_Error = m_Sound->release();
			errorCheck(m_Error);
			m_Error = m_SoundSystem->close();
			errorCheck(m_Error);
			m_Error = m_SoundSystem->release();
			errorCheck(m_Error);
		}

		void Sound::Play()
		{
			if (m_Channels[m_ChannelNum] == NULL)
			{
				for (int i = 0; i < MAX_CHANNELS; i++)
				{
					m_ChannelNum == i;
				}
			}
			
			m_Channels[m_ChannelNum]->isPlaying(&m_Play);
			if (!m_Play)
			{
				m_Error = m_Sound->setMode(FMOD_LOOP_OFF);
				errorCheck(m_Error);

				m_Error = m_SoundSystem->playSound(m_Sound, 0, true, &m_Channels[m_ChannelNum]);
				errorCheck(m_Error);
			}
			m_Channels[m_ChannelNum]->getPaused(&m_Pause);
			if (m_Pause)
				m_Error = m_Channels[m_ChannelNum]->setPaused(false);
		}

		void Sound::Stop()
		{
			m_Channels[m_ChannelNum]->stop();
		}

		void Sound::Pause()
		{
			m_Error = m_Channels[m_ChannelNum]->getPaused(&m_Pause);
			if (!m_Pause)
				m_Error = m_Channels[m_ChannelNum]->setPaused(true);

			errorCheck(m_Error);
		}

		void Sound::Loop()
		{
			if (m_Channels[m_ChannelNum] == NULL)
			{
				for (int i = 0; i < MAX_CHANNELS; i++)
				{
					if (m_Channels[i] == NULL)
					{
						m_ChannelNum = i;
						break;
					}
				}
			}

			m_Channels[m_ChannelNum]->isPlaying(&m_Play);
			if (!m_Play)
			{
				m_Error = m_Sound->setMode(FMOD_LOOP_NORMAL);
				errorCheck(m_Error);

				m_Error = m_SoundSystem->playSound(m_Sound, 0, true, &m_Channels[0]);
				errorCheck(m_Error);
			}
			m_Channels[m_ChannelNum]->getPaused(&m_Pause);
			if (m_Pause)
				m_Error = m_Channels[m_ChannelNum]->setPaused(false);
		}

		void Sound::Update()
		{
			FMOD_RESULT error;
			
			error = m_SoundSystem->update();
			errorCheck(error);
			
		}

		bool Sound::Init()
		{
			//Initializing Audio
			FMOD_RESULT error;
			error = FMOD::System_Create(&m_SoundSystem);
			if (!errorCheck(error))
			{
				m_SoundSystem->close();
				m_SoundSystem->release();

				return false;
			}
			
			unsigned int version;
			error = m_SoundSystem->getVersion(&version);
			if (version < FMOD_VERSION)
				std::cout << "FMOD lib version " << version << " does not match the header version " << FMOD_VERSION << std::endl;
			else
				std::cout << "FMOD version " << FMOD_VERSION << std::endl;

			error = m_SoundSystem->init(MAX_CHANNELS, FMOD_INIT_NORMAL, 0);
			if (!errorCheck(error))
			{
				m_SoundSystem->close();
				m_SoundSystem->release();
				
				return false;
			}

			memset(m_Channels, 0, sizeof(FMOD::Channel)*MAX_CHANNELS);
			return true;
		}

	}
}