#include "Label.hpp"
#include "Shader.hpp"

#include "Events.hpp"
#include "Window.hpp"

#include "Mesh.hpp"
#include "Font.hpp"

Label::Label(const char* fontPath, glm::vec2 pos, const char* text, glm::vec4 color)
{
    this->font = new Font(fontPath, 24);
    this->xPos = pos.x;
    this->yPos = pos.y;
    this->color = color;//glm::vec4(glm::vec3(0.f),1.f);

}

Label::~Label()
{
    delete font;
}

void Label::renderText(Shader& shader) 
{
    if(!Enable) return;
    glDisable(GL_DEPTH_TEST);

    shader.use();
    glActiveTexture(0);

    float x = 0.f, y = 0.f;
    for (int i = 0; i < text.length(); i++)
    {
        unsigned int c = text[i];
        Character* ch = font->getCharacter(c);
        font->renderCharacter(&shader, c);

        float xpos = x + ch->Bearing.x * (scale/100);
        float ypos = y - (ch->Size.y - ch->Bearing.y) * (scale/100);

        float w = ch->Size.x * (scale/100);
        float h = ch->Size.y * (scale/100);

        float aspectRatio = Window::getHeight() / Window::getWidth();
        float scaleX = 640.f / Window::getWidth();
        float scaleY = 640.f / Window::getHeight();

        glm::mat4 ModelMatrix = glm::mat4(1.f);
        glm::mat4 projection = glm::ortho(-2.f, 2.f, -2.f, 2.f, 0.1f, 100.f);

        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-2.0, -2.0, 0)); // Pin left-bot

        ModelMatrix = Scalable ? glm::scale(ModelMatrix, glm::vec3(1*aspectRatio, 1, 1.f)) : glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, 1.f));

        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(xPos, yPos, 0));
        shader.setMat4("projection", projection);
        shader.setMat4("model", ModelMatrix);

        Mesh mesh(new std::vector<Vertex>{
                    //Pos                                  //TexCoord             //Normal        //Color 
            Vertex {glm::vec3(xpos, ypos + h, -1.f),     glm::vec2(0.f, 0.f),   glm::vec3(0.f), glm::vec4(color)}, //Left-bot
            Vertex {glm::vec3(xpos, ypos, -1.f),         glm::vec2(0.f, 1.f),   glm::vec3(0.f), glm::vec4(color)},
            Vertex {glm::vec3(xpos + w, ypos, -1.f),     glm::vec2(1.f, 1.f),   glm::vec3(0.f), glm::vec4(color)},

            Vertex {glm::vec3(xpos, ypos + h, -1.f),     glm::vec2(0.f, 0.f),   glm::vec3(0.f), glm::vec4(color)},
            Vertex {glm::vec3(xpos + w, ypos, -1.f),     glm::vec2(1.f, 1.f),   glm::vec3(0.f), glm::vec4(color)},  
            Vertex {glm::vec3(xpos + w, ypos + h, -1.f), glm::vec2(1.f, 0.f),   glm::vec3(0.f), glm::vec4(color)},  
        });

        mesh.render();

        x += (ch->Advance >> 6) * (scale/100);
    }
    glEnable(GL_DEPTH_TEST);
}