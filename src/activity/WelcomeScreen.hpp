#ifndef WELCOME_SCREEN_HPP
#define WELCOME_SCREEN_HPP

#include "activity/Activity.hpp"

class WelcomeScreen : public Activity {
 public:
  WelcomeScreen(smk::Screen& screen) : Activity(screen) {}
  void Draw() override;
  void OnEnter() override;

  std::function<void()> on_quit = [] {};

 private:
  float time_start = 0.f;
};

#endif /* end of include guard: WELCOME_SCREEN_HPP */
