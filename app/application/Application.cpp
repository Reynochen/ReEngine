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
#include "Font.hpp"

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
    //Font test
    Font fontTest("res/Fonts/arial.ttf", 24);

    //GUI widget test
    GUI GUIchat(BOTTOM, glm::vec4(glm::vec3(0.0f), 0.5f), false, 0.25, 0.25);
    GUIchat.setY(150);
    GUIchat.flexible = true;

    GUI GUItext(LEFTBOT, glm::vec4(glm::vec3(1.f, 1.f, 1.f), 1.f), false, 0.15, 0.20, "res/Texture/amogus.png");
    GUItext.setY(150);
    GUItext.setX(200);

    //Entities controller
    ENTController ENTCtrl;
    ENTCtrl.addEntity(glm::vec3(0.f, 0.f, 0.f), "");

    //Shaders
    Shader shader("res/shaders/main/main.vs", "res/shaders/main/main.fs");
    Shader GUIshader("res/shaders/GUI/main.vs", "res/shaders/GUI/main.fs");
    Camera camera(shader); //Create camera

    Entity* entity;
    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    while (!Window::shouldClose())
    {
        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            if(GUIchat.Enable) {
                camera.EnableMove = true;
                Events::hideMouse(camera.EnableMove); 
                GUIchat.Enable = !GUIchat.Enable;
                GUItext.Enable = !GUItext.Enable;
            }
            else
                Window::shouldClose(true);
        }
        if (Events::jpressed(GLFW_KEY_Z))
            ENTCtrl.removeEntity();
        if (Events::jpressed(GLFW_KEY_0))
            ENTCtrl.addEntity(camera.getPos(), "Monkey");
        if (Events::jpressed(GLFW_KEY_SLASH)) {
            camera.EnableMove = false;
            Events::hideMouse(camera.EnableMove); 
            GUIchat.Enable = true;
            GUItext.Enable = true;
        }
        if(Events::jpressed(GLFW_KEY_F))
            GUIchat.flexible = !GUIchat.flexible;
        
        if(Events::pressed(GLFW_KEY_LEFT)) {
            GUItext.setX(-140 * Events::getDeltaTime());
        }
        if(Events::pressed(GLFW_KEY_RIGHT)) {
            GUItext.setX(140 * Events::getDeltaTime());
        }
        if(Events::pressed(GLFW_KEY_UP)) {
            GUItext.setY(230 * Events::getDeltaTime());
        }
        if(Events::pressed(GLFW_KEY_DOWN)) {
            GUItext.setY(-230 * Events::getDeltaTime());
        }

        if(Events::jpressed(GLFW_KEY_1))
            GUIchat.scalableX = !GUIchat.scalableX;


        // entity = ENTCtrl.getEntity(0);
        // if (entity != nullptr)
        //     entity->rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);
        
        entity = ENTCtrl.getEntity(1);
        if (entity != nullptr)
            entity->scale = glm::vec3(sin((float)glfwGetTime()*glm::radians(50.f))*5);

        ENTCtrl.renderEntities(shader, camera);

        GUIchat.render(&GUIshader);
        GUItext.render(&GUIshader, &fontTest);
        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() 
{
    Application* app = new Application;
    return app;
}