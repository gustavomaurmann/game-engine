#ifndef PLAYER_H
#define PLAYER_H
#include <glm/glm.hpp>
#include "camera.h"

class Player
{
public:
	glm::vec3 position;
	glm::vec3 camOffset = glm::vec3(0, 2, 0);

	float speed = 5;
	float sensitivity = 0.1f;
	Player();
	~Player();
	Camera *cam;
	void Move(glm::vec2 direction, float dt);
	void Look(glm::vec2 mousePos);
private: 
	glm::vec2 lastMouse;
	bool firstMouse = true;
};
#endif

