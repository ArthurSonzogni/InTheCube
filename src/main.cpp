#include "BackgroundMusic.hpp"
#include "Input.hpp"
#include "Lang.hpp"
#include "Level.hpp"
#include "LevelListLoader.hpp"
#include "SaveManager.hpp"
#include "Shape.hpp"
#include "Text.hpp"

#include "Screen.hpp"

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

int main(int argc, char const* argv[]);
std::string getName();
void popup(std::wstring message);
bool question(std::wstring message, std::wstring q1, std::wstring q2);
std::string intToString(int n);

Screen* screen = nullptr;
void Loop();

BackgroundMusic backMusic;

class WelcomeScreen {
 public:
  void Draw();
  bool quit_ = false;

 private:
  int step_ = 0;
};
WelcomeScreen welcome_screen;

class MainScreen {
 public:
  void Draw();
  bool quit_ = false;

 private:
  int languageXPos[3] = {640, 640, 640};
  int t = 255;
};
MainScreen main_screen;

class IntroScreen {
 public:
  void Draw();
  bool quit_ = false;

 private:
  int t = 0;

  int position = -1;
  float xpos = 0;
  float Dxpos = 0;

  int Qxpos = 0;
  float Rxpos = 0;

  int timeDelay = 10;

  const int r[6] = {100, 0, 200, 100, 0, 0};
  const int g[6] = {100, 100, 0, 100, 100, 0};
  const int b[6] = {100, 200, 0, 0, 100, 0};
};

IntroScreen intro_screen;

float start_time;
int frame = 0;

int main(int argc, char const* argv[]) {
  std::locale::global(std::locale("C.UTF-8"));
  Screen my_screen(640, 480, "InTheCube");
  screen = &my_screen;
  start_time = glfwGetTime();
  frame = 0;
  my_screen.SetLoop(Loop);
  my_screen.Run();
  return EXIT_SUCCESS;
}

enum class State {
  Init,
  WelcomeScreenStep,
  MainScreenStep,
  LevelStep,
};
State state = State::Init;
int level_index = 0;
Level level;
bool level_loaded = false;

SaveManager savFile(P"sav/gameSav");
SaveManager langFile(P"sav/language");

void Loop() {
  
  float new_time = glfwGetTime();
  int new_frame = (new_time - start_time) * 30;

  if (new_frame > frame + 10) {
    std::cerr << "Skip " << new_frame - frame << " frames" << std::endl;
    frame = 0;
    start_time = new_time;
    return;
  }

  if (new_frame <= frame) {
    return;
  }

  frame++;

  if (state == State::Init) {
    initRessource();

    // load traduction
    // clang-format off
    switch (langFile.GetLevel("language")) {
      case 0: LoadTraduction(P"lang/lang_fr"); break;
      case 1: LoadTraduction(P"lang/lang_en"); break;
      case 2: LoadTraduction(P"lang/lang_de"); break;
    }
    state = State::WelcomeScreenStep;
  }

  if (state == State::WelcomeScreenStep) {
    welcome_screen.Draw();
    if (welcome_screen.quit_) {
      state = State::MainScreenStep;
    }
  }

  if (state == State::MainScreenStep) {
    main_screen.Draw();
    if (main_screen.quit_) {
      state = State::LevelStep;
      level_index = 0;
    }
  }

  if (state == State::LevelStep) {
    if (level_index == 0 && !intro_screen.quit_) {
      intro_screen.Draw();
    } else {
      if (!level_loaded) {
        level_loaded = true;
        // load the list of Level
        level = Level();
        std::vector<std::string> levelList = LevelListLoader();
        level.LoadFromFile(levelList[level_index]);
      }
      // Start the BackgroundMusic
      //backMusic.Start();

      //screen->Clear(glm::vec4(0.0, 0.0, 0.0, 1.0));
      level.Step(*screen);
      level.Draw(*screen);

      if (level.isLose) {
        level_loaded = false;
      }

      if (level.isWin) {
        level_index++;
        level_loaded = false;
        //runTheLevel = false;
        //savFile.SetLevel(name, level_index);
      }

      if (level.isEscape) {
        level_loaded = false;
        state = State::MainScreenStep;
      }
    }
  }
}

