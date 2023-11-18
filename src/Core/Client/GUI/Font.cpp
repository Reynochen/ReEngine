#include "Font.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Texture.hpp"

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
}