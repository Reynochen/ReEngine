#ifndef ENGINE_LABEL
#define ENGINE_LABEL

#include "GUI.hpp"
#include "Font.hpp"
#include <string>
#include <vector>

class Mesh;
class Shader;

class Label
{
    Font* font;

public:
    std::wstring text;

    bool Scalable = true;
    float xPos = 0.f, yPos = 0.f;
    float scale = 0.5;

    glm::vec4 color = glm::vec4(1.f);

    bool Enable = true;

    Label(const char* fontPath, glm::vec2 pos = glm::vec2(0.f), const char* text = "", glm::vec4 color = glm::vec4(1.f));
    ~Label();

    void renderText(Shader& shader);
};

#endif