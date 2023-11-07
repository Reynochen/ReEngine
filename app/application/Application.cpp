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

#include "Entity.hpp"
#include "ENTController.hpp"

Application::Application() {
    Window::initialization(640, 480, "ReEngine", 0);
    Events::initialization(Window::getWindow());

    Window::swapBuffers();
    Window::swapBuffers();
}

Application::~Application() {
    Window::terminate();
}

void Application::run() {
    ENTController ENTCtrl;
    ENTCtrl.addEntity(glm::vec3(5.f, 0.f, 0.f), "Monke\\monke.obj", "res/amogus.png");

    Shader shader("res/shaders/mainShader/main.vs", "res/shaders/mainShader/main.fs"); //Create shader
    Camera camera(shader); //Create camera

    Entity* entity;
    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    while (!Window::shouldClose())
    {
        camera.update();

        if (Events::pressed(GLFW_KEY_ESCAPE)) {
            Window::shouldClose(true);
        }
        if (Events::jpressed(GLFW_KEY_Z))
            ENTCtrl.removeEntity();
        if (Events::jpressed(GLFW_KEY_0))
            ENTCtrl.addEntity(camera.getPos(), "Dominus\\dominus.obj");
        if (Events::jpressed(GLFW_KEY_SLASH)) {
            camera.EnableMove = !camera.EnableMove;
            Events::hideMouse(camera.EnableMove); 
        }

        shader.use();
        shader.setFloat("time", (float)glfwGetTime());
        shader.setVec3("viewPos", camera.Position);

        entity = ENTCtrl.getEntity(0);
        if (entity != nullptr)
            entity->rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);
        
        entity = ENTCtrl.getEntity(1);
        if (entity != nullptr)
            entity->rotation = glm::vec3(0.f, sin((float)glfwGetTime()*glm::radians(50.f))*5 ,0.f);

        ENTCtrl.renderEntities(shader);
        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() {
    Application* app = new Application;
    return app;
}