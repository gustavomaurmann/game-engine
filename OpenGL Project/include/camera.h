#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 8;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    bool orthoView;
    float Yaw;
    float Pitch;
    glm::quat rotation;
    bool firstMouse = true;
    glm::vec2 lastMousePos;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    bool mouseEnabled;
    bool zoomEnabled;
    bool wasdEnabled;

    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(glm::vec2 mousePos);
    void ProcessMouseScroll(float yoffset);

    void updateCameraVectors();
    void RotateCamera(float xoffset, float yoffset, bool constrainPitch = true);
};
#endif

