#include "activity/LevelScreen.hpp"
#include <smk/Color.hpp>
LevelScreen::LevelScreen(smk::Window& window, std::string level_name)
    : Activity(window) {
  level_.LoadFromFile(level_name);
  frame = 0;
  start_time = window.time();
}

void LevelScreen::Draw() {
  float new_time = window().time();
  int new_frame = (new_time - start_time) * 30;

  if (new_frame > frame + 10) {
    std::cerr << "Skip " << new_frame - frame << " frames" << std::endl;
    frame = 0;
    new_frame = 1;
    start_time = new_time;
  }

  for (; frame < new_frame; ++frame) {
    window().PoolEvents();
    level_.Step(window());
  }

  window().Clear(glm::vec4(0.f, 0.f, 0.f, 0.f));
  level_.Draw(window());
  window().Display();

  if (level_.isLose) {
    on_restart();
    return;
  }

  if (level_.isWin) {
    on_win();
    return;
  }

  if (level_.isPrevious) {
    on_previous();
    return;
  }

  if (level_.isEscape) {
    on_quit();
    return;
  }
}
