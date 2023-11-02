#include "Application.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Graphics.hpp"
#include "Camera.hpp"
#include "Events.hpp"
#include "Model.hpp"

#include <math.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OBJLoader.hpp"
#include "Entity.hpp"
#include "ENTManager.hpp"

Application::Application() {
    Window::initialization(640, 480, "ReEngine", 0);
    Events::initialization(Window::getWindow());

    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    Window::swapBuffers();
    Window::swapBuffers();
}

Application::~Application() {
    Window::terminate();
}

void Application::run() {
    ENTManager ENTMng;

    Model monkey(glm::vec3(5.f, 0.f, 0.f), "res/amogus.png", "res/amogus.png", "res/models/monke.obj");

    Shader shader("res/shaders/mainShader/main.vs", "res/shaders/mainShader/main.fs"); //Create shader
    Camera camera(shader); //Create camera

    Entity* entity;
    while (!Window::shouldClose())
    {
        camera.update();

        if (Events::pressed(GLFW_KEY_ESCAPE)) {
            Window::shouldClose(true);
        }
        if (Events::jpressed(GLFW_KEY_0))
            ENTMng.addEntity(camera.getPos(), "Dominus\\dominus.obj");

        shader.use();
        shader.setFloat("time", (float)glfwGetTime());
        shader.setVec3("viewPos", camera.Position);
        ENTMng.renderEntities(shader);

        entity = ENTMng.getEntity(0);
        if (entity != nullptr)
            entity->rotation = glm::vec3(0.f, sin((float)glfwGetTime()*glm::radians(50.f))*5 ,0.f);
        
        monkey.rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);
        monkey.render(&shader);

        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() {
    Application* app = new Application;
    return app;
}