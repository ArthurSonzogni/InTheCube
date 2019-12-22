#include "Pincette.hpp"
#include <smk/Window.hpp>

Pincette::Pincette() {
  step_ = 0;
  pincetteSprite.SetTexture(img_pincette);
  heroSprite.SetTexture(img_hero_left);
  heroSprite.SetScale(0.85, 1);
}

void Pincette::Step() {
  pincetteSprite.SetPosition(128, -128);
  heroSprite.SetPosition(128 + 4, -128 + 304 - 24);

  // Bezier interpolation.
  // clang-format off
  int xpos[] = {128  , 128 + 50  , 128       , 128 - 50   , 128        , 128 + 50   , 128        , 128 - 50   , 128        , 128 - 50   , 128       , 128 + 50  , 128};
  int ypos[] = {-128 , -128 + 40 , -128 + 80 , -128 + 120 , -128 + 160 , -128 + 200 , -128 + 240 , -128 + 240 , -128 + 200 , -128 + 100 , -128 - 30 , -128 - 50 , -128 - 100};

  float t = float(step_ % 60) / 60.0;
  int pos = 2 * (step_ / 60);

  float dx = (1 - t) * (1 - t) * xpos [pos] +
             2 * t * (1 - t)   * xpos [pos + 1] +
             t * t             * xpos [pos + 2];
  float dy = (1 - t) * (1 - t) * ypos [pos] +
             2 * t * (1 - t)   * ypos [pos + 1] +
             t * t             * ypos [pos + 2];

  pincetteSprite.Move(dx,dy);
  heroSprite.Move(dx,dy);

  // clang-format on

  if (step_ > 60 * 3)
    heroSprite.Move(0, (step_ - 60 * 3) * (step_ - 60 * 3) / 5.0);
  step_++;
}

void Pincette::Draw(smk::Window& window) {
  window.Draw(pincetteSprite);
  window.Draw(heroSprite);
}
