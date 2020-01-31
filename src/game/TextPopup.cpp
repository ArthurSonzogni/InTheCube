#include "game/TextPopup.hpp"
#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include "game/Lang.hpp"
#include "game/Resource.hpp"

TextPopup::TextPopup(int t) {
  switch (t) {
    case 0:
      geometry.left = 320;
      geometry.right = 320 + 16;
      geometry.top = 160;
      geometry.bottom = 160 + 96;
      text.push_back({
          tr(L"arbret11"),
          tr(L"arbret12"),
          tr(L"arbret13"),
          tr(L"arbret14"),
      });
      break;
    case 1:
      geometry.left = 576;
      geometry.right = 576 + 32;
      geometry.top = 160;
      geometry.bottom = 448;
      text.push_back({
          tr(L"arbret21"),
      });
      text.push_back({
          tr(L"arbret22"),
      });
      break;
    case 2:
      text.push_back({
          tr(L"arbret31"),
          tr(L"arbret32"),
      });
      text.push_back({
          tr(L"arbret41"),
          tr(L"arbret42"),
      });
      text.push_back({
          tr(L"arbret51"),
          tr(L"arbret52"),
          tr(L"arbret53"),
          tr(L"arbret54"),
      });
      text.push_back({
          tr(L"arbret61"),
          tr(L"arbret62"),
          tr(L"arbret63"),
          tr(L"arbret64"),
          tr(L"arbret65"),
      });
      text.push_back({
          tr(L"arbret71"),
          tr(L"arbret72"),
          tr(L"arbret73"),
          tr(L"arbret74"),
          tr(L"arbret75"),
      });
      text.push_back({
          tr(L"arbret81"),
          tr(L"arbret82"),
          tr(L"arbret83"),
      });
      text.push_back({
          tr(L"arbret91"),
          tr(L"arbret92"),
          tr(L"arbret93"),
      });
      text.push_back({
          tr(L"arbret101"),
          tr(L"arbret102"),
          tr(L"arbret103"),
          tr(L"arbret104"),
          tr(L"arbret105"),
      });
      text.push_back({
          tr(L"arbret111"),
          tr(L"arbret112"),
      });
      break;
    case 3: {
      geometry.left = 1408;
      geometry.right = 1408 + 128;
      geometry.top = 32;
      geometry.bottom = 480;
      text.push_back({
          tr(L"instruction1"),
          tr(L"instruction2"),
          tr(L"instruction3"),
          tr(L"instruction4"),
          tr(L"instruction5"),
      });
      text.push_back({
          tr(L"instruction6"),
          tr(L"instruction7"),
          tr(L"instruction8"),
      });
    } break;
  }
  spaceSprite = smk::Sprite(img_decorSpace);
}

bool TextPopup::Step(smk::Window& window) {
  time++;
  horizontal_shift += (100 - horizontal_shift) / 10.0;

  if (time > 10) {
    if (window.input().IsMousePressed(GLFW_MOUSE_BUTTON_1) ||
        window.input().IsKeyPressed(GLFW_KEY_SPACE) ||
        window.input().IsKeyPressed(GLFW_KEY_ENTER) ||
        window.input().IsCursorReleased()) {
      p++;
      horizontal_shift = 640;
      time = 0;
      if (p >= (int)text.size())
        return true;
    }
  }
  return false;
}

void TextPopup::Draw(smk::Window& window) {
  if (p >= (int)text.size())
    return;
  // FloatRect rect = window.GetView().GetRect();
  // drawing cadre
  float left = window.GetView().Left();
  float top = window.GetView().Top();
  int x1 = left + 640 / 5;
  int y1 = top + 480 / 5 + horizontal_shift;

  int x2 = 640 * 4 / 5 + left;
  int y2 = 480 + horizontal_shift + top;

  int r = 25;
  int e = 10;

  glm::vec4 c0 = {0.05, 0.05, 0.05, 1.0};
  glm::vec4 c1 = smk::Color::White;

  auto circle_1 = smk::Shape::Circle(r);
  auto circle_2 = smk::Shape::Circle(r - e);
  circle_1.SetColor(c0);
  circle_2.SetColor(c1);
  for (glm::vec2 position : {glm::vec2(x1, y1), glm::vec2(x2, y1)}) {
    circle_1.SetPosition(position);
    circle_2.SetPosition(position);
    window.Draw(circle_1);
    window.Draw(circle_2);
  }

  auto rect = smk::Shape::Square();
  rect.SetPosition(x1, y1 - r);
  rect.SetScale(x2 - x1, y2 - y1 + 2 * r);
  rect.SetColor(c0);
  window.Draw(rect);

  rect.SetPosition(x1 - r, y1);
  rect.SetScale(x2 - x1 + 2 * r, y2 - y1);
  window.Draw(rect);

  rect.SetColor(c1);

  rect.SetPosition(x1, y1 - r + e);
  rect.SetScale(x2 - x1, y2 - y1 + 2 * r - 2 * e);
  rect.SetColor(c1);
  window.Draw(rect);

  rect.SetPosition(x1 - r + e, y1);
  rect.SetScale(x2 - x1 + 2 * r - 2 * e, y2 - y1);
  window.Draw(rect);

  // drawing texte
  int x = x1 + 5;
  int y = y1 + 5;
  textString.SetColor(c0);
  textString.SetFont(font_arial);
  for (auto& t : text[p]) {
    textString.SetPosition(x, y);
    textString.SetString(t);
    window.Draw(textString);
    y += 40;
  }
  spaceSprite.SetPosition(x2 - 128, y2 - 135);
  window.Draw(spaceSprite);
}
