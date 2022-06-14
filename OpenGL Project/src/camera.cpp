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
    // assuming 16:9 perspective. change later to take into account window aspect ratio
    float ratio = 1.77778f;
    if (orthoView)
    {
        return glm::ortho(-ratio * Zoom/20, ratio * Zoom / 20, -ratio * Zoom / 20, ratio * Zoom / 20, -1000.0f, 1000.0f);
    }   
    return glm::perspective(glm::radians(Zoom), ratio, 0.1f, 100.0f);
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
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position += -Front * velocity;
    if (direction == LEFT)
        Position += -Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}
void Camera::ProcessMouseMovement(glm::vec2 mousePos)
{
    if (!mouseEnabled)
        return;
    if (firstMouse)
    {
        lastMousePos = mousePos;
        firstMouse = false;
    }
    glm::vec2 delta = lastMousePos - mousePos;
    lastMousePos = mousePos;
    RotateCamera(delta.x, delta.y);
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

}

void Camera::RotateCamera(float xoffset, float yoffset, bool constrainPitch)
{
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

    rotation = glm::quat(glm::vec3(glm::radians(Pitch), glm::radians(Yaw), 0));
    // update Front, Right and Up Vectors using the updated Euler angles
    Front = rotation * glm::vec3(0, 0, -1);
    Right = rotation * glm::vec3(1, 0, 0);
    Up = rotation * glm::vec3(0, 1, 0);
}
