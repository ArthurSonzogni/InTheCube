// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "activity/MainScreen.hpp"

#include <codecvt>
#include <iostream>
#include <locale>
#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <smk/View.hpp>

#include "game/Lang.hpp"
#include "game/Resource.hpp"

std::wstring to_wstring(const std::string& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(s);
}

std::string intToString(int n) {
  std::string retour = "";
  retour += char(n % 10 + '0');
  while (n >= 10) {
    n /= 10;
    retour = char(n % 10 + '0') + retour;
  }
  return retour;
}

void MainScreen::OnEnter() {
  previous_time = window().time();
  for (auto& it : languageXPos)
    it = 640;
}

void MainScreen::Draw() {
  window().PoolEvents();

  if (window().input().IsKeyPressed(GLFW_KEY_ESCAPE))
    on_quit();

  float time = window().time();
  float dt = time - previous_time;
  previous_time = time;

  std::vector<smk::Sprite> sprLanguage = {
      smk::Sprite(img_frenchFlag),
      smk::Sprite(img_englishFlag),
      smk::Sprite(img_deutschFlag),
  };
  for (size_t i = 0; i < sprLanguage.size(); ++i)
    sprLanguage[0].SetPosition(640, 100 * i);

  float zoom = std::min(window().width() / 640.f, window().height() / 480.f);
  glm::vec2 mouse = window().input().mouse();
  mouse -= window().dimension() * 0.5f;
  mouse /= zoom;
  mouse += glm::vec2(640, 480) * 0.5f;

  if (question_ || get_string_)
    mouse = {0.f, 0.f};

  bool mouse_pressed = window().input().IsMousePressed(GLFW_MOUSE_BUTTON_1);

  // Draw the background.
  {
    auto background = smk::Sprite(img_background);
    for (int x = 0; x <= 640; x += 24) {
      for (int y = 0; y <= 480; y += 24) {
        background.SetPosition(x, y);
        window().Draw(background);
      }
    }
  }

  // Language
  for (int i = 0; i < 3; i++) {
    bool selected = mouse.x >= 640 - 128 &&   //
                    mouse.x <= 640 &&         //
                    mouse.y > 100 * i &&      //
                    mouse.y <= 100 * i + 64;  //

    float target = selected ? 640 - 128 : 640 - 100;
    languageXPos[i] += (target - languageXPos[i]) * 30 * dt;
    sprLanguage[i].SetPosition(languageXPos[i], 100 * i);
    sprLanguage[i].SetColor(selected ? smk::Color::White
                                     : glm::vec4{0.5, 0.5, 0.5, 1.0});
    if (selected && mouse_pressed)
      on_update_traduction(i);

    window().Draw(sprLanguage[i]);
  }

  // Draw the save files.
  int i = 0;
  for (auto& it : save_file_.saveList) {
    float decale = std::abs(mouse.y - (50 + i * 40));
    decale = std::max(decale, -30 - 370 + mouse.x);
    decale = std::max(5.f, std::min(decale, 40.f));

    // rectangle
    {
      auto rectangle = smk::Shape::Square();
      rectangle.SetPosition(30, 30 + i * 40);
      rectangle.SetScale(370, 40);
      rectangle.SetColor(glm::vec4(decale + 50, 2 * decale + 100,
                                   2 * decale + 150, 255 - decale * 4) /
                         255.f);
      rectangle.Move(decale, 0);
      window().Draw(rectangle);
    }

    // text
    {
      smk::Text text;
      text.SetFont(font_arial);
      text.SetString(it.first + "  /  " + intToString(it.second));
      text.SetPosition(40, 30 + i * 40);
      text.SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
      text.Move(decale, 0);
      window().Draw(text);

      text.Move(-2, -2);
      text.SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
      window().Draw(text);
    }

    // deleteButton
    {
      auto deleteButton = smk::Sprite(img_deleteButton);
      deleteButton.SetPosition(1, 30 + i * 40);
      float delete_button_alpha =
          8000.0 / (std::abs(mouse.x) + std::abs(mouse.y - 40 - i * 40));
      delete_button_alpha =
          std::max(100.f, std::min(255.f, delete_button_alpha));
      deleteButton.SetColor(
          glm::vec4(1.0, 1.0, 1.0, delete_button_alpha / 255.f));
      window().Draw(deleteButton);
    }

    if (mouse_pressed) {
      if (mouse.y > 30 + i * 40 && mouse.y < 70 + i * 40) {
        if (mouse.x > 30 + decale && mouse.x < 400 + decale) {
          on_name_selected(it.first);
        } else {
          if (mouse.x >= 0 && mouse.x <= 24 && mouse.y >= 30 + i * 40 &&
              mouse.y <= 24 + 30 + i * 40) {
            question_ = std::make_unique<Question>(window());
            question_->question = tr(L"confirmDelete1") + L"\n" +
                                  tr(L"confirmDelete2") + L"\n" +
                                  tr(L"confirmDelete3") + to_wstring(it.first);
            question_->yes = tr(L"yes");
            question_->no = tr(L"no");
            question_->on_yes = [this, name = it.first] {
              save_file_.saveList.erase(name);
            };
          }
        }
      }
    }
    i++;
  }

  auto newGame = smk::Sprite(img_newGame);
  newGame.SetPosition(320 - 300 / 2, 480 - 64);

  auto newGameText = smk::Text(font_arial, tr(L"newGame"));
  newGameText.SetPosition(220, 430);
  newGameText.SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

  // button new game
  if (mouse.y < 480 && mouse.y > 480 - 64 && mouse.x > 640 / 2 - 300 / 2 &&
      mouse.x < 640 / 2 + 300 / 2) {
    newGame.SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    if (mouse_pressed) {
      window().Draw(newGame);
      window().Draw(newGameText);

      get_string_ = std::make_unique<GetString>(window());
      get_string_->message = tr(L"enterYourName");
      get_string_->on_enter = [this](std::string name) {
        if (save_file_.saveList.count(name)) {
          question_ = std::make_unique<Question>(window());
          question_->question = tr(L"profileExistAlready");
          question_->yes = tr(L"okay");
          question_->no = tr(L"");
        } else
          save_file_.saveList[name] = 0;
      };
    }
  } else {
    newGame.SetColor(glm::vec4(200, 200, 200, 255) / 255.f);
  }
  window().Draw(newGame);
  window().Draw(newGameText);

  if (question_) {
    if (question_->Draw(window()))
      question_.reset();
  }

  if (get_string_) {
    if (get_string_->Draw(window()))
      get_string_.reset();
  }
}

