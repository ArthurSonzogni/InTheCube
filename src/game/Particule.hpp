#ifndef GAME_PARTICULE_HPP
#define GAME_PARTICULE_HPP

#include "game/Hero.hpp"
#include <smk/Sprite.hpp>

class window;

class Particule {
 public:
  smk::Sprite sprite;
  bool (*transform)(Particule*);
  float xspeed, yspeed;
  float x, y;
  float alpha;
  int t;
  Particule(bool (*stepF)(Particule*));
  bool Step();
  void Draw(smk::Window& window);
};

// particules fonctions
Particule essai();
bool essaiStep(Particule* p);

// fire
Particule fireParticule(int x, int y);
bool fireParticuleStep(Particule* p);

// laser on hero Particule
Particule particuleLaserOnHero(int x, int y, int xstart, int ystart);
bool particuleLaserOnHeroStep(Particule* p);

// laser on glass Particule
Particule particuleLaserOnGlass(int x, int y, int xstart, int ystart);
bool particuleLaserOnGlassStep(Particule* p);

// creeper explosion
Particule particuleCreeperExplosion(int x, int y);
bool particuleCreeperExplosionStep(Particule* p);

// cloneur
Particule particuleCloneur(int x, int y);
bool particuleCloneurStep(Particule* p);

// arrowTrace
Particule particuleArrow(int x, int y);
bool particuleArrowStep(Particule* p);

// wind
Particule particuleWind(int x, int y);
bool particuleWindStep(Particule* p);

// deadParticule
Particule particuleDead(int x, int y);
bool particuleDeadStep(Particule* p);

// arbreBossParticule
Particule arbreBossParticule(int x, int y, glm::vec4 c);
bool arbreBossParticuleStep(Particule* p);

// acc
Particule accParticule(int x, int y, float xspeed, int t);
bool accParticuleStep(Particule* p);

float square(float x);

#endif /* GAME_PARTICULE_HPP */
