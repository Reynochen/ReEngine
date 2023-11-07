#include "Camera.hpp"

void Camera::update() {
    if(EnableMove) {
        updateMouseMove();
        updateMove();
    }
    
    updateVectors();

    glm::mat4 view = glm::lookAt(Position, Position + Front, Up);
    glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)Window::getWidth()/(float)Window::getHeight(), 0.04f, 1000.0f);
    // glm::mat4 proj = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
    shader->setMat4("view", view);
    shader->setMat4("projection", proj);
}

void Camera::updateMouseMove(GLboolean constrainPitch) {
    float xoffset = Events::getDeltaX() * MouseSensitivity;
    float yoffset = Events::getDeltaY() * MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }
}

void Camera::updateMove() {
    float velocity = MovementSpeed * Events::getDeltaTime();

    if(Events::pressed(GLFW_KEY_W)) Position += Front * velocity;
    if(Events::pressed(GLFW_KEY_S)) Position -= Front * velocity;
    if(Events::pressed(GLFW_KEY_A)) Position -= Right * velocity;
    if(Events::pressed(GLFW_KEY_D)) Position += Right * velocity;
}

void Camera::updateVectors() {
    glm::vec3 newFront;

    newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    newFront.y = sin(glm::radians(Pitch));
    newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(newFront);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}