#pragma once
#include "shader.h"

namespace ferrari {
	namespace graphics {
		namespace ShaderFactory {
			Shader* DefaultShader();
			Shader* BasicLightShader();
		}
	}
}