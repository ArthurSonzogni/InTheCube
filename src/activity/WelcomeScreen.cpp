// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "activity/WelcomeScreen.hpp"

#include <smk/Input.hpp>
#include <smk/Sprite.hpp>
#include <smk/View.hpp>

#include "game/BackgroundMusic.hpp"
#include "game/Resource.hpp"

extern BackgroundMusic background_music;

void WelcomeScreen::OnEnter() {
  time_start = window().time();
  background_music.SetSound(SB_intro);
}

void WelcomeScreen::Draw() {
  window().PoolEvents();

  if (window().input().IsMousePressed(GLFW_MOUSE_BUTTON_1) ||
      window().input().IsKeyPressed(GLFW_KEY_SPACE) ||
      window().input().IsKeyPressed(GLFW_KEY_ENTER)) {
    on_quit();
  }

  float t = window().time() - time_start;
  t = std::max(0.f, std::min(1.f, t));
  t = t * t;

  smk::Sprite sprite(img_accueil);
  sprite.SetColor(glm::vec4(t, t, t, 1.0));
  window().Draw(sprite);
}
