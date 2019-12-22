#include "activity/WelcomeScreen.hpp"

#include "Resource.hpp"
#include <smk/Sprite.hpp>
#include <smk/View.hpp>
#include <smk/Input.hpp>
#include "BackgroundMusic.hpp"

extern BackgroundMusic background_music;

void WelcomeScreen::OnEnter() {
  time_start = window().time();
  background_music.SetSound(SB_intro);
}

void WelcomeScreen::Draw() {
  window().PoolEvents();
  smk::View view;
  view.SetCenter(320, 240);
  view.SetSize(640, 480);
  window().SetView(view);

  if (window().input().IsMousePressed(GLFW_MOUSE_BUTTON_1) ||
      window().input().IsKeyPressed(GLFW_KEY_SPACE) ||
      window().input().IsKeyPressed(GLFW_KEY_ENTER)) {
    on_quit();
  }

  float t = window().time() - time_start;
  t = std::max(0.f, std::min(1.f, t));
  t = t * t;

  smk::Sprite sprite;
  sprite.SetTexture(img_accueil);
  sprite.SetColor(glm::vec4(t, t, t, 1.0));

  window().Clear(glm::vec4(0.0, 0.0, 0.0, 0.0));
  window().Draw(sprite);
  window().Display();
}
