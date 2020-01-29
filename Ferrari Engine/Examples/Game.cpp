#include "../src/Ferrari.h"

using namespace ferrari;
using namespace graphics;
using namespace audio;

class Game : public Ferrari
{
private:
	Display* m_Window;
	Layer* m_Layer;
	Label* m_FPS;
	Sprite* m_Sprite;
	Shader* m_Shader;
public:
	Game()
	{

	}

	~Game()
	{
		delete m_Layer;
	}

	void Init() override
	{
		m_Window = CreateDisplay("Ferrari", 960, 540);
		FontManager::Get()->setScale(m_Window->getWidth() / 32.0f, m_Window->getHeight() / 18.0f);
		m_Shader = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
		m_Layer = new Layer(new BatchRenderer2D(), m_Shader, maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		m_Sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("Mario", "mario running.png"));
		m_Layer->Add(m_Sprite);

		m_FPS = new Label("", -15.5f, 7.8f, 0xffffffff);
		m_Layer->Add(m_FPS);
	}

	void Tick() override
	{
		m_FPS->text = std::to_string(getFPS()) + " fps";
		std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
	}

	void Update() override
	{
		float speed = 0.5f;
		if (m_Window->isKeyHeld(GLFW_KEY_UP))
			m_Sprite->position.y += speed;
		if (m_Window->isKeyHeld(GLFW_KEY_DOWN))
			m_Sprite->position.y -= speed;
		if (m_Window->isKeyHeld(GLFW_KEY_LEFT))
			m_Sprite->position.x -= speed;
		if (m_Window->isKeyHeld(GLFW_KEY_RIGHT))
			m_Sprite->position.x += speed;

		double x, y;
		m_Window->GetMousePosition(x, y);
		m_Shader->setUniform2f("light_pos", maths::vec2((float)(x * 32.0f / m_Window->getWidth() - 16.0f), (float)(9.0f - y * 18.0f / m_Window->getHeight())));

	}

	void Render() override
	{
		m_Layer->Render();
	}
};

int main()
{
	Game game;
	game.start();
	return 0;
}