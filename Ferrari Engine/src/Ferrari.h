#pragma once

#include "graphics\Display.h"
#include "graphics\Layers\Layer.h"
#include "graphics\BatchRenderer2D.h"
#include "graphics\renderer2D.h"
#include "graphics\sprite.h"
#include "graphics\Label.h"
#include "audio\Sound.h"

#include "maths\maths.h"

#include "utils\Timer.h"

namespace ferrari {
	class Ferrari
	{
	private:
		graphics::Display* m_Window;
		audio::Sound* m_Sound;
		Timer* m_Timer;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
	protected:
		Ferrari()
			:m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}

		virtual ~Ferrari()
		{
			delete m_Window;
			delete m_Timer;
		}

		graphics::Display* CreateDisplay(const char *name, int width, int height)
		{
			m_Window = new graphics::Display(name, width, height);
			return m_Window;
		}

		//Runs once upon initialization
		virtual void Init() = 0;
		//Runs once per second
		virtual void Tick() {};
		//Runs 60 times per second
		virtual void Update() {};
		//Runs as fast as possible (unless vsync is enabled)
		virtual void Render() = 0;

		const unsigned int getFPS() { return m_FramesPerSecond; }
		const unsigned int getUPS() { return m_UpdatesPerSecond; }

	public:
		void start()
		{
			Init();
			Run();
		}
	private:
		void Run()
		{
			audio::Sound::Init();
			m_Timer = new Timer();

			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

			while (!m_Window->Closed())
			{
				m_Window->Clear(0,0,0,0);
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					Update();
					updates++;
					updateTimer += updateTick;
				}

				Render();
				frames++;
				m_Window->Update();
				audio::Sound::Update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					Tick();
				}
			}
		}
	};
}