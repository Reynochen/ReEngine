#ifndef ENGINE_FONT
#define ENGINE_FONT

#include <glm/glm.hpp>
#include <map>

class Texture;

struct Character {
    unsigned int TextureID;
    glm::vec2 Size;
    glm::vec2 Bearing;
    unsigned int Advance;
};

class Font {
public:
    Font(const char* fontPath, int fontSize);

    ~Font() {

    }

    void bind() const {
        
    }

private:
    Texture* texture = nullptr;
    std::map<char, Character> Characters;
    int fontSize_;
};

#endif