#ifndef SMK_FONT_HPP
#define SMK_FONT_HPP

#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <smk/OpenGL.hpp>
#include <smk/Texture.hpp>
#include <string>

namespace smk {

class Font {
 public:
  Font() = default; // Empty font.
  Font(const std::string& filename, int size);
  int size() const { return size_; }

  struct Character {
    smk::Texture texture;
    glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
    float advance;       // Offset to advance to next glyph
  };
  Character* GetCharacter(wchar_t) const;
 private:
  std::map<wchar_t, std::unique_ptr<Character>> characters_;
  int size_ = 0;

 public:
  Font(Font&&) = default;  // Movable object
  void operator=(Font&&);  // Movable object.
 private:
  Font(const Font&) = delete;            // Non copyable object.
  void operator=(const Font&) = delete;  // Non copyable object.
};

}  // namespace smk

#endif /* end of include guard: SMK_FONT_HPP */
