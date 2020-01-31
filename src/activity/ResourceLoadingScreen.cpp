#include "activity/ResourceLoadingScreen.hpp"
#include <cmath>
#include <smk/Color.hpp>
#include <smk/Text.hpp>

void ResourceLoadingScreen::Draw() {
  window().PoolEvents();
  time = window().time();

  if (!initializer.resources.empty()) {
    ResourceInitializer::Resource resource = initializer.resources.front();
    initializer.resources.pop_front();

    smk::Text text;
    text.SetFont(font_arial);
    text.SetString("Decoding: " + *resource.path);
    text.SetColor(smk::Color::White);
    text.SetPosition({10.f, 480.f - 60.f});
    window().Draw(text);
    window().Display();

    resource.Load();
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
