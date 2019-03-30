#include "BackgroundMusic.hpp"

BackgroundMusic::BackgroundMusic() {
  current = 0;
  next = 1;
  t = 100;
  //sound[0].openFromFile("snd/intro.ogg");
  //sound[1].setLoop(true);
  tt = 100;
}

void BackgroundMusic::Start() {
  //sound[current].play();
  //sound[next].stop();
}

void BackgroundMusic::Step() {
  //if (t < tt) {
    //t += 1;
    //sound[current].setVolume(t * 100 / tt);
    //sound[next].setVolume(100 - t * 100 / tt);
    //if (t >= tt) {
      //sound[next].stop();
    //}
  //}
}

void BackgroundMusic::SetLevel(std::string level) {
  //if (level == "lvl/LevelArbreBoss")
    //changeMusic("snd/actionMusic.ogg", 100);
  //else if (level == "lvl/LevelEnd")
    //changeMusic("snd/end.ogg", 100);
}

void BackgroundMusic::ChangeMusic(std::string soundFile, int ttt) {
  //sound[next].openFromFile(soundFile);
  //sound[next].setLoop(true);
  //sound[next].play();
  //std::swap(current, next);
  //t = 0;
  //tt = ttt;
}
