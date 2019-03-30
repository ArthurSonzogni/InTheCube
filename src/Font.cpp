#include "Font.hpp"

#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

const float super_resolution = 1.0;

Font::Font() {}
Font::Font(const std::string& filename, int size) : size(size) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
              << std::endl;

  FT_Face face;
  if (FT_New_Face(ft, filename.c_str(), 0, &face)) {
    std::cout << "ERROR::FREETYPE: Failed to load" << filename << std::endl;
  }

  FT_Set_Pixel_Sizes(face, 0, size * super_resolution);
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
    std::cout << "ERROR::FREETYTPE: Failed to load Glyph for file " << filename
              << std::endl;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Disable byte-alignment restriction

  for (int c = 0; c < 256; c++) {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // Generate texture
    Texture texture;
    texture.width = face->glyph->bitmap.width;
    texture.height = face->glyph->bitmap.rows;
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, texture.width, texture.height, 0,
                 GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture.width /= super_resolution;
    texture.height /= super_resolution;

    // Now store character for later use
    characters[c] = {
      texture,
      glm::ivec2(face->glyph->bitmap_left / super_resolution, face->glyph->bitmap_top / super_resolution),
      face->glyph->advance.x / (64.0f * super_resolution)
    };
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}