void Remaining() {
  // Draw accueil
  //accueil();

  SaveManager savFile(P"sav/gameSav");
  SaveManager langFile(P"sav/language");
  std::vector<std::string> levelList = LevelListLoader();

  // load traduction
  // clang-format off
  switch (langFile.GetLevel(P"language")) {
    case 0: LoadTraduction(P"lang/lang_fr"); break;
    case 1: LoadTraduction(P"lang/lang_en"); break;
    case 2: LoadTraduction(P"lang/lang_de"); break;
  }
  // clang-format on

  // main screen
  std::string name;
  // mainScreen();

  // Start main loop
  unsigned int level_index = savFile.GetLevel(name);

   //introduction
  //if (level_index == 0) {
    //intro();
  //}

  backMusic.ChangeMusic(P"snd/backgroundMusic.ogg", 50);

  while (level_index < levelList.size()) {
    // load the Level
    Level level;
    level.LoadFromFile(levelList[level_index]);
    bool runTheLevel = true;

    // change the BackgroundMusic
    backMusic.SetLevel(levelList[level_index]);

    // Clock timeClock;
    while (runTheLevel) {
      backMusic.Step();
      level.Step(*screen);
      level.Draw(*screen);

      // check the end
      if (level.isLose)
        runTheLevel = false;
      if (level.isWin) {
        runTheLevel = false;
        level_index++;
        savFile.SetLevel(name, level_index);
      }
      if (level.isEscape)
        return;
    }
  }
}

double sqr(double x) {
  return x * x;
}

