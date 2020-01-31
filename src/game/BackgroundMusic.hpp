#ifndef GAME_BACKGROUND_MUSIC_HPP
#define GAME_BACKGROUND_MUSIC_HPP

#include <string>

#include <smk/Sound.hpp>
#include <smk/SoundBuffer.hpp>
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
