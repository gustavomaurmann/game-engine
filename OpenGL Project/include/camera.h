#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>


class Camera
{
public:
    glm::vec3 position;
    glm::quat rotation;
    float yaw, pitch;
    float fov;
    glm::vec3 front, up;
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
};
#endif

