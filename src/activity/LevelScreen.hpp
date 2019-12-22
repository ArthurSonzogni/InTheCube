#ifndef LEVEL_WINDOW_HPP
#define LEVEL_WINDOW_HPP

#include "SaveManager.hpp"
#include "activity/Activity.hpp"
#include "Level.hpp"
#include <memory>

class LevelScreen : public Activity {
 public:
  LevelScreen(smk::Window& window, std::string level);
  ~LevelScreen() override = default;

  void Draw() override;

  std::function<void()> on_restart = []{};
  std::function<void()> on_previous = [] {};
  std::function<void()> on_win = []{};
  std::function<void()> on_quit = []{};
 private:
  Level level_;
  float start_time = 0.f;
  int frame = 0;
};

#endif /* end of include guard: LEVEL_window_HPP */
