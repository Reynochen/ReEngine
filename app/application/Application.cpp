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

#include "GUI.hpp"

Application::Application() 
{
    Window::initialization(640, 480, "ReEngine", 0);
    Events::initialization(Window::getWindow());

    Window::swapBuffers();
    Window::swapBuffers();
}

Application::~Application() 
{
    Window::terminate();
}

void Application::run() 
{
    //GUI widget test
    GUI GUItest(0.15, glm::vec4(glm::vec3(0.0f), 0.5f), false);
    GUI GUItest2(0.15, glm::vec4(glm::vec3(1.f, 0.f, 1.f), 1.f), false);
    GUItest2.flexible = false;
    GUItest.setX(1);
    // GUItest.width = 53;
    // GUItest.height = 25;

    //Entities controller
    ENTController ENTCtrl;
    ENTCtrl.addEntity(glm::vec3(5.f, 0.f, 0.f), "Monke\\monke.obj", "res/Texture/amogus.png");

    //Shaders
    Shader shader("res/shaders/main/main.vs", "res/shaders/main/main.fs");
    Shader GUIshader("res/shaders/GUI/main.vs", "res/shaders/GUI/main.fs");
    Camera camera(shader); //Create camera
    float xGUI = 0;
    Entity* entity;
    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    while (!Window::shouldClose())
    {
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
            GUItest.Enable = !GUItest.Enable;
            GUItest2.Enable = !GUItest2.Enable;
        }
        if(Events::jpressed(GLFW_KEY_F))
            GUItest.flexible = !GUItest.flexible;
        
        if(Events::pressed(GLFW_KEY_LEFT)) {
            xGUI -= 8 * Events::getDeltaTime();
            GUItest2.setX(xGUI);
        }
        if(Events::pressed(GLFW_KEY_RIGHT)) {
            xGUI += 8 * Events::getDeltaTime();
            GUItest2.setX(xGUI);
        }


        entity = ENTCtrl.getEntity(0);
        if (entity != nullptr)
            entity->rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);
        
        entity = ENTCtrl.getEntity(1);
        if (entity != nullptr)
            entity->rotation = glm::vec3(0.f, sin((float)glfwGetTime()*glm::radians(50.f))*5 ,0.f);

        ENTCtrl.renderEntities(shader, camera);

        GUItest.render(&GUIshader);
        GUItest2.render(&GUIshader);
        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() 
{
    Application* app = new Application;
    return app;
}