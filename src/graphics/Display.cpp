#include "Display.h"

namespace ferrari {
	namespace graphics {
		int oldState = -1;

		Display::Display(const char* name, int width, int height)
			:m_Title(name), m_Width(width), m_Height(height)
		{
			if (!Init())
				glfwTerminate();

			FontManager::Add(new Font("Arial", "arial.ttf", 32));
		}

		Display::~Display()
		{
			glfwTerminate();
			FMOD_RESULT FMOD_System_Release();
		}

		bool Display::Init()
		{

			//Initializing the Window
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!\n";
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, ResizeWindow);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
			glfwSetCursorPosCallback(m_Window, CursorPositionCallback);
			glfwSwapInterval(0);
			
			//Creating the Array of Inputs
			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_KeyHeld[i] = false;
				m_KeyState[i] = false;
			}
			memcpy(m_KeyPress, m_KeyHeld, MAX_KEYS);

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_ButtonHeld[i] = false;
				m_ButtonState[i] = false;
			}
			memcpy(m_ButtonPress, m_ButtonHeld, MAX_BUTTONS);

			//Initializing the GLEW for Graphics Design
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialize GLEW!\n";
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			return true;
		}

		void Display::Clear(float red, float green, float blue, float alpha) const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		int state;
		void Display::Update()
		{
			GLenum GLerror = glGetError();
			if (GLerror != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << GLerror << std::endl;

			for (int i = 0; i < MAX_KEYS; i++)
			{
				state = glfwGetKey(m_Window, i);
				if (state == GLFW_PRESS)
				{
					if (m_KeyState[i] == GLFW_PRESS)
						m_KeyPress[i] = false;
					else
						m_KeyPress[i] = true;

					m_KeyHeld[i] = true;
				}
				else if (state == GLFW_RELEASE)
				{
					m_KeyPress[i] = false;
					m_KeyHeld[i] = false;
				}
				m_KeyState[i] = state;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				state = glfwGetMouseButton(m_Window, i);
				if (state == GLFW_PRESS)
				{
					if (m_ButtonState[i] == GLFW_PRESS)
						m_ButtonPress[i] = false;
					else
						m_ButtonPress[i] = true;

					m_ButtonHeld[i] = true;
				}
				else if (state == GLFW_RELEASE)
				{
					m_ButtonPress[i] = false;
					m_ButtonHeld[i] = false;
				}
				m_ButtonState[i] = state;
			}

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Display::Closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void Display::GetMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		bool Display::isKeyPressed(unsigned int keycode) const
		{
			// TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;

			return m_KeyPress[keycode];
		}

		bool Display::isKeyHeld(unsigned int keycode) const
		{
			// TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;

			return m_KeyHeld[keycode];
		}

		bool Display::isButtonPressed(unsigned int buttoncode) const
		{
			// TODO: Log this!
			if (buttoncode >= MAX_BUTTONS)
				return false;

			return m_ButtonPress[buttoncode];
		}

		bool Display::isButtonHeld(unsigned int buttoncode) const
		{
			// TODO: Log this!
			if (buttoncode >= MAX_BUTTONS)
				return false;

			return m_ButtonHeld[buttoncode];
		}

		void ResizeWindow(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Display* win = (Display*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Display* win = (Display*)glfwGetWindowUserPointer(window);
		}    

		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Display* win = (Display*)glfwGetWindowUserPointer(window);
		}

		void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Display* win = (Display*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}
	}
}