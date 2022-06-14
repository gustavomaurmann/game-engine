#include "renderer_utility.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include "vertex.h"


void RendererUtility::DrawVBO(Shader* shader)
{
}

void RendererUtility::DrawSprite(glm::vec3 position, glm::quat rotation, glm::vec3 size, Texture2D texture, Shader shader)
{
	// note: making this draw from the center. When I implement sprite objects and assets I will change this to take offset values and pivots
	// create buffer
	Vertex buffer[6];

	Vertex v1, v2, v3, v4;
	v1.Position = position + glm::vec3(-size.x / 2, -size.y / 2, 0);
	v1.TexCoords = glm::vec2(0.0f, 0.0f);

	v2.Position = position + glm::vec3(size.x / 2, -size.y / 2, 0);
	v2.TexCoords = glm::vec2(1.0f, 0.0f);

	v3.Position = position + glm::vec3(-size.x / 2, size.y / 2, 0);
	v3.TexCoords = glm::vec2(0.0f, 1.0f);

	v4.Position = position + glm::vec3(size.x / 2, size.y / 2, 0);
	v4.TexCoords = glm::vec2(1.0f, 1.0f);

	buffer[0] = v1;
	buffer[1] = v2;
	buffer[2] = v3;
	buffer[3] = v2;
	buffer[4] = v3;
	buffer[5] = v4;

	// set shader transforms
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	// translate
	model = glm::translate(model, position);
	// rotate
	model *= glm::mat4_cast(rotation);
	// scale
	model = glm::scale(model, size);

	shader.SetMatrix4("model", model);

	//set texture
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	unsigned int VAO;
	GLuint VBO;
	// create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), &buffer[0], GL_STATIC_DRAW);
	// bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// texpos attrib
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// sprite, so no normals
	// free memory
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

