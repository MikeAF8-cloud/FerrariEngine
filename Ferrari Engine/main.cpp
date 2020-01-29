#include <iostream>
#if 0
#include "src\graphics\Display.h"
#include "src\maths\maths.h"
#include "src\graphics\shader.h"
#include "src\graphics\Buffers\vertexbuffer.h"
#include "src\graphics\Buffers\vertexarray.h"
#include "src\graphics\Buffers\indexbuffer.h"

#include "src\graphics\BatchRenderer2D.h"
#include "src\graphics\sprite.h"
#include "src\graphics/renderable2D.h"

#include "src\utils\Timer.h"

#include "src\graphics\Layers\TileLayer.h"
#include "src\graphics\Layers\Group.h"

#include "src\graphics\Label.h"
#include "src\graphics\Font_Manager.h"

#include "src\audio\Sound.h"


int main()
{
	using namespace ferrari;
	using namespace graphics;
	using namespace maths;
	using namespace audio;
	
	Display window("Ferrari Engine", 960, 540);
	Sound::Init();
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	Sound sound("Evacuate", "Evacuate.wav");

	mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
	Shader& shader = *s;
	shader.Enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);
	
	Texture* textures[] =
	{
		new Texture("Yoshi.png"),
		new Texture("mario running.png"),
		new Texture("peacock feather.png")
	};

	for (float y = -9.0f; y < 9.0f; y += 1.0f)
	{
		for (float x = -16.0f; x < 16.0f; x += 1.0f)
		{
			int r = rand() % 256;

			int col = 0xffff00 << 8 | r;
			if (rand() % 4 == 0)
				layer.Add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
				layer.Add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

	FontManager::Add(new Font("SourceSansPro", "SourceSansPro-Light.ttf", 32));

	Group* g = new Group(maths::mat4::Translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label* fps = new Label("", 0.4f, 0.4f, FontManager::Get("SourceSansPro", 32) ,0xffffffff);
	g->Add(new Sprite(0, 0, 5, 1.5f, 0x505050dd));
	g->Add(fps);

	layer.Add(g);

	shader.Enable();
	shader.setUniformMat4("pr_matrix", ortho);

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float t = 0.0f;

	while (!window.Closed())
	{
		t += 0.001f;
		window.Clear(0, 0, 0, 0);

		if (window.isKeyPressed(GLFW_KEY_A))
		{
			sound.Loop();
		}

		if (window.isKeyPressed(GLFW_KEY_SPACE))
		{
			sound.Pause();
		}

		if (window.isKeyPressed(GLFW_KEY_S))
		{
			sound.Stop();
		}

		double xpos, ypos;
		window.GetMousePosition(xpos, ypos);

		shader.Enable();
		shader.setUniform2f("light_pos", vec2((float)(xpos * 32.0f / 960.0f - 16.0f) / 1.0f, (float)(9.0f - ypos * 18.0f / 540.0f) / 1.0f));
		
		layer.Render();

		const std::vector<Renderable2D*>& rs = layer.getRenderables();
		for (int i = 0; i < rs.size(); i++)
		{
			float c = sin(t) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(c, 0, 1, 1));
		}

		window.Update();
		Sound::Update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	for (int i = 0; i < 3; i++)
		delete textures[i];

	FontManager::Terminate();
	return 0;
}
#endif

//key inputs
/*
if (window.isKeyPressed(GLFW_KEY_A))
std::cout << "A!\n";

if (window.isKeyHeld(GLFW_KEY_B))
std::cout << "B!\n";

if (window.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
std::cout << "Left Button Clicked!\n";

if (window.isButtonHeld(GLFW_MOUSE_BUTTON_RIGHT))
std::cout << "Right Button Held!\n";
*/

//vector components and mathematics
/*
std::cout << vec2() << std::endl;
std::cout << vec2(5.0f) << std::endl;
std::cout << vec2(vec3(1.0f, 2.0f, 4.0f)) << std::endl;
std::cout << vec2(vec4(3.0f, 5.0f, 7.0f, 9.0f)) << std::endl;

std::cout << vec3() << std::endl;
std::cout << vec3(5.0f) << std::endl;
std::cout << vec3(4.0f, 6.0f, 8.0f) << std::endl;
std::cout << vec3(1.0f, 5.0f) << std::endl;
std::cout << vec3(vec2(1.0f, 2.0f)) << std::endl;
std::cout << vec3(vec4(6.0f, 5.0f, 2.0f, 1.0f)) << std::endl;

std::cout << vec4() << std::endl;
std::cout << vec4(6.0f) << std::endl;
std::cout << vec4(3.0f, 7.0f, 2.0f, 9.0f) << std::endl;
std::cout << vec4(vec2(1.0f, 2.0f), 3.0f, 4.0f) << std::endl;
std::cout << vec4(vec3(2.0f, 1.0f, 0.0f), 3.0f) << std::endl;
std::cout << vec4(vec2(3.0f, 7.0f)) << std::endl;
std::cout << vec4(vec3(9.0f, 8.0f, 7.0f)) << std::endl;

std::cout << "-----------------------------------------------------------------------\n";

std::cout << vec2::Up() << std::endl;
std::cout << vec2::Down() << std::endl;
std::cout << vec2::Left() << std::endl;
std::cout << vec2::Right() << std::endl;
std::cout << vec2::Zero() << std::endl;

std::cout << vec3::Up() << std::endl;
std::cout << vec3::Down() << std::endl;
std::cout << vec3::Left() << std::endl;
std::cout << vec3::Right() << std::endl;
std::cout << vec3::Near() << std::endl;
std::cout << vec3::Far() << std::endl;
std::cout << vec3::Zero() << std::endl;

std::cout << vec4::Up() << std::endl;
std::cout << vec4::Down() << std::endl;
std::cout << vec4::Left() << std::endl;
std::cout << vec4::Right() << std::endl;
std::cout << vec4::Near() << std::endl;
std::cout << vec4::Far() << std::endl;
std::cout << vec4::Zero() << std::endl;

std::cout << vec4::Up(1.0f) << std::endl;
std::cout << vec4::Down(1.0f) << std::endl;
std::cout << vec4::Left(1.0f) << std::endl;
std::cout << vec4::Right(1.0f) << std::endl;
std::cout << vec4::Near(1.0f) << std::endl;
std::cout << vec4::Far(1.0f) << std::endl;

std::cout << vec2::X_Axis() << std::endl;
std::cout << vec2::Y_Axis() << std::endl;

std::cout << vec3::X_Axis() << std::endl;
std::cout << vec3::Y_Axis() << std::endl;
std::cout << vec3::Z_Axis() << std::endl;

std::cout << vec4::X_Axis() << std::endl;
std::cout << vec4::Y_Axis() << std::endl;
std::cout << vec4::Z_Axis() << std::endl;

std::cout << vec4::X_Axis(1.0f) << std::endl;
std::cout << vec4::Y_Axis(1.0f) << std::endl;
std::cout << vec4::Z_Axis(1.0f) << std::endl;

std::cout << "-----------------------------------------------------------------------\n";

vec2 a(1.0, 2.0);
vec2 b(3.0, 4.0);
std::cout << a << '\n' << b << std::endl;

vec2 c = a + b;
std::cout << c << std::endl;
c = a - b;
std::cout << c << std::endl;
c = a * b;
std::cout << c << std::endl;
c = a / b;
std::cout << c << std::endl;

std::cout << "-----------------------------------------------------------------------\n";

vec3 d(1.0, 2.0, 3.0);
vec3 e(4.0, 5.0, 6.0);
std::cout << d << '\n' << e << std::endl;

vec3 f = d + e;
std::cout << f << std::endl;
f = d - e;
std::cout << f << std::endl;
f = d * e;
std::cout << f << std::endl;
f = d / e;
std::cout << f << std::endl;

vec4 g(1.0, 2.0, 3.0, 4.0);
vec4 h(5.0, 6.0, 7.0, 8.0);
std::cout << g << '\n' << h << std::endl;

vec4 i = g + h;
std::cout << i << std::endl;
i = g - h;
std::cout << i << std::endl;
i = g * h;
std::cout << i << std::endl;
i = g / h;
std::cout << i << std::endl;

std::cout << "-----------------------------------------------------------------------\n";

vec2 s(4.0f, 7.0f);
vec2 t(2.0f, 4.0f);
std::cout << (s == t) << std::endl;
std::cout << (s != t) << std::endl;
std::cout << (s < t) << std::endl;
std::cout << (s <= t) << std::endl;
std::cout << (s > t) << std::endl;
std::cout << (s >= t) << std::endl;

vec3 u(4.0f, 4.0f, 1.0f);
vec3 v(4.0f, 4.0f, 1.0f);
std::cout << (u == v) << std::endl;
std::cout << (u != v) << std::endl;
std::cout << (u < v) << std::endl;
std::cout << (u <= v) << std::endl;
std::cout << (u > v) << std::endl;
std::cout << (u >= v) << std::endl;

vec4 w(1.0f, 2.0f, 3.0f, 4.0f);
vec4 x(6.0f, 7.0f, 8.0f, 9.0f);
std::cout << (w == x) << std::endl;
std::cout << (w != x) << std::endl;
std::cout << (w < x) << std::endl;
std::cout << (w <= x) << std::endl;
std::cout << (w > x) << std::endl;
std::cout << (w >= x) << std::endl;

std::cout << "-----------------------------------------------------------------------\n";

vec2 j(3.0, 4.0);
std::cout << j.sqrLength() << std::endl;
std::cout << j.Length() << std::endl;
std::cout << j.Normalize() << std::endl;

vec3 k(3.0, 4.0, 5.0);
std::cout << k.sqrLength() << std::endl;
std::cout << k.Length() << std::endl;
std::cout << k.Normalize() << std::endl;

vec4 l(2.0, 3.0, 4.0, 5.0);
std::cout << l.sqrLength() << std::endl;
std::cout << l.Length() << std::endl;
std::cout << l.Normalize() << std::endl;

std::cout << "------------------------------------------------------------------------\n;

vec2 m(2.0, 3.0);
vec2 n(3.0, 4.0);
std::cout << m.Dot(n) << std::endl;
std::cout << m.cos_theta(n) << std::endl;
std::cout << m.Cross_Z(n) << std::endl;
std::cout << m.Cross_Pos(5) << std::endl;
std::cout << m.Cross_Neg(5) << std::endl;
std::cout << m.Distance(n) << std::endl;

vec3 o(2.0, 3.0, 4.0);
vec3 p(4.0, 5.0, 6.0);
std::cout << o.Dot(p) << std::endl;
std::cout << o.cos_theta(p) << std::endl;
std::cout << o.Cross(p) << std::endl;
std::cout << o.Distance(p) << std::endl;

vec4 q(2.0, 3.0, 4.0, 5.0);
vec4 r(4.0, 5.0, 6.0, 7.0);
std::cout << q.Dot(r) << std::endl;
std::cout << q.cos_theta(r) << std::endl;
std::cout << q.Distance(r) << std::endl;

std::cout << "------------------------------------------------------------------------\n;
*/

//matrix components and mathematics
/*
float a = 5;

std::cout << mat4() << std::endl;
std::cout << mat3() << std::endl;
std::cout << mat2() << std::endl;

std::cout << mat2(a) << std::endl;
std::cout << mat3(a) << std::endl;
std::cout << mat4(a) << std::endl;

std::cout << mat2(vec2(1, 2), vec2(3, 4)) << std::endl;
std::cout << mat3(vec3(1, 2, 3), vec3(4, 5, 6), vec3(7, 8, 9)) << std::endl;
std::cout << mat4(vec4(0, 1, 2, 3), vec4(4, 5, 6, 7), vec4(8, 9, 10, 11), vec4(12, 13, 14, 15)) << std::endl;

mat2 a1(1.0f, 2.0f, 3.0f, 4.0f);
std::cout << a1 << std::endl;
std::cout << a1.GetColumn(1) << std::endl;
a1.SetColumn(1, vec2(7, 6));
std::cout << a1 << std::endl;
std::cout << a1.GetRow(1) << std::endl;
a1.SetRow(1, vec2(56, 72));
std::cout << a1 << std::endl;

mat3 a2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
std::cout << a2 << std::endl;
std::cout << a2.GetColumn(2) << std::endl;
a2.SetColumn(2, vec3(100, 101, 102));
std::cout << a2 << std::endl;
std::cout << a2.GetRow(1) << std::endl;
a2.SetRow(1, vec3(56, 72, 49));
std::cout << a2 << std::endl;

mat4 a3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
std::cout << a3 << std::endl;
std::cout << a3.GetColumn(3) << std::endl;
a3.SetColumn(3, vec4(57, 38, 76, 109));
std::cout << a3 << std::endl;
std::cout << a3.GetRow(1) << std::endl;
a3.SetRow(1, vec4(34, 51, 30, 10));
std::cout << a3 << std::endl;

std::cout << mat2::Identity() << std::endl;
std::cout << mat3::Identity() << std::endl;
std::cout << mat4::Identity() << std::endl;

mat2 a4(5.0f, 6.0f, 7.0f, 8.0f);
std::cout << a1 * a4 << std::endl;

mat3 a5(10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 17.0f);
std::cout << a2 * a5 << std::endl;

mat4 a6(1.0f, 2.0f, 3.0f, 11.0f, 12.0f, 13.0f, 7.0f, 8.0f, 9.0f, 10.0f, 13.0f, 14.0f, 15.0f, 16.0f, 4.0f, 5.0f);
std::cout << a3 * a6 << std::endl;

std::cout << a4.Invert() << std::endl;
std::cout << a5.Invert() << std::endl;
std::cout << a6.Invert() << std::endl;

std::cout << a5.GetPosition() << std::endl;
a5.SetPosition(vec2(50, 60));
std::cout << a5 << std::endl;

std::cout << a6.GetPosition() << std::endl;
a6.SetPosition(vec3(30, 60, 90));
std::cout << a6 << std::endl;

mat4 a7(vec4(0, 1, 2, 3), vec4(4, 5, 6, 7), vec4(8, 9, 10, 11), vec4(12, 13, 14, 15));
mat3 a8(vec3(0, 1, 2), vec3(3, 4, 5), vec3(6, 7, 8));
mat2 a9(vec2(0, 1), vec2(2, 3));

std::cout << mat4::Orthographic(2, 4, 6, 8, 6, 4) << std::endl;
std::cout << mat4::Perspective(PI, 0.5, 2, 4) << std::endl;
std::cout << mat4::LookAt(vec3(2, 3, 4), vec3(3, 4, 0), vec3(2, 4, 6)) << std::endl;

std::cout << mat4::Translation(vec3(1, 2, 3)) << std::endl;
std::cout << mat3::Translation(vec2(4, 5)) << std::endl;

std::cout << mat4::Rotation(45, vec3(1, 1, 1)) << std::endl;
std::cout << mat3::Rotation(45, vec2(1, 1)) << std::endl;
std::cout << mat4::X_Rotation(45) << std::endl;
std::cout << mat4::Y_Rotation(45) << std::endl;
std::cout << mat4::Z_Rotation(45) << std::endl;
std::cout << mat3::C_Rotation(45) << std::endl;
std::cout << mat3::CC_Rotation(45) << std::endl;

std::cout << mat4::Scale(vec3(2, 4, 6)) << std::endl;
std::cout << mat3::Scale(vec2(2, 4)) << std::endl;

std::cout << mat4::X_Reflection() << std::endl;
std::cout << mat4::Y_Reflection() << std::endl;
std::cout << mat4::Z_Reflection() << std::endl;
std::cout << mat4::XY_Reflection() << std::endl;
std::cout << mat4::XZ_Reflection() << std::endl;
std::cout << mat4::YZ_Reflection() << std::endl;
std::cout << mat3::X_Reflection() << std::endl;
std::cout << mat3::Y_Reflection() << std::endl;
std::cout << mat3::PosX_Equal_Y_Reflection() << std::endl;
std::cout << mat3::NegX_Equal_Y_Reflection() << std::endl;

std::cout << mat4::Shear(2, 3, 4, 2, 1, 3) << std::endl;
std::cout << mat3::Shear(vec2(3, 4)) << std::endl;

std::cout << mat2::Invert(a9) << std::endl;
std::cout << mat3::Invert(a8) << std::endl;
std::cout << mat4::Invert(a7) << std::endl;

std::cout << mat2::Transpose(a9) << std::endl;
std::cout << mat3::Transpose(a8) << std::endl;
std::cout << mat4::Transpose(a7) << std::endl;
*/

//Quaternions
/*
std::cout << Quaternion() << std::endl;
std::cout << Quaternion(1, 2, 3, 4) << std::endl;
std::cout << Quaternion(Quaternion(5, 6, 7, 8)) << std::endl;
std::cout << Quaternion(vec2(2, 4), 7, 9) << std::endl;
std::cout << Quaternion(vec3(3, 5, 7), 9) << std::endl;
std::cout << Quaternion(vec4(1, 2, 4, 8)) << std::endl;
std::cout << Quaternion(8) << std::endl;
Quaternion a(0.3, 0.2, 0.1, 0.2);

std::cout << a << std::endl;
a.SetXYZ(vec3(0.1, 0.6, 0.3));
std::cout << a << std::endl;
std::cout << a.GetXYZ() << std::endl;

std::cout << a.SetElem(1, 0.2) << std::endl;
std::cout << a.GetElem(1) << std::endl;

std::cout << a.GetAxis() << std::endl;
std::cout << a.ToEulerAngles() << std::endl;


Quaternion b(0, 0, 0, 0);
std::cout << b << std::endl;
b = a;
std::cout << b << std::endl;

std::cout << a + b << std::endl;
std::cout << a - b << std::endl;
std::cout << a * b << std::endl;
std::cout << a / b << std::endl;

std::cout << a + 5 << std::endl;
std::cout << a - 5 << std::endl;
std::cout << a * 5 << std::endl;
std::cout << a / 5 << std::endl;

a += b;
std::cout << a << std::endl;
a -= b;
std::cout << a << std::endl;
a *= b;
std::cout << a << std::endl;
a /= b;
std::cout << a << std::endl;

a += 5;
std::cout << a << std::endl;
a -= 5;
std::cout << a << std::endl;
a *= 5;
std::cout << a << std::endl;
a /= 5;
std::cout << a << std::endl;

std::cout << (a == b) << std::endl;
std::cout << (a != b) << std::endl;

std::cout << -(a) << std::endl;

std::cout << a[2] << std::endl;

std::cout << Quaternion::Identity() << std::endl;

std::cout << Quaternion::FromEulerAngles(vec3(0.45, 0.9, 0.3)) << std::endl;
Quaternion c = Quaternion::FromEulerAngles(vec3(0.45, 0.9, 0.3));
std::cout << c.ToEulerAngles() << std::endl;

std::cout << Quaternion::RotationX(3.14 / 2) << std::endl;
std::cout << Quaternion::RotationY(3.14 / 2) << std::endl;
std::cout << Quaternion::RotationZ(3.14 / 2) << std::endl;

std::cout << Quaternion::Rotation(vec3(1, 1, 1), vec3(1, 1, 1)) << std::endl;
std::cout << Quaternion::Rotation(3.14 / 2, vec3(0.3, 0.45, 0.6)) << std::endl;
*/

//Shader
/*
GLfloat vertices[] =
{
-0.5f, -0.5f, +0.0f,
-0.5f, +0.5f, +0.0f,
+0.5f, +0.5f, +0.0f,
+0.5f, +0.5f, +0.0f,
+0.5f, -0.5f, +0.0f,
-0.5f, -0.5f, +0.0f
}; //These will be the vertices to draw the triangles that make up the square

GLuint vbo;
glGenBuffers(1, &vbo); //This creates an buffer array to store data to give to opengl
glBindBuffer(GL_ARRAY_BUFFER, vbo); //Selects the buffer array to be used at the current moment 
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); Subits the data to opengl
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Provides the list of data to be given to shader programs
glEnableVertexAttribArray(0); //Enables the pointer 
*/

//Shader demonstarting rotation, scaling, translating, projection, and lighting
/*
int main()
{
using namespace ferrari;
using namespace graphics;
using namespace maths;

Display window("Ferrari Engine", 960, 540);
glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

GLfloat vertices[] =
{
0, 0, 0,
8, 0, 0,
0, 3, 0,
0, 3, 0,
8, 3, 0,
8, 0, 0
};

GLuint vbo;
glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
glEnableVertexAttribArray(0);
Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
shader.Enable();
mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

float r = 0.0f, g = 0.0f, b = 0.0f;
bool red = false, blue = false, green = false;
float scalar = 2.0f;
bool size = false;
float x = 0.0f, y = 0.0f;
float angle = 0.0f;
//mat4 trans = mat4::Translation(vec3(x, y, 0));
while (!window.Closed())
{
window.Clear(0.2f, 0.3f, 0.8f, 1.0f);
glDrawArrays(GL_TRIANGLES, 0, 6);
mat4 trans = mat4::Translation(vec3(x, y, 0));
mat4 scale = mat4::Scale(scalar);
mat4 rot = mat4::Translation(vec3(4.0, 1.5, 0.0)) * mat4::Rotation(angle, vec3(0, 0, 1)) * mat4::Translation(vec3(-4, -1.5, 0));
if (r >= 1.0f)
red = false;
else if (r <= 0.0f)
red = true;
if (g >= 1.0f)
green = false;
else if (g <= 0.0f)
green = true;
if (b >= 1.0f)
blue = false;
else if (b <= 0.0f)
blue = true;

if (red == true && green == true && blue == true)
r += 0.002f;
else if (red == false && green == true && blue == true)
g += 0.002f;
else if (red == false && green == false && blue == true)
b += 0.002f;
else if (red == false && green == false && blue == false)
r -= 0.002f;
else if (red == true && green == false && blue == false)
g -= 0.002f;
else if (red == true && green == true && blue == false)
b -= 0.002f;

if (scalar >= 1.5f)
size = false;
else if (scalar <= 0.5f)
size = true;

if (size == false)
scalar -= 0.001f;
else if (size == true)
scalar += 0.001f;

if (window.isKeyHeld(GLFW_KEY_UP))
y += 0.01;
if (window.isKeyHeld(GLFW_KEY_DOWN))
y -= 0.01;
if (window.isKeyHeld(GLFW_KEY_LEFT))
x -= 0.01;
if (window.isKeyHeld(GLFW_KEY_RIGHT))
x += 0.01;

if (window.isKeyHeld(GLFW_KEY_Z))
angle += 0.1;
if (window.isKeyHeld(GLFW_KEY_X))
angle -= 0.1;

shader.setUniform2f("light_pos", vec2(x + 4, y + 1.5));
shader.setUniform4f("colour", vec4(r, g, b, 1.0));
shader.setUniformMat4("pr_matrix", ortho);
shader.setUniformMat4("vw_matrix", scale);
shader.setUniformMat4("ml_matrix", trans);
shader.setUniformMat4("rot_matrix", rot);
window.Update();

std::cout << x << ", " << y << std::endl;
}

return 0;
}
*/

//Implementation of Vertex Array Objects, Vertex Buffers, and Index Buffers
/*
int main()
{
using namespace ferrari;
using namespace graphics;
using namespace maths;

Display window("Ferrari Engine", 960, 540);
glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
#if 0
GLfloat vertices[] =
{
0, 0, 0,
8, 0, 0,
0, 3, 0,
0, 3, 0,
8, 3, 0,
8, 0, 0
};

GLuint vbo;
glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
glEnableVertexAttribArray(0);
#else
GLfloat vertices[] =
{
0, 0, 0,
0, 3, 0,
8, 3, 0,
8, 0, 0
};

GLushort indices[] =
{
0, 1, 2,
2, 3, 0
};

GLfloat colorsA[] =
{
0, 1, 0, 1,
1, 1, 0, 1,
0, 0, 1, 1,
1, 0, 0, 1,
};

GLfloat colorsB[] =
{
1, 1, 0, 1,
1, 0, 0, 1,
0, 0, 1, 1,
0, 1, 0, 1,
};

VertexArray sprite1, sprite2;
IndexBuffer ibo(indices, 6);

sprite1.addBuffer(new VertexBuffer(vertices, 4 * 3, 3), 0);
sprite1.addBuffer(new VertexBuffer(colorsA, 4 * 4, 4), 1);
sprite2.addBuffer(new VertexBuffer(vertices, 4 * 3, 3), 0);
sprite2.addBuffer(new VertexBuffer(colorsB, 4 * 4, 4), 1);

#endif
Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
shader.Enable();
mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

float r = 0.0f, g = 0.0f, b = 0.0f;
bool red = false, blue = false, green = false;
float scalar = 2.0f;
bool size = false;
float x = 0.0f, y = 0.0f;
float angle = 0.0f;
//mat4 trans = mat4::Translation(vec3(x, y, 0));
while (!window.Closed())
{
double xpos, ypos;
window.GetMousePosition(xpos, ypos);

mat4 trans = mat4::Translation(vec3(x, y, 0));
mat4 scale = mat4::Scale(1.0f);
mat4 rot = mat4::Translation(vec3(4.0, 1.5, 0.0)) * mat4::Rotation(angle, vec3(0, 0, 1)) * mat4::Translation(vec3(-4, -1.5, 0));
window.Clear(0.2f, 0.3f, 0.8f, 1.0f);
#if 0
glDrawArrays(GL_TRIANGLES, 0, 6);
#else
sprite1.Bind();
ibo.Bind();
shader.setUniform2f("light_pos", vec2((float)(xpos * 16.0f / 960.0f) / 1.0f, (float)(9.0f - ypos * 9.0f / 540.0f) / 1.0f));
shader.setUniform4f("colour", vec4(r, g, b, 1.0));
shader.setUniformMat4("pr_matrix", ortho);
shader.setUniformMat4("vw_matrix", scale);
shader.setUniformMat4("ml_matrix", trans);
shader.setUniformMat4("rot_matrix", rot);
glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
ibo.Unbind();
sprite1.Unbind();

sprite2.Bind();
ibo.Bind();
shader.setUniform2f("light_pos", vec2((float)(xpos * 16.0f / 960.0f) / 1.0f, (float)(9.0f - ypos * 9.0f / 540.0f) / 1.0f));
shader.setUniformMat4("pr_matrix", ortho);
shader.setUniformMat4("vw_matrix", scale);
shader.setUniformMat4("ml_matrix", mat4::Translation(vec3(5 + x, 6 + y, 0)));
shader.setUniformMat4("rot_matrix", rot);
glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
ibo.Unbind();
sprite2.Unbind();
#endif
if (r >= 1.0f)
red = false;
else if (r <= 0.0f)
red = true;
if (g >= 1.0f)
green = false;
else if (g <= 0.0f)
green = true;
if (b >= 1.0f)
blue = false;
else if (b <= 0.0f)
blue = true;

if (red == true && green == true && blue == true)
r += 0.002f;
else if (red == false && green == true && blue == true)
g += 0.002f;
else if (red == false && green == false && blue == true)
b += 0.002f;
else if (red == false && green == false && blue == false)
r -= 0.002f;
else if (red == true && green == false && blue == false)
g -= 0.002f;
else if (red == true && green == true && blue == false)
b -= 0.002f;

if (scalar >= 1.5f)
size = false;
else if (scalar <= 0.5f)
size = true;

if (size == false)
scalar -= 0.001f;
else if (size == true)
scalar += 0.001f;

if (window.isKeyHeld(GLFW_KEY_UP))
y += 0.01;
if (window.isKeyHeld(GLFW_KEY_DOWN))
y -= 0.01;
if (window.isKeyHeld(GLFW_KEY_LEFT))
x -= 0.01;
if (window.isKeyHeld(GLFW_KEY_RIGHT))
x += 0.01;

if (window.isKeyHeld(GLFW_KEY_Z))
angle += 0.1;
if (window.isKeyHeld(GLFW_KEY_X))
angle -= 0.1;

std::cout << xpos << ", " << ypos << std::endl;
window.Update();

}

return 0;
}
*/

//Using the renderer to display over 50000 tiny squares on screen
/*
int main()
{
using namespace ferrari;
using namespace graphics;
using namespace maths;

Display window("Ferrari Engine", 960, 540);
glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
mat4 trans = mat4::Translation(vec3(0, 0, 0));
mat4 scale = mat4::Scale(1.0f);
mat4 rot = mat4::Translation(vec3(4.0, 1.5, 0.0)) * mat4::Rotation(0.0f, vec3(0, 0, 1)) * mat4::Translation(vec3(-4, -1.5, 0));

Shader shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
shader.Enable();

window.Clear(0.2f, 0.3f, 0.8f, 1.0f);

shader.setUniform4f("colour", vec4(0.0f, 1.0f, 1.0f, 1.0));
shader.setUniformMat4("pr_matrix", ortho);
shader.setUniformMat4("vw_matrix", 1.0f);
shader.setUniformMat4("ml_matrix", trans);
shader.setUniformMat4("rot_matrix", rot);

std::vector<Renderable2D*> sprites;
unsigned int color;
for (float y = 0; y < 9.0f; y += 0.05)
{
for (float x = 0; x < 16.0f; x += 0.05)
{
color = rand() % 256 << 24 | rand() % 256 << 16 | rand() % 256 << 8 | rand() % 256;
sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, color));
}
}
BatchRenderer2D renderer;

while (!window.Closed())
{
double xpos, ypos;
window.GetMousePosition(xpos, ypos);
shader.setUniform2f("light_pos", vec2((float)(xpos * 16.0f / 960.0f) / 1.0f, (float)(9.0f - ypos * 9.0f / 540.0f) / 1.0f));
window.Clear(0, 0 , 0 ,0);

renderer.Begin();
for (int i = 0; i < sprites.size(); i++)
{
renderer.Submit(sprites[i]);
}
renderer.End();
renderer.Flush();

printf("Sprites: %d\n", sprites.size());

window.Update();
}

return 0;
}
*/

//Layer Implementation
/*
int main()
{
using namespace ferrari;
using namespace graphics;
using namespace maths;

Display window("Ferrari Engine", 960, 540);
//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

Shader* s = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
Shader& shader = *s;
shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
shader.Enable();

Shader* s2 = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
Shader& shader2 = *s2;

TileLayer layer(&shader);
unsigned int color = 255 << 24 | 255 << 16 | 0 << 8 | rand() % 256;
for (float y = -9.0f; y < 9.0f; y += 0.10f)
{
for (float x = -16.0f; x < 16.0f; x += 0.10f)
{
layer.Add(new Sprite(x, y, 0.09f, 0.09f, 255 << 24 | 255 << 16 | 0 << 8 | rand() % 256));
}
}

shader2.Enable();
shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));

TileLayer layer2(&shader2);
layer2.Add(new Sprite(-2, -2, 4, 4, 0xffff00ff));

Timer time;
float timer = 0;
unsigned int frames = 0;
float times = 0.0f;

while (!window.Closed())
{
window.Clear(0, 0, 0, 0);

double xpos, ypos;
window.GetMousePosition(xpos, ypos);
shader.Enable();
shader.setUniform2f("light_pos", vec2((float)(xpos * 32.0f / 960.0f - 16.0f) / 1.0f, (float)(9.0f - ypos * 18.0f / 540.0f) / 1.0f));
shader2.Enable();
shader2.setUniform2f("light_pos", vec2((float)(xpos * 32.0f / 960.0f - 16.0f), (float)(9.0f - ypos * 18.0f / 540.0f)));

layer.Render();
layer2.Render();

window.Update();
frames++;
if (time.elapsed() - timer > 1.0f)
{
timer += 1.0f;
printf("%d fps\n", frames);
frames = 0;
}
}

return 0;
}
*/

//The transformation stack allows the user to position and rotate matrices around specific object

//Implementation of groups, tranformations of objects around a specific object
/*
int main()
{
using namespace ferrari;
using namespace graphics;
using namespace maths;

Display window("Ferrari Engine", 960, 540);
//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

Shader* s = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
Shader* s2 = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
Shader& shader = *s;
Shader& shader2 = *s2;
shader.Enable();
shader2.Enable();
shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));


TileLayer layer(&shader);
#if 0
for (float y = -9.0f; y < 9.0f; y += 0.10f)
{
for (float x = -16.0f; x < 16.0f; x += 0.10f)
{
layer.Add(new Sprite(x, y, 0.09f, 0.09f, 255 << 24 | 255 << 16 | 0 << 8 | rand() % 256));
}
}
#else
Group* group = new Group(mat4::Translation(maths::vec3(-15.0f, 5.0f, 0.0f)) * mat4::Rotation(45, vec3(0, 0, 1)));
group->Add(new Sprite(0, 0, 6, 3, 0xffffffff));

Group* button = new Group(mat4::Translation(vec3(0.5f, 0.5f, 0.0f)));
button->Add(new Sprite(0, 0, 5.0f, 2.0f, 0xffff00ff));
button->Add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, 0xff501e14));
group->Add(button);

layer.Add(group);
#endif

TileLayer layer2(&shader2);
layer2.Add(new Sprite(-2, -2, 4, 4, 0xffff00ff));

Timer time;
float timer = 0;
unsigned int frames = 0;

while (!window.Closed())
{
window.Clear(0, 0, 0, 0);

double xpos, ypos;
window.GetMousePosition(xpos, ypos);

shader.Enable();
shader.setUniform2f("light_pos", vec2((float)(xpos * 32.0f / 960.0f - 16.0f) / 1.0f, (float)(9.0f - ypos * 18.0f / 540.0f) / 1.0f));
//shader2.Enable();
//shader2.setUniform2f("light_pos", vec2((float)(xpos * 32.0f / 960.0f - 16.0f), (float)(9.0f - ypos * 18.0f / 540.0f)));

layer.Render();
//layer2.Render();

window.Update();
frames++;
if (time.elapsed() - timer > 1.0f)
{
timer += 1.0f;
printf("%d fps\n", frames);
frames = 0;
}
}

return 0;
}
*/

//Implementation of textures and texture arrays
/*
int main()
{
using namespace ferrari;
using namespace graphics;
using namespace maths;

Display window("Ferrari Engine", 960, 540);
//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

Shader* s = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
Shader& shader = *s;
shader.Enable();
shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

TileLayer layer(&shader);

Texture* textures[] =
{
new Texture("Yoshi.png"),
new Texture("mario running.png"),
new Texture("peacock feather.png")
};

Texture* tex1 = new Texture("Yoshi.png");

for (float y = -9.0f; y < 9.0f; y += 1.0f)
{
for (float x = -16.0f; x < 16.0f; x += 1.0f)
{
if (rand() % 3 == 0)
layer.Add(new Sprite(x, y, 0.9f, 0.9f, 255 << 24 | 255 << 16 | 0 << 8 | rand() % 256));
else
layer.Add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));

}
}

GLint texIds[] =
{
0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

shader.Enable();
shader.setUniform1iv("textures", texIds, 10);
//shader.setUniformMat4("pr_matrix", ortho);

Timer time;
float timer = 0;
unsigned int frames = 0;

while (!window.Closed())
{
window.Clear(0, 0, 0, 0);

double xpos, ypos;
window.GetMousePosition(xpos, ypos);

shader.Enable();
shader.setUniform2f("light_pos", vec2((float)(xpos * 32.0f / 960.0f - 16.0f) / 1.0f, (float)(9.0f - ypos * 18.0f / 540.0f) / 1.0f));

layer.Render();
//layer2.Render();

window.Update();
frames++;
if (time.elapsed() - timer > 1.0f)
{
timer += 1.0f;
printf("%d fps\n", frames);
frames = 0;
}
}

for (int i = 0; i < 3; i++)
delete textures[i];

return 0;
}
*/

//Initializing and implementation of sounds
/*
int main()
{
using namespace ferrari;
using namespace graphics;
using namespace maths;
using namespace audio;

Display window("Ferrari Engine", 960, 540);
Sound::Init();
glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

Sound sound("Shuffle", "questions_money.wav");

mat4 ortho = mat4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

Shader* s = new Shader("src/shaders/latest/basic.vert", "src/shaders/latest/basic.frag");
Shader& shader = *s;
shader.Enable();
shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

TileLayer layer(&shader);

Texture* textures[] =
{
new Texture("Yoshi.png"),
new Texture("mario running.png"),
new Texture("peacock feather.png")
};

for (float y = -9.0f; y < 9.0f; y += 1.0f)
{
for (float x = -16.0f; x < 16.0f; x += 1.0f)
{
int r = rand() % 256;

int col = 0xffff00 << 8 | r;
if (rand() % 4 == 0)
layer.Add(new Sprite(x, y, 0.9f, 0.9f, col));
else
layer.Add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
}
}

FontManager::Add(new Font("SourceSansPro", "SourceSansPro-Light.ttf", 32));

Group* g = new Group(maths::mat4::Translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
Label* fps = new Label("", 0.4f, 0.4f, FontManager::Get("SourceSansPro", 32) ,0xffffffff);
g->Add(new Sprite(0, 0, 5, 1.5f, 0x505050dd));
g->Add(fps);

layer.Add(g);

GLint texIds[] =
{
0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

shader.Enable();
shader.setUniform1iv("textures", texIds, 10);
//shader.setUniformMat4("pr_matrix", ortho);

Timer time;
float timer = 0;
unsigned int frames = 0;
float t = 0.0f;

while (!window.Closed())
{
t += 0.001f;
window.Clear(0, 0, 0, 0);

if (window.isKeyPressed(GLFW_KEY_A))
{
sound.Loop();
}

if (window.isKeyPressed(GLFW_KEY_SPACE))
{
sound.Pause();
}

if (window.isKeyPressed(GLFW_KEY_S))
{

sound.Stop();
}

double xpos, ypos;
window.GetMousePosition(xpos, ypos);

shader.Enable();
shader.setUniform2f("light_pos", vec2((float)(xpos * 32.0f / 960.0f - 16.0f) / 1.0f, (float)(9.0f - ypos * 18.0f / 540.0f) / 1.0f));

layer.Render();

const std::vector<Renderable2D*>& rs = layer.getRenderables();
for (int i = 0; i < rs.size(); i++)
{
float c = sin(t) / 2 + 0.5f;
rs[i]->setColor(maths::vec4(c, 0, 1, 1));
}

window.Update();
Sound::Update();

frames++;
if (time.elapsed() - timer > 1.0f)
{
timer += 1.0f;
fps->text = std::to_string(frames) + " fps";
printf("%d fps\n", frames);
frames = 0;
}
}

for (int i = 0; i < 3; i++)
delete textures[i];

FontManager::Terminate();
return 0;
}
*/