std::wstring StringToWString(const std::string& s) {
  std::wstring temp(s.length(), L' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

void MainScreen::Draw() {
  View view;
  view.SetCenter(320, 240);
  view.SetSize(640, 480);
  screen->SetView(view);

  Sprite sprLanguage[3];
  sprLanguage[0].SetTexture(img_frenchFlag);
  sprLanguage[1].SetTexture(img_englishFlag);
  sprLanguage[2].SetTexture(img_deutschFlag);
  sprLanguage[0].SetPosition(640, 0);
  sprLanguage[1].SetPosition(640, 100);
  sprLanguage[2].SetPosition(640, 200);

  Sprite deleteButton;
  Sprite newGame;
  Sprite background;

  deleteButton.SetTexture(img_deleteButton);

  newGame.SetTexture(img_newGame);
  newGame.SetPosition(320 - 300 / 2, 480 - 64);
  Text newGameText;
  newGameText.SetFont(font_arial);
  newGameText.SetString(tr(L"newGame"));
  newGameText.SetPosition(220, 430);
  newGameText.SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));

  background.SetTexture(img_background);

  std::string name;

  // Clock timeClock;
  int mouse_x = Input::MouseX();
  int mouse_y = Input::MouseY();
  bool mouse_pressed = Input::IsMousePressed(GLFW_MOUSE_BUTTON_1);

  ///// Draw

  // Draw the background.
  for (int x = 0; x <= 640; x += 24) {
    for (int y = 0; y <= 480; y += 24) {
      background.SetPosition(x, y);
      screen->Draw(background);
    }
  }

  // Draw the save files.
  int i = 0;
  for (auto& it : savFile.saveList) {
    (void)it;
    int decale = std::max(5, std::min(std::abs(mouse_y - (50 + i * 40)), 40));

    // rectangle
    Shape rectangle =
        Shape::Rectangle(30, 30 + i * 40, 400, 70 + i * 40,
                         glm::vec4(decale + 50, 2 * decale + 100,
                                   2 * decale + 150, 255 - decale * 4) /
                             255.f,
                         3, glm::vec4(0, 0, 0, 0));
    rectangle.Move(decale, 0);
    screen->Draw(rectangle);

    // text
    Text text;
    text.SetFont(font_arial);
    text.SetString(it.name + "  /  " + intToString(it.level));
    text.SetPosition(40, 30 + i * 40);
    text.SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
    text.Move(decale, 0);
    screen->Draw(text);

    text.Move(-2, -2);
    text.SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    screen->Draw(text);

    // deleteButton
    deleteButton.SetPosition(1, 30 + i * 40);
    float delete_button_alpha =
        8000.0 / (std::abs(mouse_x) + std::abs(mouse_y - 40 - i * 40));
    delete_button_alpha = std::max(100.f, std::min(255.f, delete_button_alpha));
    deleteButton.SetColor(
        glm::vec4(1.0, 1.0, 1.0, delete_button_alpha / 255.f));
    screen->Draw(deleteButton);

    if (mouse_pressed) {
      if (mouse_y > 30 + i * 40 and mouse_y < 70 + i * 40) {
        if (mouse_x > 30 + decale and mouse_x < 400 + decale) {
          quit_ = true;
          name = it.name;
          return;
        } else {
          if (mouse_x >= 0 and mouse_x <= 24 and mouse_y >= 30 + i * 40 and
              mouse_y <= 24 + 30 + i * 40) {
            // if (question(tr(L"confirmDelete1") + L"\n" +
            // tr(L"confirmDelete2") + L"\n" + tr(L"confirmDelete3") +
            // StringToWString(it.name),
            // tr(L"yes"), tr(L"no"))) {
            savFile.DeleteProfile(it.name);
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
  if (mouse_y < 480 and mouse_y > 480 - 64 and mouse_x > 640 / 2 - 300 / 2 and
      mouse_x < 640 / 2 + 300 / 2) {
    newGame.SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    if (mouse_pressed) {
      screen->Draw(newGame);
      screen->Draw(newGameText);
      std::string name = getName();
      if (savFile.ExistProfile(name)) {
        popup(tr(L"profileExistAlready"));
      } else {
        savFile.NewProfile(name);
      }
    }
  } else {
    newGame.SetColor(glm::vec4(200, 200, 200, 255) / 255.f);
  }
  screen->Draw(newGame);
  screen->Draw(newGameText);

  // bouton language
  for (int i = 0; i < 3; i++) {
    if (mouse_x >= 640 - 128 and mouse_x <= 640 and mouse_y > 100 * i and
        mouse_y <= 100 * i + 64) {
      sprLanguage[i].SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
      languageXPos[i] += (640 - 128 - languageXPos[i]) / 10;
      if (mouse_pressed) {
        std::cout << "coucou" << std::endl;
        // setting the language
        langFile.SetLevel("language", i);
        // load traduction
        // clang-format off
        switch (langFile.GetLevel("language")) {
          case 0: LoadTraduction(P"lang/lang_fr"); break;
          case 1: LoadTraduction(P"lang/lang_en"); break;
          case 2: LoadTraduction(P"lang/lang_de"); break;
          default:
        std::cout << "merde" << std::endl;
        }
        // clang-format on
        newGameText.SetString(tr(L"newGame"));
        newGameText.SetPosition(220, 430);
      }
    } else {
      sprLanguage[i].SetColor(glm::vec4(125, 125, 125, 255) / 255.f);
      languageXPos[i] += (640 - 100 - languageXPos[i]) / 10;
    }
    sprLanguage[i].SetPosition(languageXPos[i], 100 * i);
    screen->Draw(sprLanguage[i]);

    // escape button
    // if (screen.GetInput().IsKeyDown(Key::Escape)) {
    // exit(0);
    //}

    if (t > 0) {
      Shape rect =
          Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, t / 255.f));
      screen->Draw(rect);
      t -= 4;
    }
  }
}

std::string getName() {
  // text
  //Text text;
  //text.SetFont(font_arial);
  //text.SetString(tr(L"enterYourName"));
  //text.SetColor(glm::vec4(100, 100, 100, 255) / 255.f);
  //text.SetPosition(320, 240);
  // FloatRect position = text.GetRect();
  // Text.SetPosition(320 - position.GetWidth() / 2, 240 - 30 / 2);
  std::string text = "";

  // cadre
  Sprite sprCadreInput;
  sprCadreInput.SetTexture(img_cadreInput);
  sprCadreInput.SetPosition(640 / 2 - 320 / 2, 480 / 2 - 64 / 2);

  // arriere plan
  Shape arrierePlan =
      Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, 0.05), 0);

  // event & clock
  // Event event;
  // Clock timeClock;
  bool continuer = true;

  // Image background = screen.Capture();
  Sprite backSpr;
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
  screen->Draw(backSpr);
  screen->Draw(arrierePlan);
  screen->Draw(sprCadreInput);
  //screen->Draw(Text);
  // Sleep(float(1.0 / 30.0 - timeClock.GetElapsedTime()));
  // timeClock.Reset();
  //}
  return text;
}

void popup(std::wstring message) {
  // Clock timeClock;
  Shape arrierePlan =
      Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, 0.05));
  Shape rectangle = Shape::Rectangle(640 * 0.2, 480 * 0.2, 640 * 0.8, 480 * 0.8,
                                     glm::vec4(1.0, 1.0, 1.0, 1.0));

  Text text;
  text.SetFont(font_arial);
  text.SetString(message);
  // text.SetPosition(640 / 2 - text.GetRect().GetWidth() / 2,
  // 480 / 2 - text.GetRect().GetHeight());
  text.SetColor(glm::vec4(0.f, 0.f, 0.f, 1.0));

  // Event event;
  // while (screen.GetEvent(event))
  //;

  // Image background = screen.Capture();
  Sprite backSpr;
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

  screen->Draw(backSpr);
  screen->Draw(arrierePlan);
  screen->Draw(rectangle);
  //screen->Draw(text);

  // Sleep(float(1.0 / 20.0 - timeClock.GetElapsedTime()));
  // timeClock.Reset();
  //}
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

