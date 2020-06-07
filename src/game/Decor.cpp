// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Decor.hpp"

#include <iostream>
#include <smk/Window.hpp>

#include "game/Resource.hpp"

Decor::Decor(int X, int Y, int IMG) {
  switch (IMG) {
    // clang-format off
    case 0: sprite = smk::Sprite(img_decorLampe); break;
    case 1: sprite = smk::Sprite(img_decorSpace); break;
    case 2: sprite = smk::Sprite(img_decorDirectionnelles); break;
    case 3: sprite = smk::Sprite(img_decorPilier); break;
    case 4: sprite = smk::Sprite(img_decorPlateforme6432); break;
    case 5: sprite = smk::Sprite(img_decorPlateforme9632); break;
    case 6: sprite = smk::Sprite(img_decorGlass); break;	
    case 7: sprite = smk::Sprite(img_decorSupport); break;
    case 8: sprite = smk::Sprite(img_pipe); sprite.SetCenter(3,0); break;
    case 9: sprite = smk::Sprite(img_pipe); sprite.SetCenter(35,96); sprite.SetRotation(180); break;
    case 10: sprite = smk::Sprite(img_oeil); break;
    case 11: sprite = smk::Sprite(img_ouvertureEffect); break;
    case 12: sprite = smk::Sprite(img_arbre);break;
    case 13: sprite = smk::Sprite(img_trou);break;
    case 14: sprite = smk::Sprite(img_couchetrou);break;
    case 15: sprite = smk::Sprite(img_arbreDecorsFront);break;
    case 16: sprite = smk::Sprite(img_arbreDecorsBack);break;
    case 17: sprite = smk::Sprite(img_decorNoisette);break;
    case 18: sprite = smk::Sprite(img_arbreDecors2Front);break;
    case 19: sprite = smk::Sprite(img_arbreDecors2Back);break;
    case 20: sprite = smk::Sprite(img_arbreDecors3Front);break;
    case 21: sprite = smk::Sprite(img_arbreDecors4Back);break;
    case 22: sprite = smk::Sprite(img_arbreDecors4Front);break;
    case 23: sprite = smk::Sprite(img_arbreDecorsBossFront);break;
    case 24: sprite = smk::Sprite(img_arbreDecors5Front);break;
    case 25: sprite = smk::Sprite(img_tuyau); sprite.SetScale(1.05,0);break;
    case 26: sprite = smk::Sprite(img_arbreDecors6Front); break;
    case 27: sprite = smk::Sprite(img_arbreDecors2Back); sprite.SetScaleY(-1); break;
    case 28: sprite = smk::Sprite(img_arbreDecorsEndFront);break;
    case 29: sprite = smk::Sprite(img_arbreDecorsEndBack1);break;
    case 30: sprite = smk::Sprite(img_arbreDecorsEndBack2);break;
      // clang-format on
  }
  sprite.SetPosition(X, Y);
}

void Decor::Draw(smk::Window& window) {
  window.Draw(sprite);
}
