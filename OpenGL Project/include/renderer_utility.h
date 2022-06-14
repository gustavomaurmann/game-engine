#ifndef RENDERER_UTILITY_H
#define RENDERER_UTILITY_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

namespace Rendering
{
	class RendererUtility
	{
	public:
		static void DrawVBO(Shader* shader);
	private:
		//static void InitPrimitives()
		// primitives
	};
}
#endif

