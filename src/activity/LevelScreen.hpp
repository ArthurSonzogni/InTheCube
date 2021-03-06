// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef LEVEL_WINDOW_HPP
#define LEVEL_WINDOW_HPP

#include <memory>

#include "activity/Activity.hpp"
#include "game/Level.hpp"
#include "game/SaveManager.hpp"

class LevelScreen : public Activity {
 public:
  LevelScreen(smk::Window& window, std::string level);
  ~LevelScreen() override = default;

  void Draw() override;

  std::function<void()> on_restart = [] {};
  std::function<void()> on_previous = [] {};
  std::function<void()> on_win = [] {};
  std::function<void()> on_quit = [] {};

 private:
  Level level_;
  float start_time = 0.f;
  int frame = 0;

  bool cursor_in = false;
  glm::vec2 cursor_reference;
  int previous_input = 0;
};

#endif /* end of include guard: LEVEL_window_HPP */
