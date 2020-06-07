// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "activity/IntroScreen.hpp"

#include <glm/gtx/compatibility.hpp>
#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>

#include "game/BackgroundMusic.hpp"
#include "game/Lang.hpp"
#include "game/Resource.hpp"

extern BackgroundMusic background_music;

void IntroScreen::OnEnter() {
  previous_time = window().time();
  x = 0;
  dx = 0;
  position = 1;
  background_music.SetSound(SB_intro);
}

void IntroScreen::Draw() {
  window().PoolEvents();
  // Input
  {
    if (window().input().IsKeyPressed(GLFW_KEY_SPACE) ||
        window().input().IsKeyPressed(GLFW_KEY_ENTER) ||
        window().input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
      position++;
    }
  }

  float t = window().time();
  float dt = t - previous_time;
  previous_time = t;

  // Update (x,dx) smoothly toward position.
  {
    float dxx = 20 * (position * 640 - x) - 6 * dx;
    dx += dxx * dt;
    x += dx * dt;
  }

  // Background color
  {
    static const glm::vec4 colors[] = {
        {0.0f, 0.0f, 0.0f, 1.0f}, {0.4f, 0.4f, 0.4f, 1.0f},
        {0.0f, 0.4f, 0.8f, 1.0f}, {0.8f, 0.0f, 0.0f, 1.0f},
        {0.4f, 0.4f, 0.0f, 1.0f}, {0.0f, 0.4f, 0.4f, 1.0f},
    };

    int index = x / 640;
    float lambda = (x - index * 640) / 640.0;
    glm::vec4 background_color =
        glm::lerp(colors[index], colors[index + 1], lambda);
    window().Clear(background_color);
  }

  // Text
  {
    // clang-format off
    smk::Text text[] = {
      smk::Text(font_arial, tr(L"intro11") + L"\n" + tr(L"intro12") + L"\n" + tr(L"intro13") + L"\n" + tr(L"intro14")),
      smk::Text(font_arial, tr(L"intro21") + L"\n" + tr(L"intro22") + L"\n" + tr(L"intro23") + L"\n" + tr(L"intro24")),
      smk::Text(font_arial, tr(L"intro31") + L"\n" + tr(L"intro32") + L"\n" + tr(L"intro33") + L"\n" + tr(L"intro34")),
      smk::Text(font_arial, tr(L"intro41") + L"\n" + tr(L"intro42") + L"\n" + tr(L"intro43") + L"\n" + tr(L"intro44") + L"\n" + tr(L"intro45")),
      smk::Text(font_arial, tr(L"intro51") + L"\n" + tr(L"intro52") + L"\n" + tr(L"intro53") + L"\n" + tr(L"intro54")),
    };
    // clang-format on

    int p = 0;
    for (auto& it : text) {
      if (p >= position)
        break;
      it.SetPosition(670 - x + p * 640, 10);
      window().Draw(it);
      ++p;
    }
  }

  if (x > 640 * 5.9)
    on_quit();
}
