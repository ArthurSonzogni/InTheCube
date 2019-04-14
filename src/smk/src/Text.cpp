#include <codecvt>
#include <iostream>
#include <locale>
#include <smk/Font.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <vector>

namespace smk {

std::wstring to_wstring(const std::string& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(s);
}

void Text::SetString(const std::wstring& s) {
  string_ = s;
}

void Text::SetString(const std::string& s) {
  string_ = to_wstring(s);
}

void Text::SetFont(const Font& font) {
  font_ = &font;
}

void Text::Draw(const glm::mat4& view) const {
  const glm::mat4& v = view * GetTransformation(1.0, 1.0);
  Sprite sprite;
  sprite.SetColor(color());

  float advance_x = 0.f;
  float advance_y = font_->size();
  for (const auto& it : string_) {
    if (it == U'\n') {
      advance_x = 0.f;
      advance_y += font_->size();
      continue;
    }
    auto character = font_->GetCharacter(it);
    if (!character)
      continue;

    sprite.SetPosition(advance_x + character->bearing.x,
                       advance_y + character->bearing.y);
    sprite.SetTexture(character->texture);
    sprite.Draw(v);
    advance_x += character->advance;
  }
}

}  // namespace smk
