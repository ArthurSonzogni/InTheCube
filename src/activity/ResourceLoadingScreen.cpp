// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "activity/ResourceLoadingScreen.hpp"

#include <cmath>
#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Text.hpp>

void ResourceLoadingScreen::Draw() {
  window().PoolEvents();
  time = window().time();

  if (!initializer.resources.empty()) {
    ResourceInitializer::Resource resource = initializer.resources.front();
    initializer.resources.pop_front();

    resource.Load();
    smk::Text text;
    text.SetScale(0.7);
    text.SetFont(font_arial);
    text.SetString("Decoded: " + *resource.path);
    text.SetColor(smk::Color::White);
    text.SetPosition({10.f, 480.f - 60.f});
    window().Draw(text);
    window().Display();
    return;
  }

  smk::Text text;
  text.SetFont(font_arial);
  text.SetString("Press space to start");
  text.SetColor(smk::Color::White * float(0.5f + 0.4f * sin(time * 8.f)));
  text.SetPosition({10.f, 480.f - 60.f});

  window().Draw(text);

  if (window().input().IsKeyPressed(GLFW_KEY_SPACE))
    on_desktop_device();

  if (window().input().IsCursorReleased())
    on_touch_device();
}
