#include "activity/MainScreen.hpp"

#include "Lang.hpp"
#include "Resource.hpp"
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <smk/View.hpp>
#include <smk/Color.hpp>

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
  float previous_time = screen().time();
  languageXPos[0] = 640;
  languageXPos[1] = 640;
  languageXPos[2] = 640;
}

void MainScreen::Draw() {
  screen().PoolEvents();
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

  // Clock timeClock;
  glm::vec2 mouse = screen().input().mouse();
  bool mouse_pressed = screen().input().IsMousePressed(GLFW_MOUSE_BUTTON_1);

  ///// Draw

  // Draw the background.
  for (int x = 0; x <= 640; x += 24) {
    for (int y = 0; y <= 480; y += 24) {
      background.SetPosition(x, y);
      screen().Draw(background);
    }
  }

  // Draw the save files.
  int i = 0;
  for (auto& it : save_file_.saveList) {
    (void)it;
    float decale = std::max(5.f, std::min(std::abs(mouse.y - (50 + i * 40)), 40.f));

    // rectangle
    smk::Shape rectangle =
        smk::Shape::Rectangle(30, 30 + i * 40, 400, 70 + i * 40,
                              glm::vec4(decale + 50, 2 * decale + 100,
                                        2 * decale + 150, 255 - decale * 4) /
                                  255.f,
                              3, glm::vec4(0, 0, 0, 0));
    rectangle.Move(decale, 0);
    screen().Draw(rectangle);

    // text
    smk::Text text;
    text.SetFont(font_arial);
    text.SetString(it.name + "  /  " + intToString(it.level));
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
          on_name_selected(it.name);
        } else {
          if (mouse.x >= 0 && mouse.x <= 24 && mouse.y >= 30 + i * 40 &&
              mouse.y <= 24 + 30 + i * 40) {
            // if (Question(tr(L"confirmDelete1") + L"\n" +
            // tr(L"confirmDelete2") + L"\n" + tr(L"confirmDelete3") +
            // StringToWString(it.name),
            // tr(L"yes"), tr(L"no"))) {
            save_file_.DeleteProfile(it.name);
            i++;
            break;
            //}
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
      std::string name = GetName();
      if (save_file_.ExistProfile(name)) {
        Popup(tr(L"profileExistAlready"));
      } else {
        save_file_.NewProfile(name);
      }
    }
  } else {
    newGame.SetColor(glm::vec4(200, 200, 200, 255) / 255.f);
  }
  screen().Draw(newGame);
  screen().Draw(newGameText);

  // bouton language
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

    // escape button
    if (screen().input().IsKeyPressed(GLFW_KEY_ESCAPE))
      on_quit();

    //if (t > 0) {
      //smk::Shape rect =
          //smk::Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, t / 255.f));
      //screen().Draw(rect);
      //t -= 4;
    //}
  }

  screen().Display();
}

std::string MainScreen::GetName() {
  // text
  // Text text;
  // text.SetFont(font_arial);
  // text.SetString(tr(L"enterYourName"));
  // text.SetColor(glm::vec4(100, 100, 100, 255) / 255.f);
  // text.SetPosition(320, 240);
  // FloatRect position = text.GetRect();
  // Text.SetPosition(320 - position.GetWidth() / 2, 240 - 30 / 2);
  std::string text = "";

  // cadre
  smk::Sprite sprCadreInput;
  sprCadreInput.SetTexture(img_cadreInput);
  sprCadreInput.SetPosition(640 / 2 - 320 / 2, 480 / 2 - 64 / 2);

  // arriere plan
  smk::Shape arrierePlan =
      smk::Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, 0.05), 0);

  // event & clock
  // Event event;
  // Clock timeClock;
  bool continuer = true;

  // Image background = screen.Capture();
  smk::Sprite backSpr;
  // backSpr.SetTexture(background);

  // while (continuer) {
  // while (screen.GetEvent(event)) {
  // if (event.Type == sf::Event::TextEntered) {
  // if (event.Text.Unicode == 8) {
  // if (!text.empty()) {
  // text.erase(text.end() - 1);
  // Text.SetString(text);
  //}

  //} else if (event.Text.Unicode == 13) {
  // continuer = false;
  //} else if (event.Text.Unicode < 128) {
  // if (position.GetWidth() < 285) {
  // text += static_cast<char>(event.Text.Unicode);
  // Text.SetString(text);
  // Text.SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
  //}
  //}
  // position = Text.GetRect();
  // Text.SetPosition(320 - position.GetWidth() / 2, 240 - 30 / 2);
  //}
  //}
  screen().Draw(backSpr);
  screen().Draw(arrierePlan);
  screen().Draw(sprCadreInput);
  // screen().Draw(Text);
  // Sleep(float(1.0 / 30.0 - timeClock.GetElapsedTime()));
  // timeClock.Reset();
  //}
  return text;
}

