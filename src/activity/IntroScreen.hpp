#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "activity/Activity.hpp"
#include <memory>

class IntroScreen : public Activity {
 public:
  IntroScreen(smk::Window& window) : Activity(window) {}
  ~IntroScreen() override = default;

  void Draw() override;
  void OnEnter() override;

  std::function<void()> on_quit = []{};

 private:
  bool quit_ = false;

  float previous_time = 0.f;

  int position = 0;
  float x = 0;
  float dx = 0;

  int Qxpos = 0;
  float Rxpos = 0;

  int timeDelay = 10;
};

#endif /* end of include guard: INTRO_SCREEN_HPP */
