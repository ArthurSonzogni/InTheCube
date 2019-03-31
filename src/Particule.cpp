#include "Particule.hpp"
#include <smk/Screen.hpp>
#include <cstdlib>
#include <cmath>

Particule::Particule(bool (*stepF)(Particule*)) {
  transform = stepF;
}

bool Particule::Step() {
  return transform(this);
}

void Particule::Draw(smk::Screen& screen) {
  screen.Draw(sprite);
}

Particule essai() {
  Particule p(essaiStep);
  p.sprite.SetTexture(img_particule_smoothRound);
  p.sprite.SetCenter(16, 16);
  p.sprite.SetPosition(200, 200);
  p.xspeed = rand() % 11 - 5;
  p.yspeed = rand() % 11 - 5;
  p.sprite.SetBlendMode(Blend::Add);
  p.t = 0;
  p.alpha = 255;
  return p;
}

bool essaiStep(Particule* p) {
  p->sprite.Move(p->xspeed, p->yspeed);
  p->sprite.Rotate(1 + rand() % 3);
  p->alpha *= 0.95;
  p->sprite.SetColor(glm::vec4(255, p->alpha, p->alpha / 2, p->alpha) / 255.f);
  p->xspeed += p->yspeed / 200;
  p->yspeed -= p->xspeed / 200;
  p->xspeed *= 0.7;
  p->yspeed -= 0.3;
  p->t++;
  return (p->t > 90);
}

// fire
Particule fireParticule(int x, int y) {
  Particule p(fireParticuleStep);
  p.sprite.SetTexture(img_particule_fire);
  p.sprite.SetCenter(8, 8);
  p.sprite.SetScale(2, 2);
  p.sprite.SetPosition(x, y);
  p.xspeed = rand() % 6 - 2;
  p.yspeed = rand() % 6 - 2;
  p.sprite.SetBlendMode(Blend::Add);
  p.t = 0;
  p.alpha = 255;
  return p;
}

bool fireParticuleStep(Particule* p) {
  p->sprite.Move(p->xspeed, p->yspeed);
  p->sprite.Rotate(1 + rand() % 3);
  p->alpha *= 0.9;
  p->sprite.SetColor(glm::vec4(255, p->alpha, p->alpha / 2, p->alpha) / 255.f);
  p->xspeed += p->yspeed / 200;
  p->yspeed -= p->xspeed / 200;
  p->xspeed *= 0.3;
  p->yspeed -= 0.1;
  p->t++;
  return (p->t > 90);
}

float square(float x) {
  return x * x;
}

Particule particuleLaserOnHero(int x, int y, int xstart, int ystart) {
  Particule p(particuleLaserOnHeroStep);
  p.sprite.SetTexture(img_particule_etincelles);
  p.sprite.SetCenter(3, 3);
  p.sprite.SetPosition(x, y);

  float normalisation = std::sqrt(square(x - xstart) + square(y - ystart)) / 5;
  p.xspeed = (xstart - x) / normalisation;
  p.yspeed = (ystart - y) / normalisation;

  p.xspeed += rand() % 4 - 1;
  p.yspeed += rand() % 4 - 1;
  p.sprite.SetBlendMode(Blend::Add);
  p.t = 0;
  p.alpha = 255;
  return p;
}
bool particuleLaserOnHeroStep(Particule* p) {
  p->sprite.Move(p->xspeed, p->yspeed);
  p->sprite.SetRotation(atan2(-p->yspeed, p->xspeed) * 57 - 90);
  p->alpha *= 0.9;
  p->sprite.SetColor(glm::vec4(200, 100, 10, p->alpha) / 255.f);
  p->yspeed += 0.2;
  p->t++;
  return (p->t > 60);
}

Particule particuleLaserOnGlass(int x, int y, int xstart, int ystart) {
  Particule p(particuleLaserOnGlassStep);
  p.sprite.SetTexture(img_particule_etincelles);
  p.sprite.SetCenter(3, 3);
  p.sprite.SetPosition(x, y);
  p.sprite.SetScale(2, 2);

  float normalisation = sqrt(square(x - xstart) + square(y - ystart)) / 3;
  p.xspeed = (xstart - x) / normalisation;
  p.yspeed = (ystart - y) / normalisation;

  p.xspeed += rand() % 3 - 1;
  p.yspeed += rand() % 3 - 1;
  p.sprite.SetBlendMode(Blend::Add);
  p.t = 0;
  p.alpha = 200;
  p.Step();
  return p;
}
bool particuleLaserOnGlassStep(Particule* p) {
  p->sprite.Move(p->xspeed, p->yspeed);
  p->sprite.SetRotation(atan2(-p->yspeed, p->xspeed) * 57 - 90);
  p->alpha *= 0.8;
  p->sprite.SetColor(glm::vec4(40, 80, 255, p->alpha)/255.f);
  p->yspeed += 0.2;
  p->xspeed *= 0.8;
  p->t++;
  return (p->t > 20);
}

Particule particuleCloneur(int x, int y) {
  Particule p(particuleCloneurStep);
  p.sprite.SetTexture(img_particule_etincelles);
  p.sprite.SetCenter(3, 3);
  p.sprite.SetPosition(x, y - 9);
  p.sprite.SetScale(2, 2);

  p.xspeed = 0;
  p.yspeed = -2;

  p.sprite.SetBlendMode(Blend::Add);
  p.t = 0;
  p.alpha = 200;
  p.Step();
  return p;
}

bool particuleCloneurStep(Particule* p) {
  p->sprite.Move(p->xspeed, p->yspeed);
  p->sprite.SetRotation(atan2(-p->yspeed, p->xspeed) * 57 - 90);
  p->alpha *= 0.8;
  p->sprite.SetColor(glm::vec4(40, 80, 255, p->alpha) / 255.f);
  p->t++;
  return (p->t > 20);
}

