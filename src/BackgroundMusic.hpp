#ifndef BACKGROUND_MUSIC_HPP
#define BACKGROUND_MUSIC_HPP

#include <string>

#include <smk/Sound.hpp>
#include <smk/SoundBuffer.hpp>
#include "Music.hpp"
#include "Resource.hpp"

class BackgroundMusic {
 public:
  void Start();
  void SetSound(const smk::SoundBuffer& buffer);
  void Step();

 private:
  smk::Sound foreground_sound_;
  smk::Sound background_sound_;

  float time_ = 1.f;
};

#endif /* BACKGROUND_MUSIC_HPP */