std::string* character_callback_string = nullptr;
void character_callback(GLFWwindow*, unsigned int codepoint) {
  if (!character_callback_string)
    return;
  *character_callback_string += (wchar_t)codepoint;
}

MainScreen::GetString::GetString(smk::Window& window) : window_(window) {
  character_callback_string = &typed_text_;
  glfwSetCharCallback(window_.window(), character_callback);
}

MainScreen::GetString::~GetString() {
  glfwSetCharCallback(window_.window(), nullptr);
}

bool MainScreen::GetString::Draw(smk::Window& window) {
  {
    if (time_ <= -1) {
      time_ = window.time();
    }
    float target = exiting_ ? 0.0 : 1.0;
    for (int i = 0; i < 10; ++i) {
      alpha += (target - alpha) * (window.time() - time_);
    }

    if (exiting_ && alpha <= 0.01)
      return true;
    time_ = window.time();
  }

  // Black shadow.
  {
    auto black_shadow = smk::Shape::Square();
    black_shadow.SetPosition(0, 0);
    black_shadow.SetScale(640, 480);
    black_shadow.SetColor(glm::vec4(0, 0, 0, 0.5 * alpha));
    window.Draw(black_shadow);
  }

  // Frame
  {
    auto frame_sprite = smk::Sprite(img_cadreInput);
    frame_sprite.SetColor(glm::vec4(1.0, 1.0, 1.0, alpha));
    frame_sprite.SetPosition(640 / 2 - img_cadreInput.width() / 2,
                             480 / 2 - img_cadreInput.height() / 2);
    window.Draw(frame_sprite);
  }

  // text
  if (typed_text_.empty()) {
    smk::Text enter_your_name;
    enter_your_name.SetFont(font_arial);
    enter_your_name.SetString(tr(L"enterYourName"));
    enter_your_name.SetColor(glm::vec4(0.3, 0.3, 0.3, alpha));

    glm::vec2 dimension = enter_your_name.ComputeDimensions();
    enter_your_name.SetPosition(640 / 2 - dimension.x / 2,
                                480 / 2 - dimension.y / 2);
    window.Draw(enter_your_name);
  }

  // Written text
  {
    smk::Text text;
    text.SetFont(font_arial);
    text.SetString(typed_text_);
    auto dimension = text.ComputeDimensions();
    text.SetPosition(640 / 2 - dimension.x / 2, 480 / 2 - dimension.y / 2);
    text.SetColor(glm::vec4(0.0, 0.0, 0.0, alpha));
    window.Draw(text);

    if (window.input().IsKeyPressed(GLFW_KEY_BACKSPACE) ||
        dimension.x > img_cadreInput.width() - 12) {
      typed_text_ = typed_text_.substr(0, typed_text_.size() - 1);
    }

    if (window.input().IsKeyPressed(GLFW_KEY_ENTER)) {
      on_enter(typed_text_);
      exiting_ = true;
    }
  }

  return false;
}

