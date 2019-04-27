#include "activity/ResourceLoadingScreen.hpp"
#include <smk/Color.hpp>
#include <cmath>
#include <smk/Text.hpp>

void ResourceLoadingScreen::Draw() {
  screen().PoolEvents();
  time = screen().time();

  screen().Clear(smk::Color::Black);

  if (!initializer.resources.empty()) {
    ResourceInitializer::Resource resource = initializer.resources.front();
    initializer.resources.pop_front();

    smk::View view;
    view.SetCenter(320, 240);
    view.SetSize(640, 480);
    screen().SetView(view);

    smk::Text text;
    text.SetFont(font_arial);
    text.SetString("Decoding: " + *resource.path);
    text.SetColor(smk::Color::White);
    text.SetPosition({10.f, 480.f - 60.f});
    screen().Draw(text);

    screen().Display();

    resource.Load();
    return;
  }

  smk::Text text;
  text.SetFont(font_arial);
  text.SetString("Press space to start");
  text.SetColor(smk::Color::White * float(0.5f + 0.4f * sin(time * 8.f)));
  text.SetPosition({10.f, 480.f - 60.f});

  screen().Draw(text);
  screen().Display();

  if (screen().input().IsKeyPressed(GLFW_KEY_SPACE))
    on_quit();
}
