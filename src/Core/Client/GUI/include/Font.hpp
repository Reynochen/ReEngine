#ifndef ENGINE_FONT
#define ENGINE_FONT

#include <glm/glm.hpp>
#include <map>
#include <string>

class Texture;
class Shader;

struct Character {
    Texture* texture;
    glm::vec2 Size;
    glm::vec2 Bearing;
    long int Advance;
};

class Font {
    std::map<char, Character> Characters;
    int fontSize_;


public:
    Font(const char* fontPath, int fontSize);

    ~Font() {

    }

    void renderCharacter(Shader* shader, int character);

};

#endif