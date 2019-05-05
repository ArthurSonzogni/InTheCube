#include "activity/MainScreen.hpp"

#include "Lang.hpp"
#include "Resource.hpp"
#include <codecvt>
#include <codecvt>
#include <iostream>
#include <locale>
#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Shape.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <smk/View.hpp>

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
  previous_time = screen().time();
  languageXPos[0] = 640;
  languageXPos[1] = 640;
  languageXPos[2] = 640;
}

void MainScreen::Draw() {
  screen().PoolEvents();

  // escape button
  if (screen().input().IsKeyPressed(GLFW_KEY_ESCAPE))
    on_quit();

  float time = screen().time();
  float dt = time - previous_time;
  previous_time = time;

  smk::View view;
  view.SetCenter(320, 240);
  view.SetSize(640, 480);
  screen().SetView(view);

  smk::Sprite sprLanguage[3];
  sprLanguage[0].SetTexture(img_frenchFlag);
  sprLanguage[1].SetTexture(img_englishFlag);
  sprLanguage[2].SetTexture(img_deutschFlag);
  sprLanguage[0].SetPosition(640, 0);
  sprLanguage[1].SetPosition(640, 100);
  sprLanguage[2].SetPosition(640, 200);

  smk::Sprite deleteButton;
  smk::Sprite newGame;
  smk::Sprite background;

  deleteButton.SetTexture(img_deleteButton);

  newGame.SetTexture(img_newGame);
  newGame.SetPosition(320 - 300 / 2, 480 - 64);
  smk::Text newGameText;
  newGameText.SetFont(font_arial);
  newGameText.SetString(tr(L"newGame"));
  newGameText.SetPosition(220, 430);
  newGameText.SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

  background.SetTexture(img_background);

  std::string name;

  glm::vec2 mouse = screen().input().mouse();
  bool mouse_pressed = screen().input().IsMousePressed(GLFW_MOUSE_BUTTON_1);

  if (question_) {
    mouse = question_->alpha * glm::vec2(0.f, 0.f) +
            (1.f - question_->alpha) * mouse;
  }
  if (get_string_) {
    mouse = get_string_->alpha * glm::vec2(0.f, 0.f) +
            (1.f - get_string_->alpha) * mouse;
  }
  ///// Draw

  // Draw the background.
  for (int x = 0; x <= 640; x += 24) {
    for (int y = 0; y <= 480; y += 24) {
      background.SetPosition(x, y);
      screen().Draw(background);
    }
  }

  // Language
  for (int i = 0; i < 3; i++) {
    bool selected = mouse.x >= 640 - 128 &&   //
                    mouse.x <= 640 &&         //
                    mouse.y > 100 * i &&      //
                    mouse.y <= 100 * i + 64;  //

    float target = selected ? 640 - 128 : 640 - 100;
    languageXPos[i] += (target - languageXPos[i]) * 30 *  dt;
    sprLanguage[i].SetPosition(languageXPos[i], 100 * i);
    sprLanguage[i].SetColor(selected ? smk::Color::White
                                     : glm::vec4{0.5, 0.5, 0.5, 1.0});
    if (selected && mouse_pressed) {
      on_update_traduction(i);
      newGameText.SetString(tr(L"newGame"));
      newGameText.SetPosition(220, 430);
    }

    screen().Draw(sprLanguage[i]);
  }
  // Draw the save files.
  int i = 0;
  for (auto& it : save_file_.saveList) {
    (void)it;
    float decale = std::abs(mouse.y - (50 + i * 40));
    decale = std::max(decale, -30-370 + mouse.x);
    decale = std::max(5.f, std::min(decale, 40.f));

    // rectangle
    smk::Shape rectangle = smk::Shape::Square();
    rectangle.SetPosition(30, 30 + i * 40);
    rectangle.SetScale(370, 40);
    rectangle.SetColor(glm::vec4(decale + 50, 2 * decale + 100,
                                 2 * decale + 150, 255 - decale * 4) /
                       255.f);
    rectangle.Move(decale, 0);
    screen().Draw(rectangle);

    // text
    smk::Text text;
    text.SetFont(font_arial);
    text.SetString(it.first + "  /  " + intToString(it.second));
    text.SetPosition(40, 30 + i * 40);
    text.SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
    text.Move(decale, 0);
    screen().Draw(text);

    text.Move(-2, -2);
    text.SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    screen().Draw(text);

    // deleteButton
    deleteButton.SetPosition(1, 30 + i * 40);
    float delete_button_alpha =
        8000.0 / (std::abs(mouse.x) + std::abs(mouse.y - 40 - i * 40));
    delete_button_alpha = std::max(100.f, std::min(255.f, delete_button_alpha));
    deleteButton.SetColor(
        glm::vec4(1.0, 1.0, 1.0, delete_button_alpha / 255.f));
    screen().Draw(deleteButton);

    if (mouse_pressed) {
      if (mouse.y > 30 + i * 40 && mouse.y < 70 + i * 40) {
        if (mouse.x > 30 + decale && mouse.x < 400 + decale) {
          on_name_selected(it.first);
        } else {
          if (mouse.x >= 0 && mouse.x <= 24 && mouse.y >= 30 + i * 40 &&
              mouse.y <= 24 + 30 + i * 40) {
            question_ = std::make_unique<Question>();
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

  // button new game
  if (mouse.y < 480 && mouse.y > 480 - 64 && mouse.x > 640 / 2 - 300 / 2 &&
      mouse.x < 640 / 2 + 300 / 2) {
    newGame.SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    if (mouse_pressed) {
      screen().Draw(newGame);
      screen().Draw(newGameText);

      get_string_ = std::make_unique<GetString>(screen());
      get_string_->message = tr(L"enterYourName");
      get_string_->on_enter = [this](std::string name) {
        if (save_file_.saveList.count(name)) {
          question_ = std::make_unique<Question>();
          question_->question = tr(L"profileExistAlready");
          question_->yes = tr(L"okay");
          question_->no = tr(L"");
        }
        else
          save_file_.saveList[name] = 0;
      };
    }
  } else {
    newGame.SetColor(glm::vec4(200, 200, 200, 255) / 255.f);
  }
  screen().Draw(newGame);
  screen().Draw(newGameText);


  if (question_) {
    if (question_->Draw(screen()))
      question_.reset();
  }

  if (get_string_) {
    if (get_string_->Draw(screen()))
      get_string_.reset();
  }

  screen().Display();
}

std::string* character_callback_string = nullptr;
void character_callback(GLFWwindow* , unsigned int codepoint)
{
  if (!character_callback_string)
    return;
  *character_callback_string += (wchar_t)codepoint;
}

MainScreen::GetString::GetString(smk::Screen& screen) : screen_(screen) {
  character_callback_string = &typed_text_;
  glfwSetCharCallback(screen_.window(), character_callback);
}

MainScreen::GetString::~GetString() {
  glfwSetCharCallback(screen_.window(), nullptr);
}

bool MainScreen::GetString::Draw(smk::Screen& screen) {
  {
    if (time_ <= -1) {
      time_ = screen.time();
    }
    float target = exiting_ ? 0.0 : 1.0;
    for (int i = 0; i < 10; ++i) {
      alpha += (target - alpha) * (screen.time() - time_);
    }

    if (exiting_ && alpha <= 0.01)
      return true;
    time_ = screen.time();
  }

  // Black shadow.
  {
    smk::Shape black_shadow = smk::Shape::Square();
    black_shadow.SetPosition(0,0);
    black_shadow.SetScale(640,480);
    black_shadow.SetColor(glm::vec4(0, 0, 0, 0.5 * alpha));
    screen.Draw(black_shadow);
  }

  // Frame
  {
    smk::Sprite frame_sprite;
    frame_sprite.SetTexture(img_cadreInput);
    frame_sprite.SetColor(glm::vec4(1.0, 1.0, 1.0, alpha));
    frame_sprite.SetPosition(640 / 2 - img_cadreInput.width / 2,
                             480 / 2 - img_cadreInput.height / 2);
    screen.Draw(frame_sprite);
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
    screen.Draw(enter_your_name);
  }


  // Written text
  {
    smk::Text text;
    text.SetFont(font_arial);
    text.SetString(typed_text_);
    auto dimension = text.ComputeDimensions();
    text.SetPosition(640 / 2 - dimension.x / 2, 480 / 2 - dimension.y / 2);
    text.SetColor(glm::vec4(0.0, 0.0, 0.0, alpha));
    screen.Draw(text);

    if (screen.input().IsKeyPressed(GLFW_KEY_BACKSPACE) ||
        dimension.x > img_cadreInput.width - 12) {
      typed_text_ = typed_text_.substr(0, typed_text_.size() - 1);
    }

    if (screen.input().IsKeyPressed(GLFW_KEY_ENTER)) {
      on_enter(typed_text_);
      exiting_ = true;
    }
  }

  return false;
}

bool MainScreen::Question::Draw(smk::Screen& screen) {
  {
    if (time_ <= -1) {
      time_ = screen.time();
    }
    float target = exiting_ ? 0.0 : 1.0;
    for (int i = 0; i < 10; ++i) {
      alpha += (target - alpha) * (screen.time() - time_);
    }

    if (exiting_ && alpha <= 0.01)
      return true;
    time_ = screen.time();
  }

  // Black shadow.
  {
    smk::Shape black_shadow = smk::Shape::Square();
    black_shadow.SetPosition(0,0);
    black_shadow.SetScale(640,480);
    black_shadow.SetColor(glm::vec4(0, 0, 0, 0.5 * alpha));
    screen.Draw(black_shadow);
  }

  // White Shadow
  {
    smk::Shape white_shadow = smk::Shape::Square();
    white_shadow.SetPosition(640 * 0.2, 480 * 0.2);
    white_shadow.SetScale(640 * 0.6, 480 * 0.6);
    white_shadow.SetColor(glm::vec4(1, 1, 1, alpha));
    screen.Draw(white_shadow);
  }

  // Question
  {
    smk::Text text_string;
    text_string.SetFont(font_arial);
    text_string.SetString(question);
    auto dimension = text_string.ComputeDimensions();
    text_string.SetPosition(640 * 0.5 - dimension.x / 2, 480 * 0.2 + 10);
    text_string.SetColor(glm::vec4(0.f, 0.f, 0.f, alpha));
    screen.Draw(text_string);
  }

  // Yes answer
  {
    smk::Text yes_string;
    yes_string.SetFont(font_arial);
    yes_string.SetString(yes);
    auto dimension = yes_string.ComputeDimensions();
    float left = 640*0.2+10;
    float right = left + dimension.x;
    float bottom = 480*0.8-10;
    float top = bottom - dimension.y;
    yes_string.SetPosition(left, top);

    if (screen.input().mouse().x >= left &&   //
        screen.input().mouse().x <= right &&  //
        screen.input().mouse().y >= top &&    //
        screen.input().mouse().y <= bottom) {
      yes_string.SetColor(glm::vec4(0.f, 0.f, 0.f, alpha));
      if (screen.input().IsMousePressed(GLFW_MOUSE_BUTTON_1) && !exiting_) {
        on_yes();
        exiting_ = true;
      }
    } else {
      yes_string.SetColor(glm::vec4(0.5, 0.5, 0.5, alpha));
    }

    screen.Draw(yes_string);
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

    if (screen.input().mouse().x >= left &&   //
        screen.input().mouse().x <= right &&  //
        screen.input().mouse().y >= top &&    //
        screen.input().mouse().y <= bottom) {
      no_string.SetColor(glm::vec4(0.0, 0.0, 0.0, alpha));
      if (screen.input().IsMousePressed(GLFW_MOUSE_BUTTON_1) && !exiting_) {
        on_no();
        exiting_ = true;
      }
    } else {
      no_string.SetColor(glm::vec4(0.5, 0.5, 0.5, alpha));
    }
    screen.Draw(no_string);
  }

  return false;
}
