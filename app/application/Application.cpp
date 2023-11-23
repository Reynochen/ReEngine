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
#include "Label.hpp"

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
    Label testLabel("res/Fonts/PFReminderPro-Bold.TTF", glm::vec2(1.5f));
    testLabel.scale = 0.25;
    Label testLabel2("res/Fonts/arial.ttf", glm::vec2(1.5f,0.8f));
    
    //GUI widget test
    GUI GUIchat(BOTTOM, glm::vec4(glm::vec3(0.0f), 0.5f), false, 10.25, 10.25);
    GUIchat.setY(150);
    GUIchat.flexible = true;

    //Entities controller
    ENTController ENTCtrl;
    ENTCtrl.addEntity(glm::vec3(0.f, 0.f, 0.f), "");

    //Shaders
    Shader shader("res/shaders/main/main.vs", "res/shaders/main/main.fs");
    Shader GUIshader("res/shaders/GUI/main.vs", "res/shaders/GUI/main.fs");
    Camera camera(shader); //Create camera

    Entity* entity;
    glClearColor(0.35, 0.77, 0.94, 0); //Sky color
    
    std::string textChat;
    unsigned int lastChar;
    while (!Window::shouldClose())
    {
        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            if(GUIchat.Enable) {
                camera.EnableMove = true;
                Events::hideMouse(camera.EnableMove); 
                GUIchat.Enable = !GUIchat.Enable;
            }
            else
                Window::shouldClose(true);
        }
        if (Events::jpressed(GLFW_KEY_Z))
            ENTCtrl.removeEntity();
        if (Events::jpressed(GLFW_KEY_0) && !GUIchat.Enable)
            ENTCtrl.addEntity(camera.getPos(), "Monkey");
        if (Events::jpressed(GLFW_KEY_SLASH)) {
            camera.EnableMove = false;
            Events::hideMouse(camera.EnableMove); 
            GUIchat.Enable = true;
        }
        if (Events::jpressed(GLFW_KEY_UP)) {
            testLabel.Scalable = !testLabel.Scalable;
            testLabel2.Scalable = !testLabel2.Scalable;
        }

        if(Events::pressAnyKey() && GUIchat.Enable)
            testLabel.text += Events::getInputCode(); 
        // entity = ENTCtrl.getEntity(0);
        // if (entity != nullptr)
        //     entity->rotation = glm::vec3(0.f, (float)glfwGetTime()*glm::radians(50.f) ,0.f);
        
        entity = ENTCtrl.getEntity(1);
        if (entity != nullptr)
            entity->scale = glm::vec3(sin((float)glfwGetTime()*glm::radians(50.f))*5);

        ENTCtrl.renderEntities(shader, camera);

        testLabel.renderText(GUIshader);
        // testLabel2.renderText(GUIshader);
        GUIchat.render(&GUIshader);
        Window::swapBuffers();
        Events::pullEvents();
    }
}

Application* CreateApplication() 
{
    Application* app = new Application;
    return app;
}