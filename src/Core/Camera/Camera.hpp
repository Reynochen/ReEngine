#ifndef CAMERA
#define CAMERA

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>

#include "Events.hpp"

const float YAW = -90.0F;
const float PITCH = 0.0f;
const float SPEED = 7.0f;
const float SENSITIVITY = 0.4f;
const float ZOOM = 90.0f;

class Camera
{
public:
    glm::vec3 Position, Front, Up, Right, WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    glm::mat4 lookAtMat;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, +3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateVectors();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void update() {
        updateMouseMove();
        updateMove();
    }

private:
    void updateMouseMove(GLboolean constrainPitch = true) {
        float xoffset = Events::getDeltaX() * MouseSensitivity;
        float yoffset = Events::getDeltaY() * MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch) {
            if (Pitch > 89.0f) Pitch = 89.0f;
            if (Pitch < -89.0f) Pitch = -89.0f;
        }

        updateVectors();
    }

    void updateMove() {
        float velocity = MovementSpeed * Events::getDeltaTime();

        if(Events::pressed(GLFW_KEY_W)) Position += Front * velocity;
        if(Events::pressed(GLFW_KEY_S)) Position -= Front * velocity;
        if(Events::pressed(GLFW_KEY_A)) Position -= Right * velocity;
        if(Events::pressed(GLFW_KEY_D)) Position += Right * velocity;
    }

    void updateVectors() {
        glm::vec3 newFront;

        newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        newFront.y = sin(glm::radians(Pitch));
        newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(newFront);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};


#endif