MainScreen::Question::Question(smk::Window& window) {
  time_ = window.time();
}

bool MainScreen::Question::Draw(smk::Window& window) {
  {
    float target = exiting_ ? 0.0 : 1.0;
    for (int i = 0; i < 10; ++i) {
      alpha += (target - alpha) * (window.time() - time_);
    }
    time_ = window.time();

    if (exiting_ && alpha <= 0.01)
      return true;
  }

  // Black shadow.
  {
    auto black_shadow = smk::Shape::Square();
    black_shadow.SetPosition(0, 0);
    black_shadow.SetScale(640, 480);
    black_shadow.SetColor(glm::vec4(0, 0, 0, 0.5 * alpha));
    window.Draw(black_shadow);
  }

  // White Shadow
  {
    auto white_shadow = smk::Shape::Square();
    white_shadow.SetPosition(640 * 0.2, 480 * 0.2);
    white_shadow.SetScale(640 * 0.6, 480 * 0.6);
    white_shadow.SetColor(glm::vec4(1, 1, 1, alpha));
    window.Draw(white_shadow);
  }

  // Question
  {
    smk::Text text_string;
    text_string.SetFont(font_arial);
    text_string.SetString(question);
    auto dimension = text_string.ComputeDimensions();
    text_string.SetPosition(640 * 0.5 - dimension.x / 2, 480 * 0.2 + 10);
    text_string.SetColor(glm::vec4(0.f, 0.f, 0.f, alpha));
    window.Draw(text_string);
  }

  // Yes answer
  {
    smk::Text yes_string;
    yes_string.SetFont(font_arial);
    yes_string.SetString(yes);
    auto dimension = yes_string.ComputeDimensions();
    float left = 640 * 0.2 + 10;
    float right = left + dimension.x;
    float bottom = 480 * 0.8 - 10;
    float top = bottom - dimension.y;
    yes_string.SetPosition(left, top);

    auto mouse = window.input().mouse();
    bool hover = mouse.x >= left &&   //
                 mouse.x <= right &&  //
                 mouse.y >= top &&    //
                 mouse.y <= bottom;
    if (hover) {
      yes_string.SetColor(glm::vec4(0.f, 0.f, 0.f, alpha));
      if (window.input().IsMousePressed(GLFW_MOUSE_BUTTON_1) && !exiting_) {
        on_yes();
        exiting_ = true;
      }
    } else {
      yes_string.SetColor(glm::vec4(0.5, 0.5, 0.5, alpha));
    }

    window.Draw(yes_string);
  }

  // No answer
  {
    smk::Text no_string;
    no_string.SetFont(font_arial);
    no_string.SetString(no);
    auto dimension = no_string.ComputeDimensions();
    float right = 640 * 0.8 - 10;
    float left = right - dimension.x;
    float bottom = 480 * 0.8 - 10;
    float top = bottom - dimension.y;
    no_string.SetPosition(left, top);

    if (window.input().mouse().x >= left &&   //
        window.input().mouse().x <= right &&  //
        window.input().mouse().y >= top &&    //
        window.input().mouse().y <= bottom) {
      no_string.SetColor(glm::vec4(0.0, 0.0, 0.0, alpha));
      if (window.input().IsMousePressed(GLFW_MOUSE_BUTTON_1) && !exiting_) {
        on_no();
        exiting_ = true;
      }
    } else {
      no_string.SetColor(glm::vec4(0.5, 0.5, 0.5, alpha));
    }
    window.Draw(no_string);
  }

  return false;
}
