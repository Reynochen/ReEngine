#ifndef ENGINE_FONT
#define ENGINE_FONT

#include <ft2build.h>
#include FT_FREETYPE_H 

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
    std::map<wchar_t, Character> Characters;
    int fontSize_;


public:
    Font(const char* fontPath, int fontSize);

    ~Font() {}

    void renderCharacter(Shader* shader, unsigned int character);
    Character* getCharacter(unsigned int character);

};

#endif