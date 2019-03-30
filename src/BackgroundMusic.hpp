#ifndef BACKGROUND_MUSIC_HPP
#define BACKGROUND_MUSIC_HPP

#include <string>

#include "Music.hpp"
#include "Resource.hpp"
#include "Sound.hpp"

class BackgroundMusic {
 public:
  Music sound[2];
  int t;
  int tt;
  int current, next;
  BackgroundMusic();
  void Start();
  void SetLevel(std::string level);
  void Step();
  void ChangeMusic(std::string soundFile, int ttt);
};

#endif /* BACKGROUND_MUSIC_HPP */
