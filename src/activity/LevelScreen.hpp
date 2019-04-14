#ifndef LEVEL_SCREEN_HPP
#define LEVEL_SCREEN_HPP

#include "SaveManager.hpp"
#include "activity/Activity.hpp"
#include "Level.hpp"
#include <memory>

class LevelScreen : public Activity {
 public:
  LevelScreen(smk::Screen& screen, std::string level);

  void Draw() override;

  std::function<void()> on_restart = []{};
  std::function<void()> on_win = []{};
  std::function<void()> on_quit = []{};
 private:
  Level level_;
  float start_time = 0.f;
  int frame = 0;
};

#endif /* end of include guard: LEVEL_SCREEN_HPP */
