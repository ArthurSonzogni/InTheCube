#include "TextureManager.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

#include "GL_CHECK_ERROR.hpp"
#include "StbImage.hpp"

int next_power_of_2(int v) {
  return v;
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

unsigned char* imageLoad(const std::string& filename,
                         int& width,
                         int& height,
                         int& comp) {
  std::cout << "imageLoad[\"" << filename << "\");" << std::endl;
  unsigned char* data;

  FILE* file = fopen(filename.c_str(), "rb");
  if (!file) {
    std::cerr << "File not found" << std::endl;
    return 0;
  }

  data = stbi_load_from_file(file, &width, &height, &comp, 0);

  std::cout << "imageLoad[\"" << filename << "\"," << (void*)data << ","
            << width << "," << height << "," << comp << "]" << std::endl;
  fclose(file);

  return data;
}

void imageFree(unsigned char* data) {
  if (data)
    stbi_image_free(data);
}

Texture TextureManager::LoadTexture(const std::string& filename) {
  GL_CHECK_ERROR(__FILE__, __LINE__);

  auto it(textures.find(filename));
  if (it != textures.end())
    return it->second;

  GLuint texture;
  int width, height, comp;

  unsigned char* data = imageLoad(filename, width, height, comp);

  int width_b = next_power_of_2(width);
  int height_b = next_power_of_2(height);

  std::cout << "enlarged = " << width_b << "," << height_b << std::endl;

  std::vector<unsigned char> transformed(width_b * height_b * 4, 0);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int c = 0; c < 4; ++c) {
        transformed[c + 4 * (x + width_b * y)] =
            (c == 3 && comp != 4) ? 255 : data[c + comp * (x + width * y)];
      }
    }
  }

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_b, height_b, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, transformed.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);

  free(data);

  textures[filename].id = texture;
  textures[filename].width = width_b;
  textures[filename].height = height_b;

  GL_CHECK_ERROR(__FILE__, __LINE__);

  return textures[filename];
}

TextureManager::~TextureManager() {
  for (auto it(textures.begin()); it != textures.end(); ++it) {
    glDeleteTextures(1, &it->second.id);
  }
}

void TextureManager::Bind(GLuint id, GLuint activetexture) {
  glActiveTexture(activetexture);
  glBindTexture(GL_TEXTURE_2D, id);
}
