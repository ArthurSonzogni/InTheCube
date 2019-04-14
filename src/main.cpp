#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Text.hpp>
#include "BackgroundMusic.hpp"
#include "Lang.hpp"
#include "Level.hpp"
#include "LevelListLoader.hpp"
#include "SaveManager.hpp"

#include <smk/Screen.hpp>

#include "activity/IntroScreen.hpp"
#include "activity/MainScreen.hpp"
#include "activity/WelcomeScreen.hpp"
#include "activity/LevelScreen.hpp"

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

int main(int argc, char const* argv[]);
smk::Screen* screen = nullptr;
void Loop();

BackgroundMusic backMusic;

float start_time;
int frame = 0;

enum class State {
  Init,
  WelcomeScreenStep,
  MainScreenStep,
  LevelStep,
};
State state = State::Init;
int level_index_ = 0;
Level level;
bool level_loaded = false;

SaveManager savFile(P "sav/gameSav");
SaveManager langFile(P "sav/language");

void UpdateTraduction() {
  // load traduction
  // clang-format off
  switch (langFile.GetLevel("language")) {
    case 0: LoadTraduction(P"lang/lang_fr"); break;
    case 1: LoadTraduction(P"lang/lang_en"); break;
    case 2: LoadTraduction(P"lang/lang_de"); break;
  }
  // clang-format on
}

void SetLanguage(int i) {
  langFile.SetLevel("language", i);
  UpdateTraduction();
}

class Main {
 public:
  Main()
      : welcome_screen_(screen),
        main_screen_(screen, savFile),
        intro_screen_(screen) {
    screen = smk::Screen(640, 480, "InTheCube");
    initRessource();
    UpdateTraduction();

    // 1. Starting activity. The welcome screen.
    activity_ = &welcome_screen_;
    welcome_screen_.on_quit = [&] { Display(&main_screen_); };

    // 2. Then the save / language selector
    main_screen_.on_update_traduction = SetLanguage;
    main_screen_.on_name_selected = [&](std::string player_name) {
      player_name_ = player_name;
      MoveToLevel(savFile.GetLevel(player_name));
    };
    main_screen_.on_quit = [&] { Display(&welcome_screen_); };

    // 3. The intro screen.
    intro_screen_.on_quit = [&] { MoveToLevel(1); };

    // 4. The level screen.
  }

  void Display(Activity* activity) {
    if (activity_)
      activity_->OnQuit();
    if (activity)
      activity->OnEnter();
    std::swap(activity_, activity);
  }

  void MoveToLevel(int index) {
    level_index_ = index;
    if (level_index_ == 0) {
      Display(&intro_screen_);
      return;
    }

    savFile.SetLevel(player_name_, index);

    to_be_removed_screen_ = std::move(level_screen_);
    level_screen_ =
        std::make_unique<LevelScreen>(screen, LevelListLoader()[level_index_]);
    level_screen_->on_restart = [&] { MoveToLevel(level_index_); };
    level_screen_->on_win = [&] { MoveToLevel(level_index_ + 1); };
    level_screen_->on_quit = [&] { Display(&main_screen_); };
    Display(level_screen_.get());
  }

  void Loop() { activity_->Draw(); }

 private:
  Activity* activity_;
  smk::Screen screen;

  WelcomeScreen welcome_screen_;
  MainScreen main_screen_;
  IntroScreen intro_screen_;
  std::unique_ptr<LevelScreen> level_screen_;
  std::unique_ptr<LevelScreen> to_be_removed_screen_;

  int level_index_ = 0;
  std::string player_name_;
};

#ifdef __EMSCRIPTEN__
std::function<void()> registered_loop;
void emscripten_loop() {
  registered_loop();
}
#endif

int main(int argc, char const* argv[]) {
  std::locale::global(std::locale("C.UTF-8"));

  Main main;
  // smk::Screen my_screen(640, 480, "InTheCube");
  // screen = &my_screen;
  start_time = glfwGetTime();
  frame = 0;

#ifdef __EMSCRIPTEN__
  registered_loop = [&]() { main.Loop(); };
  emscripten_set_main_loop(emscripten_loop, 0, 1);
#else
  while (1)
    main.Loop();
#endif
  return EXIT_SUCCESS;
}
