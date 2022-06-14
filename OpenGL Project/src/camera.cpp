#include "camera.h"

Camera::Camera()
{
    Yaw = 0;
    Pitch = 0;
    MouseSensitivity = SENSITIVITY;;
    MovementSpeed = SPEED;
    Zoom = ZOOM;
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    updateCameraVectors();
}
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}
glm::mat4 Camera::GetProjectionMatrix()
{
    if (orthoView)
    {
        float ratio = 800.0f / 600.0f;
        return glm::ortho(-ratio * Zoom/20, ratio * Zoom / 20, -ratio * Zoom / 20, ratio * Zoom / 20, -1000.0f, 1000.0f);
    }   
    return glm::perspective(glm::radians(Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
}
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    if (!wasdEnabled)
        return;
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 wDirection = Front;
    if (orthoView)
        wDirection = Up;
    if (direction == FORWARD)
        Position += glm::vec3(0, 0, 1) * velocity;
    if (direction == BACKWARD)
        Position += glm::vec3(0, 0, -1) * velocity;
    if (direction == LEFT)
        Position += glm::vec3(1, 0, 0) * velocity;
    if (direction == RIGHT)
        Position += glm::vec3(-1, 0, 0) * velocity;
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    if (!mouseEnabled)
        return;
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    if (firstMouse) // initially set to true
    {
        firstMouse = false;
    }
    else
    {
        Yaw += xoffset;
        Pitch += yoffset;
    }

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (!orthoView)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset)
{
    if (!zoomEnabled)
        return;
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}