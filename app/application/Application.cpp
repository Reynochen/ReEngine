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
    Label chatLabel("res/Fonts/PFReminderPro-Bold.TTF", glm::vec2(0.15f));
    chatLabel.scale = 0.25;
    
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
    
    std::string lastModelCreate;
    while (!Window::shouldClose())
    {
        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            if(GUIchat.Enable) {
                chatLabel.text.clear();
                camera.EnableMove = true;
                Events::hideMouse(camera.EnableMove); 
                GUIchat.Enable = !GUIchat.Enable;
            }
            else
                Window::shouldClose(true);
        }
        if(!GUIchat.Enable) {
            if (Events::jpressed(GLFW_KEY_Z))
                ENTCtrl.removeEntity();
            if (Events::jpressed(GLFW_KEY_SLASH)) {
                camera.EnableMove = false;
                Events::hideMouse(camera.EnableMove); 
                chatLabel.text += L'/';
                GUIchat.Enable = true;
            }
            if (Events::jpressed(GLFW_KEY_UP)) {
                chatLabel.Scalable = !chatLabel.Scalable;
            }
            if (Events::jpressed(GLFW_KEY_0)) {
                ENTCtrl.addEntity(camera.getPos(), lastModelCreate.c_str());
            }
        } else {
            if(Events::pressAnyKey() && GUIchat.Enable)
                chatLabel.text += Events::getInputCode(); 
            
            if(Events::jpressed(GLFW_KEY_BACKSPACE) && chatLabel.text.length() > 0)
                chatLabel.text.pop_back(); 
            
            if(Events::jpressed(GLFW_KEY_ENTER)) {
                std::wstring command = chatLabel.text;
                if(command[0] == L'/') {

                    if (command.find(L"/create ") != std::wstring::npos) {
                        std::string commandStr(command.begin(), command.end());
                        
                        if(!ENTCtrl.addEntity(camera.getPos(), commandStr.erase(0, commandStr.find_first_of(" ")+1).c_str()))
                            lastModelCreate = commandStr.erase(0, commandStr.find_first_of(" ")+1);
                    }
            
                }


                chatLabel.text.clear();
                camera.EnableMove = true;
                Events::hideMouse(camera.EnableMove); 
                GUIchat.Enable = !GUIchat.Enable;
            }
        }
        
        entity = ENTCtrl.getEntity(1);
        if (entity != nullptr)
            entity->rotation = glm::vec3(0.f, sin((float)glfwGetTime()*glm::radians(50.f))*5, 0.f);

        ENTCtrl.renderEntities(shader, camera);

        chatLabel.renderText(GUIshader);
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