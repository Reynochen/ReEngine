#ifndef CAMERA
#define CAMERA

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>

#include "Events.hpp"
#include "Window.hpp"
#include "Shader.hpp"

const float YAW = -90.0F;
const float PITCH = 0.0f;
const float SPEED = 7.0f;
const float SENSITIVITY = 0.15f;
const float ZOOM = 90.0f;

class Camera
{
public:
    glm::vec3 Position, Front, Up, Right, WorldUp;
    glm::mat4 view, proj;
    bool EnableMove = true;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    glm::mat4 lookAtMat;
    Shader* shader;

    Camera(Shader& shader, glm::vec3 position = glm::vec3(0.0f, 0.0f, +3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        this->shader = &shader;
        updateVectors();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::vec3 getPos() { 
        return Position; 
    }

    void update();

private:
    void updateMouseMove(GLboolean constrainPitch = true);

    void updateMove();

    void updateVectors();
};


#endif