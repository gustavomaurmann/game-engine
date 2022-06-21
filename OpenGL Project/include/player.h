#ifndef PLAYER_H
#define PLAYER_H
#include <glm/glm.hpp>
#include "camera.h"

class Player
{
public:
	// Movement values
	float gravity = 20.0f;
	float friction = 6;
	float moveSpeed = 7.0f;
	float runAcceleration = 14.0f; 
	float runDeacceleration = 10.0f;
	float airControl = 0.3f;
	float sideStrafeAcceleration = 50.0f;
	float sideStrafeSpeed = 1.0f;
	float jumpSpeed = 8.0f;

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 camOffset = glm::vec3(0, 2, 0);

	// velocity
	glm::vec3 moveDir, velocity;

	float sensitivity = 0.1f;
	Player();
	~Player();
	Camera *cam;
	void SetMovementDir(glm::vec2 direction);
	void Move(float dt);
	void Look(glm::vec2 mousePos);
private: 
	glm::vec2 lastMouse;
	bool firstMouse = true;
	bool isGrounded();
	// movement
	void GroundMove(float dt);
	void AirMove(float dt);
	void AirControl(float dt);
	void ApplyFriction(float t, float dt);
	void Accelerate(glm::vec3 wishdir, float wishspeed, float accel, float dt);
};
#endif

