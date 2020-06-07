// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_BACKGROUND_MUSIC_HPP
#define GAME_BACKGROUND_MUSIC_HPP

#include <smk/Sound.hpp>
#include <smk/SoundBuffer.hpp>
#include <string>

#include "game/Resource.hpp"

class BackgroundMusic {
 public:
  void Start();
  void SetSound(const smk::SoundBuffer& buffer);
  void Step();

 private:
  const smk::SoundBuffer* foreground_sound_buffer_;
  smk::Sound foreground_sound_;
  smk::Sound background_sound_;

  float time_ = 1.f;
};

#endif /* GAME_BACKGROUND_MUSIC_HPP */
