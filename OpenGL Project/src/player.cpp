#include "player.h"
#include <cglm/vec3.h>
Player::Player()
{
}

void Player::Move(glm::vec2 direction, float dt)
{
	glm::vec3 move = glm::vec3(direction.x, 0, -direction.y);
	if (glm::length2(move) == 0.0f)
		return;
	move = glm::normalize(move);
	glm::quat rotation = glm::quat(glm::vec3(0, glm::radians(cam->yaw), 0));
	move = rotation * move;
	position += move * speed * dt;
}

void Player::Look(glm::vec2 mousePos)
{
	cam->position = position + camOffset;
	if (firstMouse)
	{
		lastMouse = mousePos;
		firstMouse = false;
	}

	float xoffset = mousePos.x - lastMouse.x;
	float yoffset = lastMouse.y - mousePos.y;
	lastMouse.x = mousePos.x;
	lastMouse.y = mousePos.y;

	cam->yaw -= xoffset * sensitivity;
	cam->pitch += yoffset * sensitivity;
	if (cam->yaw > 360) cam->yaw -= 360;
	if (cam->yaw < 0) cam->yaw += 360;
	if (cam->pitch > 89.0f) cam->pitch = 89.0f;
	if (cam->pitch < -89.0f) cam->pitch = -89.0f;
}
