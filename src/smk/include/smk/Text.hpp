#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <smk/Drawable.hpp>
#include <smk/Texture.hpp>

namespace smk {
class Font;

class Text : public Drawable {
 public:
  void SetString(const std::wstring&);
  void SetString(const std::string&);
  void SetFont(const Font& font);
  void Draw(Screen& screen, RenderState state) const;

 public:
  class Context;
  friend Context;
  Context& context() const;
  const Font* font_ = nullptr;
  std::wstring string_;
};

} // namespace smk

#endif /* end of include guard: TEXT_H */
