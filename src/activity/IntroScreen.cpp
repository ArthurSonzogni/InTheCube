#include "activity/IntroScreen.hpp"

#include <smk/Input.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include "Resource.hpp"
#include "Lang.hpp"
#include <glm/gtx/compatibility.hpp>
#include <smk/Color.hpp>
#include "BackgroundMusic.hpp"

extern BackgroundMusic background_music;

void IntroScreen::OnEnter() {
  previous_time = screen().time();
  x = 0;
  dx = 0;
  position = 1;
  background_music.SetSound(SB_intro);
}

void IntroScreen::Draw() {
  screen().PoolEvents();
  // Input
  {
    if (screen().input().IsKeyPressed(GLFW_KEY_SPACE) ||
        screen().input().IsKeyPressed(GLFW_KEY_ENTER) ||
        screen().input().IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
      position++;
    }
  }

  float t = screen().time();
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
      {0.0f, 0.0f, 0.0f, 1.0f},
      {0.4f, 0.4f, 0.4f, 1.0f},
      {0.0f, 0.4f, 0.8f, 1.0f},
      {0.8f, 0.0f, 0.0f, 1.0f},
      {0.4f, 0.4f, 0.0f, 1.0f},
      {0.0f, 0.4f, 0.4f, 1.0f},
    };

    int index = x / 640;
    float lambda = (x - index * 640) / 640.0;
    glm::vec4 background_color =
        glm::lerp(colors[index], colors[index + 1], lambda);
    screen().Clear(background_color);
  }

  // Text
  {
    smk::Text text[5];
    text[0].SetString(tr(L"intro11") + L"\n" + tr(L"intro12") + L"\n" +
                    tr(L"intro13") + L"\n" + tr(L"intro14"));
    text[1].SetString(tr(L"intro21") + L"\n" + tr(L"intro22") + L"\n" +
                    tr(L"intro23") + L"\n" + tr(L"intro24"));
    text[2].SetString(tr(L"intro31") + L"\n" + tr(L"intro32") + L"\n" +
                    tr(L"intro33") + L"\n" + tr(L"intro34"));
    text[3].SetString(tr(L"intro41") + L"\n" + tr(L"intro42") + L"\n" +
                    tr(L"intro43") + L"\n" + tr(L"intro44") + L"\n" +
                    tr(L"intro45"));
    text[4].SetString(tr(L"intro51") + L"\n" + tr(L"intro52") + L"\n" +
                    tr(L"intro53") + L"\n" + tr(L"intro54"));

    int p = 0;
    for(auto& it : text) {
      if (p>=position) break;
      it.SetPosition(670-x+p*640,10);
      it.SetFont(font_arial);
      it.SetColor(smk::Color::White);
      screen().Draw(it);
      ++p;
    }
  }

  if (x > 640 * 5.9)
    on_quit();

  screen().Display();
}
