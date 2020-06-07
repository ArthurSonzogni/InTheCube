// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef WELCOME_WINDOW_HPP
#define WELCOME_WINDOW_HPP

#include "activity/Activity.hpp"

class WelcomeScreen : public Activity {
 public:
  WelcomeScreen(smk::Window& window) : Activity(window) {}
  ~WelcomeScreen() override = default;

  void Draw() override;
  void OnEnter() override;

  std::function<void()> on_quit = [] {};

 private:
  float time_start = 0.f;
};

#endif /* end of include guard: WELCOME_window_HPP */
