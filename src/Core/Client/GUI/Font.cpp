#include "Font.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glm/glm.hpp>

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

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYPE: Failed to load Glyph.\n";
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    std::wstring text = L"Ыauptmen?";
    std::wstring::iterator it = text.begin();
    for(wchar_t c = 0; c < 256; c++) {
        if (FT_Load_Char(face, *it, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph\n";
            continue;
        }

        Texture* tex = new Texture(face->glyph->bitmap.buffer, GL_TEXTURE_2D, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_CLAMP_TO_EDGE);
        
        Character character = {
            tex,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Font::renderCharacter(Shader* shader, int character) {
    glActiveTexture(0);

    std::string::const_iterator c;
    // for (c = character.begin(); c != character.end(); c++)
    // {
        Character ch = Characters[character];

        ch.texture->bind();
        shader->setInt("Texture", ch.texture->getTexUnit());
        // std::cout <<  << '\n';   
    // }
}