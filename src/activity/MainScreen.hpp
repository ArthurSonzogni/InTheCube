#ifndef MAINwindow_HPP
#define MAINwindow_HPP

#include "activity/Activity.hpp"
#include "game/SaveManager.hpp"
#include <functional>
#include <memory>

class MainScreen : public Activity {
 public:
  MainScreen(smk::Window& window, SaveManager& save_file)
      : Activity(window), save_file_(save_file) {}
  ~MainScreen() override = default;

  void Draw() override;
  void OnEnter() override;

  std::function<void()> on_quit = [] {};
  std::function<void(int)> on_update_traduction = [](int) {};
  std::function<void(std::string)> on_name_selected = [](std::string) {};

 private:
  float languageXPos[3] = {640, 640, 640};
  SaveManager& save_file_;
  std::string GetName();

  float previous_time = 0.f;

  class Question {
   public:
    Question(smk::Window& window);
    std::wstring question;
    std::wstring yes;
    std::wstring no;
    std::function<void()> on_yes = [] {};
    std::function<void()> on_no = [] {};

    bool Draw(smk::Window& window);
    float alpha = 0.f;

   private:
    float time_ = -1;
    bool exiting_ = false;
  };

  class GetString {
   public:
    GetString(smk::Window&);
    ~GetString();
    std::wstring message;
    std::function<void(std::string)> on_enter = [](std::string) {};

    bool Draw(smk::Window& window);
    float alpha = 0.f;

   private:
    std::string typed_text_;
    float time_ = -1;
    bool exiting_ = false;
    smk::Window& window_;
  };

  std::unique_ptr<Question> question_;
  std::unique_ptr<GetString> get_string_;
};

#endif /* end of include guard: MAINwindow_HPP */
