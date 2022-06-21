#include "camera.h"

Camera::Camera()
{
}
glm::mat4 Camera::GetViewMatrix()
{   
    rotation = glm::quat(glm::vec3(glm::radians(pitch), glm::radians(yaw), 0));
    front = rotation * glm::vec3(0, 0, -1);
    up = rotation * glm::vec3(0, 1, 0);
    return glm::lookAt(position,position + front,up);
}
glm::mat4 Camera::GetProjectionMatrix()
{    
    // assuming 16:9 perspective. change later to take into account window aspect ratio
    float ratio = 1.77778f;
    return glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
}