#include "player.h"
#include <cglm/vec3.h>
#include <iostream>
Player::Player()
{
	velocity = glm::vec3(1, 0, 0);
}
void Player::Move(float dt)
{
	if (isGrounded())
	{
		GroundMove(dt);
	}
	else
	{
		AirMove(dt);
	}

	// apply velocity
	position.x += velocity.x * dt;
	position.z += velocity.z * dt;
}
void Player::SetMovementDir(glm::vec2 direction)
{
	moveDir = glm::vec3(direction.x, 0, -direction.y);
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

	rotation = glm::quat(glm::vec3(0, glm::radians(cam->yaw), 0));
}
bool Player::isGrounded()
{
	if (position.y > 0) return false;
	return true;
}
void Player::GroundMove(float dt)
{
	ApplyFriction(1.0f, dt);

	glm::vec3 wishDir = glm::vec3(moveDir.x, 0, moveDir.z);
	if (glm::length2(moveDir) == 0.0f)
		return;
	wishDir = rotation * wishDir;
	wishDir = glm::normalize(wishDir);

	float wishSpeed = glm::length(wishDir);
	wishSpeed *= moveSpeed;

	Accelerate(wishDir, wishSpeed, runAcceleration, dt);
	
	// gravity
	velocity.y = -gravity * dt;
}
void Player::AirMove(float dt)
{
}
void Player::AirControl(float dt)
{
}
void Player::ApplyFriction(float t, float dt)
{
	glm::vec3 vec = glm::vec3(velocity.x, velocity.y, velocity.z);
	float speed, newspeed, control, drop;

	vec.y = 0.0f;
	speed = glm::length(vec);
	drop = 0.0f;

	/* Only if the player is on the ground then apply friction */
	if (isGrounded())
	{
		control = (speed < runDeacceleration) ? runDeacceleration : speed;
		drop = control * friction * dt * t;
	}

	newspeed = speed - drop;
	if (newspeed < 0)
		newspeed = 0;
	if (speed > 0)
		newspeed /= speed;
	velocity.x *= newspeed;
	velocity.z *= newspeed;
}
void Player::Accelerate(glm::vec3 wishdir, float wishspeed, float accel, float dt)
{
	float addspeed;
	float accelspeed;
	float currentspeed;
	currentspeed = glm::dot(velocity, wishdir);
	addspeed = wishspeed - currentspeed;
	if (addspeed <= 0) return;
	accelspeed = accel * dt * wishspeed;
	if (accelspeed > addspeed)
		accelspeed = addspeed;

	velocity.x += accelspeed * wishdir.x;
	velocity.z += accelspeed * wishdir.z;

	glm::vec2 nVel = glm::vec2(velocity.x, velocity.y);
	if (!isGrounded())
	{
		float clampSpeed = glm::length(velocity);
		if (clampSpeed > moveSpeed) clampSpeed = moveSpeed;
		if (clampSpeed < 0) clampSpeed = 0;
		nVel = glm::normalize(nVel) * clampSpeed;
		velocity.x = nVel.x;
		velocity.z = nVel.y;
	}
}
