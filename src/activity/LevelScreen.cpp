#include "activity/LevelScreen.hpp"
#include <smk/Color.hpp>
#include <thread>
#include <chrono>

LevelScreen::LevelScreen(smk::Screen& screen, std::string level_name)
    : Activity(screen) {
  level_.LoadFromFile(level_name);
  frame = 0;
  start_time = screen.time();
};

void LevelScreen::Draw() {
  float new_time = screen().time();
  int new_frame = (new_time - start_time) * 30;

  if (new_frame > frame + 10) {
    std::cerr << "Skip " << new_frame - frame << " frames" << std::endl;
    frame = 0;
    new_frame = 1;
    start_time = new_time;
  }

  static float sleep_duration = 1000000 / 60;
  static float fail_ratio = 0.1;
  if (frame == new_frame) {
    sleep_duration *= 1.01;
    std::cerr << "Bad" << std::endl;
  } else {
    sleep_duration *= 0.9999;
  }
  std::this_thread::sleep_for(std::chrono::microseconds(int(sleep_duration)));

  // Start the BackgroundMusic
  // backMusic.Start();
  bool event_are_dirty = false;

  for (; frame < new_frame; ++frame) {
    screen().PoolEvents();
    level_.Step(screen());
  }

  //std::cerr << "Drawing frame " << frame << std::endl;
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

  if (level_.isEscape) {
    on_quit();
    return;
  }
}
