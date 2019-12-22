#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Audio.hpp>
#include <smk/Text.hpp>
#include "BackgroundMusic.hpp"
#include "Lang.hpp"
#include "Level.hpp"
#include "LevelListLoader.hpp"
#include "SaveManager.hpp"
#include "Resource.hpp"

#include <smk/Window.hpp>

#include "activity/IntroScreen.hpp"
#include "activity/LevelScreen.hpp"
#include "activity/MainScreen.hpp"
#include "activity/ResourceLoadingScreen.hpp"
#include "activity/WelcomeScreen.hpp"

BackgroundMusic background_music;

class Main {
 public:
  Main()
      : resource_loading_screen_(window_),
        welcome_screen_(window_),
        main_screen_(window_, savFile),
        intro_screen_(window_) {
    window_ = smk::Window(640, 480, "InTheCube");

    Display(&resource_loading_screen_);
    resource_loading_screen_.on_quit = [&] {
      savFile.Load(SavePath() + "/.in_the_cube_sav");
      langFile.Load(SavePath() + "/.in_the_cube_language");
      UpdateTraduction();
      Display(&welcome_screen_);
    };

    // 2. Starting activity. The welcome window_.
    welcome_screen_.on_quit = [&] { Display(&main_screen_); };

    // 3. Then the save / language selector
    main_screen_.on_update_traduction = [this](int i) { SetLanguage(i); };
    main_screen_.on_name_selected = [&](std::string player_name) {
      player_name_ = player_name;
      MoveToLevel(savFile.saveList[player_name]);
    };
    main_screen_.on_quit = [&] { Display(&welcome_screen_); };

    // 4. The intro window_.
    intro_screen_.on_quit = [&] { MoveToLevel(1); };

    // 5. The level window_.
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
    if (index == 0) {
      Display(&intro_screen_);
      return;
    }

    if (index >= (int)LevelListLoader().size()) {
      Display(&welcome_screen_);
      return;
    }

    savFile.saveList[player_name_] = index;
    savFile.Sync();

    to_be_removed_screen_ = std::move(level_screen_);
    level_screen_ =
        std::make_unique<LevelScreen>(window_, LevelListLoader()[level_index_]);
    level_screen_->on_restart = [&] { MoveToLevel(level_index_); };
    level_screen_->on_win = [&] { MoveToLevel(level_index_ + 1); };
    level_screen_->on_previous = [&] { MoveToLevel(level_index_ - 1); };
    level_screen_->on_quit = [&] { Display(&main_screen_); };
    Display(level_screen_.get());
  }

  void Loop() {
    activity_->Draw();
    background_music.Step();
    to_be_removed_screen_.reset();

#ifndef __EMSCRIPTEN__
    window_.LimitFrameRate(60.f);
#endif
  }

  void SetLanguage(int i) {
    langFile.saveList["language"] = i;
    langFile.Sync();
    UpdateTraduction();
  }

  void UpdateTraduction() {
    // load traduction
    // clang-format off
    switch (langFile.saveList["language"]) {
      case 0: LoadTraduction(ResourcePath() + "/lang/lang_fr"); break;
      case -1: // fallthrough
      case 1: LoadTraduction(ResourcePath() + "/lang/lang_en"); break;
      case 2: LoadTraduction(ResourcePath() + "/lang/lang_de"); break;
    }
    // clang-format on
  }

 private:
  Activity* activity_;
  smk::Window window_;

  ResourceLoadingScreen resource_loading_screen_;
  WelcomeScreen welcome_screen_;
  MainScreen main_screen_;
  IntroScreen intro_screen_;
  std::unique_ptr<LevelScreen> level_screen_;
  std::unique_ptr<LevelScreen> to_be_removed_screen_;

  int level_index_ = 0;
  std::string player_name_;

  SaveManager savFile;
  SaveManager langFile;
};

void MainLoop() {
  static std::unique_ptr<Main> main;

  if (!main)
    main = std::make_unique<Main>();

  if (main)
    main->Loop();
}

int main() {
  smk::Audio audio;
  std::locale::global(std::locale("C.UTF-8"));

#ifdef __EMSCRIPTEN__
  // clang-format off
  EM_ASM(
      FS.mkdir('/sav');
      FS.mount(IDBFS, {}, '/sav');
      FS.syncfs(true, function(err){console.log("IndexDB synced", err)});
  , 0);
  // clang-format on
#endif

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(&MainLoop, 0, 1);
#else
  while (1)
    MainLoop();
#endif
  return EXIT_SUCCESS;
}
