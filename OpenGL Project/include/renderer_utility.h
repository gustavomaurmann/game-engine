#ifndef RENDERER_UTILITY_H
#define RENDERER_UTILITY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"
#include "shader.h"
class RendererUtility
{
public:
	static void DrawVBO(Shader* shader);
	static void DrawSprite(glm::vec3 position, glm::quat rotation, glm::vec3 size, Texture2D texture, Shader shader);
private:
	//static void InitPrimitives()
	// primitives
};

#endif