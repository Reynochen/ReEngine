#include "Font.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glm/glm.hpp>

#include <locale>
#include <codecvt>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Texture.hpp"
#include "Shader.hpp"

Font::Font(const char* fontPath, int fontSize) 
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Lib.\n";
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font.\n";
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 128);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYPE: Failed to load Glyph.\n";
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(unsigned int c = 0; c < 1106; c++) {
        std::wostringstream wss;
        wss << (wchar_t)c;
        std::wstring ch = wss.str();

        std::wstring::iterator it = ch.begin();

        if (FT_Load_Char(face, *it, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph\n";
            continue;
        }

        Texture* texture = new Texture(face->glyph->bitmap.buffer, GL_TEXTURE_2D, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_CLAMP_TO_EDGE);
        
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<wchar_t, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Character* Font::getCharacter(unsigned int character) {
    if (character > 1105) return &Characters[0];
    return &Characters[character];
}

void Font::renderCharacter(Shader* shader, unsigned int character) {
    glActiveTexture(0);

    Character ch;
    
    if(character < 1106) ch = Characters[character];
    else ch = Characters[0];

    ch.texture->bind();
    shader->setInt("Texture", ch.texture->getTexUnit());
    shader->setInt("texEmpty", ch.texture->isEmpty());
}