bool question(std::wstring message, std::wstring q1, std::wstring q2) {
  // Clock timeClock;
  Shape arrierePlan =
      Shape::Rectangle(0, 0, 640, 480, glm::vec4(0, 0, 0, 0.05));
  Shape rectangle = Shape::Rectangle(640 * 0.2, 480 * 0.2, 640 * 0.8, 480 * 0.8,
                                     glm::vec4(1.0, 1.0, 1.0, 1.0));

  Text text;
  text.SetFont(font_arial);
  text.SetString(message);
  // text.SetPosition(640 / 2 - text.GetRect().GetWidth() / 2,
  // 480 / 2 - text.GetRect().GetHeight());
  text.SetColor(glm::vec4(0.f, 0.f, 0.f, 0.f));

  Text q1String;
  q1String.SetFont(font_arial);
  Text q2String;
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

  // int mouse_x = 0;
  // int mouse_y = 0;
  bool mouse_pressed = false;
  (void)mouse_pressed;

  // Image background = screen.Capture();
  Sprite backSpr;
  //backSpr.SetTexture(background);

  while (1) {
    mouse_pressed = false;
    // while (screen.GetEvent(event)) {
    // if (event.Type == Event::MouseButtonPressed) {
    // if (event.MouseButton.Button == sf::Mouse::Left) {
    // mouse_pressed = true;
    //}
    //}

    // if (event.Type == Event::MouseMoved) {
    // mouse_x = event.MouseMove.X;
    // mouse_y = event.MouseMove.Y;
    //}
    //}

    screen->Draw(backSpr);
    screen->Draw(arrierePlan);
    screen->Draw(rectangle);
    screen->Draw(text);
    screen->Draw(q1String);
    screen->Draw(q2String);

    q1String.SetColor(gray);
    q2String.SetColor(gray);

    // if (mouse_y >= top and mouse_y <= bottom) {
    // if (mouse_x >= leftq1 and mouse_x <= rightq2) {
    // if (mouse_x <= rightq1) {
    // q1String.SetColor(black);
    // if (mouse_pressed)
    // return true;
    //} else if (mouse_x >= leftq2) {
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

void intro() {
  // Clock timeClock;
  glm::vec4 background_color(0.0,0.0,0.0,1.0);

  Text text1;
  text1.SetFont(font_arial);
  text1.SetString(tr(L"intro11") + L"\n" + tr(L"intro12") + L"\n" +
                  tr(L"intro13") + L"\n" + tr(L"intro14"));
  text1.SetColor(glm::vec4(1.0,1.0,1.0,1.0));
  text1.SetPosition(10, 10);

  Text text2;
  text2.SetFont(font_arial);
  text2.SetString(tr(L"intro21") + L"\n" + tr(L"intro22") + L"\n" +
                  tr(L"intro23") + L"\n" + tr(L"intro24"));
  text2.SetColor(glm::vec4(1.0,1.0,1.0,1.0));
  text2.SetPosition(640, 10);

  Text text3;
  text3.SetFont(font_arial);
  text3.SetString(tr(L"intro31") + L"\n" + tr(L"intro32") + L"\n" +
                  tr(L"intro33") + L"\n" + tr(L"intro34"));
  text3.SetColor(glm::vec4(1.0,1.0,1.0,1.0));
  text3.SetPosition(1280, 10);

  Text text4;
  text4.SetFont(font_arial);
  text4.SetString(tr(L"intro41") + L"\n" + tr(L"intro42") + L"\n" +
                  tr(L"intro43") + L"\n" + tr(L"intro44") + L"\n" +
                  tr(L"intro45"));
  text4.SetColor(glm::vec4(1.0,1.0,1.0,1.0));
  text4.SetPosition(1280, 10);

  Text text5;
  text5.SetFont(font_arial);
  text5.SetString(tr(L"intro51") + L"\n" + tr(L"intro52") + L"\n" +
                  tr(L"intro53") + L"\n" + tr(L"intro54"));
  text5.SetColor(glm::vec4(1.0,1.0,1.0,1.0));
  text4.SetPosition(1280, 10);

  int position = 0;
  float xpos = 0;
  float Dxpos = 0;

  int Qxpos = 0;
  float Rxpos = 0;

  int r[6] = {100, 0, 200, 100, 0, 0};
  int g[6] = {100, 100, 0, 100, 100, 0};
  int b[6] = {100, 200, 0, 0, 100, 0};

  int timeDelay = 10;

  while (1) {
    // input
    if (timeDelay > 0)
      timeDelay--;
    // Event event;
    // while (screen.GetEvent(event)) {
    // if (event.Type == Event::KeyPressed or
    // event.Type == Event::MouseButtonPressed) {
    // if (timeDelay == 0) {
    // position++;
    // timeDelay = 90;
    //}
    //}
    //}

    int i = 0;
    while (i++ < 2) {
      Dxpos += (position * 640 - xpos) / 1000;
      Dxpos *= 0.955;
      xpos += Dxpos;
    }

    text1.SetPosition(30 - xpos, 10);
    text2.SetPosition(30 - xpos + 640, 10);
    text3.SetPosition(30 - xpos + 2 * 640, 10);
    text4.SetPosition(30 - xpos + 3 * 640, 10);
    text5.SetPosition(30 - xpos + 4 * 640, 10);

    Qxpos = xpos / 640;
    Rxpos = int(xpos - Qxpos * 640);
    background_color =
        glm::vec4((Rxpos * r[Qxpos + 1] + (640 - Rxpos) * r[Qxpos]) / 640,
                  (Rxpos * g[Qxpos + 1] + (640 - Rxpos) * g[Qxpos]) / 640,
                  (Rxpos * b[Qxpos + 1] + (640 - Rxpos) * b[Qxpos]) / 640,
                  255) /
        255.f;
    // screen.Clear(background_color);

    screen->Draw(text1);
    screen->Draw(text2);
    screen->Draw(text3);
    screen->Draw(text4);
    screen->Draw(text5);

    // Sleep(float(1.0 / 60.0 - timeClock.GetElapsedTime()));
    // timeClock.Reset();

    if (xpos > 640 * 4.9)
      return;
  }
}

void WelcomeScreen::Draw() {
  View view;
  view.SetCenter(320, 240);
  view.SetSize(640, 480);
  screen->SetView(view);

  int mode = 0;
  bool pressed = false;
  // Clock timeClock;

  Sprite spr;
  spr.SetTexture(img_accueil);

  if (Input::IsMousePressed(GLFW_MOUSE_BUTTON_1) ||
      Input::IsKeyPressed(GLFW_KEY_SPACE) ||
      Input::IsKeyPressed(GLFW_KEY_ENTER)) {
    quit_ = true;
  }

  // Event event; while (screen.GetEvent(event)) {}

  // pressed = false;
  // while (screen.GetEvent(event)) {
  // if ((event.Type == sf::Event::KeyPressed))
  // pressed = true;
  // if ((event.Type == sf::Event::MouseButtonPressed))
  // pressed = true;
  //}

  spr.SetColor(glm::vec4(step_ / 255.0, step_ / 255.0, step_ / 255.0, 1.0));
  screen->Draw(spr);

  switch (mode) {
    case 0: {
      if (step_ < 255)
        step_ += 5;
      else
        mode = 1;
    } break;

    case 1: {
      if (pressed)
        mode = 2;
    } break;

    case 2: {
      if (step_ > 3)
        step_ -= 10;
      else {
        step_ = 1;
        return;
      }
    } break;
  }

  // Sleep(float(1.0 / 20.0 - timeClock.GetElapsedTime()));
  // timeClock.Reset();
}

void IntroScreen::Draw() {
  glm::vec4 background_color(0.0,0.0,0.0,1.0);

  Text text1;
  text1.SetFont(font_arial);
  text1.SetString(tr(L"intro11") + L"\n" + tr(L"intro12") + L"\n" +
                  tr(L"intro13") + L"\n" + tr(L"intro14"));
  text1.SetColor(glm::vec4(1.0,1.0,1.0,1.0));

  Text text2;
  text2.SetFont(font_arial);
  text2.SetString(tr(L"intro21") + L"\n" + tr(L"intro22") + L"\n" +
                  tr(L"intro23") + L"\n" + tr(L"intro24"));
  text2.SetColor(glm::vec4(1.0,1.0,1.0,1.0));

  Text text3;
  text3.SetFont(font_arial);
  text3.SetString(tr(L"intro31") + L"\n" + tr(L"intro32") + L"\n" +
                  tr(L"intro33") + L"\n" + tr(L"intro34"));
  text3.SetColor(glm::vec4(1.0,1.0,1.0,1.0));

  Text text4;
  text4.SetFont(font_arial);
  text4.SetString(tr(L"intro41") + L"\n" + tr(L"intro42") + L"\n" +
                  tr(L"intro43") + L"\n" + tr(L"intro44") + L"\n" +
                  tr(L"intro45"));
  text4.SetColor(glm::vec4(1.0,1.0,1.0,1.0));

  Text text5;
  text5.SetFont(font_arial);
  text5.SetString(tr(L"intro51") + L"\n" + tr(L"intro52") + L"\n" +
                  tr(L"intro53") + L"\n" + tr(L"intro54"));
  text5.SetColor(glm::vec4(1.0,1.0,1.0,1.0));

  if (Input::IsKeyPressed(GLFW_KEY_SPACE) ||
      Input::IsKeyPressed(GLFW_KEY_ENTER) ||
      Input::IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
    position++;
  }

  int i = 0;
  while (i++ < 2) {
    Dxpos += (position * 640 - xpos) / 100;
    Dxpos *= 0.88;
    xpos += Dxpos;
  }

  text1.SetPosition(30 - xpos, 10);
  text2.SetPosition(30 - xpos + 640, 10);
  text3.SetPosition(30 - xpos + 2 * 640, 10);
  text4.SetPosition(30 - xpos + 3 * 640, 10);
  text5.SetPosition(30 - xpos + 4 * 640, 10);

  Qxpos = xpos / 640;
  Rxpos = int(xpos - Qxpos * 640);
  background_color =
      glm::vec4((Rxpos * r[Qxpos + 1] + (640 - Rxpos) * r[Qxpos]) / 640,
                (Rxpos * g[Qxpos + 1] + (640 - Rxpos) * g[Qxpos]) / 640,
                (Rxpos * b[Qxpos + 1] + (640 - Rxpos) * b[Qxpos]) / 640,
                255) /
      255.f;
  screen->Clear(background_color);

  // clang-format off
  if (position >= 0) screen->Draw(text1);
  if (position >= 1) screen->Draw(text2);
  if (position >= 2) screen->Draw(text3);
  if (position >= 3) screen->Draw(text4);
  if (position >= 4) screen->Draw(text5);
  // clang-format on

  if (xpos > 640 * 4.9)
    quit_ = true;
}
