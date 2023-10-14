#include "Application.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Graphics.hpp"
#include "Camera.hpp"
#include "Events.hpp"

#include <math.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Application::Application() {
    Window::initialization(640, 480, "ReEngine");
    Events::initialization(Window::getWindow());
}

Application::~Application() {
    Window::terminate();
}

void Application::run() {
    Camera camera;

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
    Shader shader("res\\main.vs", "res\\main.fs");

    while(!Window::shouldClose())
    {
        /* Need will to create another place for all hotkey in engine */
        if (Events::pressed(GLFW_KEY_ESCAPE)) {
            Window::shouldClose(true);
        }

        glm::ortho(0.0f, 800.f, 0.0f, 600.9f, 0.1f, 100.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)Window::getWidth()/(float)Window::getHeight(), 0.1f, 100.0f);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        Window::swapBuffers();
        glfwPollEvents(); //Will need to create Events module
    }
}

void Application::updateDraw() {

}

Application* CreateApplication() {
    Application* app = new Application;
    return app;
}