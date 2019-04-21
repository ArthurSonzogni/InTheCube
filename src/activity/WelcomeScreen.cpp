#include "activity/WelcomeScreen.hpp"

#include "Resource.hpp"
#include <smk/Sprite.hpp>
#include <smk/View.hpp>
#include <smk/Input.hpp>

void WelcomeScreen::OnEnter() {
  time_start = screen().time();
}

void WelcomeScreen::Draw() {
  screen().PoolEvents();
  smk::View view;
  view.SetCenter(320, 240);
  view.SetSize(640, 480);
  screen().SetView(view);

  if (screen().input().IsMousePressed(GLFW_MOUSE_BUTTON_1) ||
      screen().input().IsKeyPressed(GLFW_KEY_SPACE) ||
      screen().input().IsKeyPressed(GLFW_KEY_ENTER)) {
    on_quit();
  }

  float t = screen().time() - time_start;
  t = std::max(0.f, std::min(1.f, t));
  t = t * t;

  smk::Sprite sprite;
  sprite.SetTexture(img_accueil);
  sprite.SetColor(glm::vec4(t, t, t, 1.0));

  screen().Draw(sprite);
  screen().Display();
}
