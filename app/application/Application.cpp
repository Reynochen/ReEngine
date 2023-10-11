#include "Application.hpp"

#include "Graphics.hpp"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <math.h>
#include <iostream>

Application::Application() {
    Window::initialization(640, 480, "ReEngine");

}

Application::~Application() {
    Window::terminate();
}

void Application::run() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }; 
    
    //Generate VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);  

    //Generate VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Create shader
    /*Need adding debug and release version*/
    Shader shader("D:\\.MyRepositories\\C++ Porjects\\.ReEngine\\res\\main.vs", "D:\\.MyRepositories\\C++ Porjects\\.ReEngine\\res\\main.fs");

    while(!Window::shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        Window::swapBuffers();
        glfwPollEvents(); //Will need to create Events module
    }
}

void Application::updateDraw() {

}

Application* CreateApllication() {
    Application* app = new Application;
    return app;
}