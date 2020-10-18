// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "activity/LevelScreen.hpp"

#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Vibrate.hpp>

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
    auto& input = window().input();
    int game_input = Input::None;
    if (input.IsKeyHold(GLFW_KEY_LEFT) || input.IsKeyHold(GLFW_KEY_A))
      game_input |= Input::Left;
    if (input.IsKeyHold(GLFW_KEY_RIGHT) || input.IsKeyHold(GLFW_KEY_D))
      game_input |= Input::Right;
    if (input.IsKeyHold(GLFW_KEY_UP) || input.IsKeyHold(GLFW_KEY_W))
      game_input |= Input::Up;
    if (input.IsKeyHold(GLFW_KEY_SPACE))
      game_input |= Input::Space;
    if (input.IsKeyPressed(GLFW_KEY_R))
      game_input |= Input::Restart;
    if (input.IsKeyReleased(GLFW_KEY_ESCAPE))
      game_input |= Input::Escape;

    if (input.IsCursorPressed()) {
      cursor_in = true;
      cursor_reference = input.cursor();
    }
    if (input.IsCursorHeld()) {
      auto diff = input.cursor() - cursor_reference;
      float trigger = std::min(window().width(), window().height()) * 0.05f;
      if (glm::length(diff) > trigger) {
        diff /= trigger;
        if (diff.x > +0.5f)
          game_input |= Input::Right;
        if (diff.x < -0.5f)
          game_input |= Input::Left;
        if (diff.y < -0.5f)
          game_input |= Input::Up;
      }
    }
    if (input.IsCursorReleased()) {
      cursor_in = false;
    }
    if (previous_input != game_input)
      smk::Vibrate(10);
    previous_input = game_input;

    level_.Step(Input::T(game_input), window());
  }

  level_.Draw(window());

  // clang-format off
  if (level_.isLose)     return on_restart();
  if (level_.isWin)      return on_win();
  if (level_.isPrevious) return on_previous();
  if (level_.isEscape)   return on_quit();
  // clang-format on
}