void MainScreen::Popup(std::wstring message) {
  // Clock timeClock;
  smk::Shape arrierePlan =
      smk::Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, 0.05));
  smk::Shape rectangle =
      smk::Shape::Rectangle(640 * 0.2, 480 * 0.2, 640 * 0.8, 480 * 0.8,
                       glm::vec4(1.0, 1.0, 1.0, 1.0));

  smk::Text text;
  text.SetFont(font_arial);
  text.SetString(message);
  // text.SetPosition(640 / 2 - text.GetRect().GetWidth() / 2,
  // 480 / 2 - text.GetRect().GetHeight());
  text.SetColor(smk::Color::Black);

  // Event event;
  // while (screen.GetEvent(event))
  //;

  // Image background = screen.Capture();
  smk::Sprite backSpr;
  // backSpr.SetTexture(background);

  // while (1) {
  // while (screen.GetEvent(event)) {
  // if (event.Type == Event::MouseButtonPressed) {
  // if (event.MouseButton.Button == sf::Mouse::Left) {
  // return;
  //}
  //}

  // if ((event.Type == sf::Event::KeyPressed))
  // return;
  //}

  screen().Draw(backSpr);
  screen().Draw(arrierePlan);
  screen().Draw(rectangle);
  // screen().Draw(text);

  // Sleep(float(1.0 / 20.0 - timeClock.GetElapsedTime()));
  // timeClock.Reset();
  //}
}

bool MainScreen::Question(std::wstring message, std::wstring q1, std::wstring q2) {
  // Clock timeClock;
  smk::Shape arrierePlan =
      smk::Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, 0.05));
  smk::Shape rectangle =
      smk::Shape::Rectangle(640 * 0.2, 480 * 0.2, 640 * 0.8, 480 * 0.8,
                       glm::vec4(1.0, 1.0, 1.0, 1.0));

  smk::Text text;
  text.SetFont(font_arial);
  text.SetString(message);
  // text.SetPosition(640 / 2 - text.GetRect().GetWidth() / 2,
  // 480 / 2 - text.GetRect().GetHeight());
  text.SetColor(glm::vec4(0.f, 0.f, 0.f, 0.f));

  smk::Text q1String;
  q1String.SetFont(font_arial);
  smk::Text q2String;
  q2String.SetFont(font_arial);
  q1String.SetString(q1);
  q2String.SetString(q2);
  // q1String.SetPosition(640 * 0.2 + 10,
  // 480 * 0.8 - q1String.GetRect().GetHeight() - 10);
  // q2String.SetPosition(640 * 0.8 - q2String.GetRect().GetWidth() - 10,
  // 480 * 0.8 - q2String.GetRect().GetHeight() - 10);
  q1String.SetColor(glm::vec4(0.f, 0.f, 0.f, 1.f));
  q2String.SetColor(glm::vec4(0.f, 0.f, 0.f, 1.f));

  // Color black = glm::vec4(0.0, 0.0, 0.0, 1.0);
  glm::vec4 gray = glm::vec4(100.0, 100.0, 100.0, 255.f) / 255.f;

  // int bottom = 480 * 0.8;
  // int top = 480 * 0.8 - 20 - q1String.GetRect().GetHeight();
  // int leftq1 = 640 * 0.2;
  // int rightq1 = 640 * 0.2 + 20 + q1String.GetRect().GetWidth();
  // int leftq2 = 640 * 0.8 - 20 - q2String.GetRect().GetWidth();
  // int rightq2 = 640 * 0.8;

  int bottom, topleftq1, rightq1, leftq2, rightq2;
  bottom = topleftq1 = rightq1 = leftq2 = rightq2 = 0;
  (void)bottom;

  // Event event;
  // while (screen.GetEvent(event))
  //;

  // int mouse.x = 0;
  // int mouse.y = 0;
  bool mouse_pressed = false;
  (void)mouse_pressed;

  // Image background = screen.Capture();
  smk::Sprite backSpr;
  // backSpr.SetTexture(background);

  while (1) {
    mouse_pressed = false;
    // while (screen.GetEvent(event)) {
    // if (event.Type == Event::MouseButtonPressed) {
    // if (event.MouseButton.Button == sf::Mouse::Left) {
    // mouse_pressed = true;
    //}
    //}

    // if (event.Type == Event::MouseMoved) {
    // mouse.x = event.MouseMove.X;
    // mouse.y = event.MouseMove.Y;
    //}
    //}

    screen().Draw(backSpr);
    screen().Draw(arrierePlan);
    screen().Draw(rectangle);
    screen().Draw(text);
    screen().Draw(q1String);
    screen().Draw(q2String);

    q1String.SetColor(gray);
    q2String.SetColor(gray);

    // if (mouse.y >= top && mouse.y <= bottom) {
    // if (mouse.x >= leftq1 && mouse.x <= rightq2) {
    // if (mouse.x <= rightq1) {
    // q1String.SetColor(black);
    // if (mouse_pressed)
    // return true;
    //} else if (mouse.x >= leftq2) {
    // q2String.SetColor(black);
    // if (mouse_pressed)
    // return false;
    //}
    //}
    //}

    // Sleep(float(1.0 / 10.0 - timeClock.GetElapsedTime()));
    // timeClock.Reset();
  }
}
