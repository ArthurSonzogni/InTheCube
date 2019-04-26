#include "activity/LevelScreen.hpp"
#include <smk/Color.hpp>
LevelScreen::LevelScreen(smk::Screen& screen, std::string level_name)
    : Activity(screen) {
  level_.LoadFromFile(level_name);
  frame = 0;
  start_time = screen.time();
}

void LevelScreen::Draw() {
  float new_time = screen().time();
  int new_frame = (new_time - start_time) * 30;

  if (new_frame > frame + 10) {
    std::cerr << "Skip " << new_frame - frame << " frames" << std::endl;
    frame = 0;
    new_frame = 1;
    start_time = new_time;
  }

  for (; frame < new_frame; ++frame) {
    screen().PoolEvents();
    level_.Step(screen());
  }

  screen().Clear(glm::vec4(0.f, 0.f, 0.f, 0.f));
  level_.Draw(screen());
  screen().Display();

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
