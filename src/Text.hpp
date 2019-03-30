#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "Drawable.hpp"
#include "Texture.hpp"

class Font;

class Text : public Drawable {
 public:
  void SetString(const std::wstring&);
  void SetString(const std::string&);
  void SetFont(const Font& font);
  void Draw(const glm::mat4& view) const;

 public:
  const Font* font_ = nullptr;
  std::wstring string_;
};

#endif /* end of include guard: TEXT_H */
