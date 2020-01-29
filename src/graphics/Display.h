#pragma once

#include <iostream>
#include <string>
#include <map>

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <FMOD\fmod.hpp>
#include <FMOD\fmod_common.h>
#include <FMOD\fmod_errors.h>

#include "Font_Manager.h"
#include "../audio/Sound.h"

namespace ferrari {
	namespace graphics {

#define MAX_KEYS	348
#define MAX_BUTTONS	8

		class Display
		{
		private:
			const char* m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;
			double mx, my;

			bool m_KeyPress[MAX_KEYS];
			bool m_KeyHeld[MAX_KEYS];
			bool m_KeyState[MAX_KEYS];
			bool m_ButtonPress[MAX_BUTTONS];
			bool m_ButtonHeld[MAX_BUTTONS];
			bool m_ButtonState[MAX_BUTTONS];

		public:
			Display(const char* name, int width, int height);
			~Display();
			void Clear(float red, float green, float blue, float alpha) const;
			void Update();
			bool Closed() const;

			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }

			void GetMousePosition(double& x, double& y) const;

			bool isKeyPressed(unsigned int keycode) const;
			bool isKeyHeld(unsigned int keycode) const;
			bool isButtonHeld(unsigned int keycode) const;
			bool isButtonPressed(unsigned int keycode) const;
		private:
			bool Init();

			friend static void ResizeWindow(GLFWwindow* window, int width, int height);
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			friend static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

		};

	}
}