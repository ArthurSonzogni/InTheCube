#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "SaveManager.hpp"
#include "activity/Activity.hpp"

class MainScreen : public Activity {
 public:
  MainScreen(smk::Screen& screen, SaveManager& save_file)
      : Activity(screen), save_file_(save_file) {}

  void Draw() override;
  void OnEnter() override;

  std::function<void()> on_quit = [] {};
  std::function<void(int)> on_update_traduction = [](int) {};
  std::function<void(std::string)> on_name_selected = [](std::string) {};

 private:
  float languageXPos[3] = {640, 640, 640};
  SaveManager& save_file_;
  bool Question(std::wstring message, std::wstring q1, std::wstring q2);
  void Popup(std::wstring message);
  std::string GetName();

  float previous_time = 0.f;
};

#endif /* end of include guard: MAINSCREEN_H */