Particule particuleCreeperExplosion(int x, int y) {
  Particule p(particuleCreeperExplosionStep);
  p.sprite.SetTexture(img_particule_explosion);
  p.sprite.SetCenter(16, 16);
  p.sprite.SetScale(2, 2);
  p.sprite.SetPosition(x, y + 5);

  p.xspeed = float((rand() % 10 - 5));
  p.yspeed = float((rand() % 10 - 5));
  ;

  p.sprite.SetBlendMode(Blend::Add);
  p.t = 0;
  p.alpha = 200;
  p.Step();
  return p;
}
bool particuleCreeperExplosionStep(Particule* p) {
  p->xspeed *= 0.9;
  p->yspeed *= 0.9;

  p->sprite.Move(p->xspeed, p->yspeed);
  p->sprite.SetRotation(p->t);
  p->alpha *= 0.95;
  p->sprite.SetColor(glm::vec4(255, p->alpha, p->alpha / 2, p->alpha) / 255.f);
  p->t++;
  return (p->alpha < 0.1);
}

// arrowTrace
Particule particuleArrow(int x, int y) {
  Particule p(particuleArrowStep);
  p.sprite.SetCenter(3, 3);
  p.sprite.SetTexture(img_particule_arrow);
  p.sprite.SetPosition(x, y);
  p.alpha = 100;
  p.xspeed = float((rand() % 10 - 5)) / 3.0;
  p.yspeed = float((rand() % 10 - 5)) / 3.0;
  p.x = x;
  p.y = y;

  return p;
}
bool particuleArrowStep(Particule* p) {
  p->x += p->xspeed;
  p->y += p->yspeed;
  p->alpha -= 10;
  p->sprite.SetPosition(p->x, p->y);
  p->sprite.SetColor(glm::vec4(155, 155, 155, p->alpha) / 255.f);
  p->sprite.Rotate(10);
  return (p->alpha < 10);
}

// deadParticule
Particule particuleDead(int x, int y) {
  Particule p(particuleDeadStep);
  p.sprite.SetTexture(img_hero_left);
  p.sprite.SetPosition(x, y);
  p.alpha = 255;
  p.xspeed = 0;
  p.yspeed = -4;
  p.x = x;
  p.y = y;

  return p;
}
bool particuleDeadStep(Particule* p) {
  p->xspeed = 2 * sin(p->alpha / 20);
  p->x += p->xspeed;
  p->y += p->yspeed;
  p->alpha -= 7;
  p->sprite.SetPosition(p->x, p->y);
  p->sprite.SetColor(glm::vec4(155, 155, 155, p->alpha) / 255.f);
  return (p->alpha < 1);
}

// arbreBossParticule
Particule arbreBossParticule(int x, int y, glm::vec4 c) {
  Particule p(arbreBossParticuleStep);
  p.sprite.SetTexture(img_particule_pixel);
  p.sprite.SetPosition(x, y);
  p.sprite.SetCenter(1, 1);
  p.sprite.SetScale(1, 1);
  p.sprite.SetColor(c);
  p.alpha = 255;
  p.xspeed = 0;
  p.yspeed = 0;
  p.x = x;
  p.y = y;

  return p;
}
bool arbreBossParticuleStep(Particule* p) {
  p->yspeed += float(rand() % 11 - 5) / 25.0 + p->xspeed * 0.002;
  p->xspeed += float(rand() % 11 - 5) / 25.0 - p->yspeed * 0.002;
  p->x += p->xspeed + float(rand() % 11 - 5) / 25.0;
  p->y += p->yspeed + float(rand() % 11 - 5) / 25;
  p->alpha -= rand() % 2;
  p->sprite.SetPosition(p->x, p->y);
  return (p->alpha < 1);
}
// arrowTrace
Particule particuleWind(int x, int y) {
  Particule p(particuleWindStep);
  p.sprite.SetScale(0.3, 5.0);
  p.sprite.SetTexture(img_particule_line);
  p.sprite.SetPosition(x, y);
  p.alpha = 120;
  p.xspeed = float((rand() % 10 - 5)) / 3.0;
  p.yspeed = -12 + float((rand() % 10 - 5)) / 3.0;
  p.x = x;
  p.y = y;
  p.sprite.Rotate(rand() % 11 - 5);
  return p;
}
bool particuleWindStep(Particule* p) {
  p->x += p->xspeed;
  p->y += p->yspeed;
  p->alpha -= 10;
  p->sprite.SetPosition(p->x, p->y);
  p->sprite.SetColor(glm::vec4(155, 155, 155, p->alpha) / 255.f);
  return (p->alpha < 10);
}

// acc
Particule accParticule(int x, int y, float xspeed, int t) {
  Particule p(accParticuleStep);
  p.sprite.SetTexture(img_particule_p);
  p.sprite.SetColor(glm::vec4(255, 255, 255, 50) / 255.f);
  p.sprite.SetCenter(16, 4);
  p.sprite.SetPosition(x, y);
  p.xspeed = xspeed;
  p.yspeed = 0.0;
  p.sprite.SetBlendMode(Blend::Add);
  p.x = x;
  p.y = y;
  p.t = t;
  return p;
}

bool accParticuleStep(Particule* p) {
  p->xspeed += p->yspeed;
  p->yspeed -= p->xspeed / 10.0;
  p->y -= 2.0;
  p->x += p->xspeed;
  p->t--;
  p->sprite.SetPosition(p->x, p->y);
  return (p->t < 1);
}
