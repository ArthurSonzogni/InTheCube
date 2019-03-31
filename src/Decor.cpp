#include "Decor.hpp"
#include "Resource.hpp"
#include <smk/Screen.hpp>

Decor::Decor(int X, int Y, int IMG) {
  sprite.SetPosition(X, Y);
  switch (IMG) {
    // clang-format off
    case 0: sprite.SetTexture(img_decorLampe); break;
    case 1: sprite.SetTexture(img_decorSpace); break;
    case 2: sprite.SetTexture(img_decorDirectionnelles); break;
    case 3: sprite.SetTexture(img_decorPilier); break;
    case 4: sprite.SetTexture(img_decorPlateforme6432); break;
    case 5: sprite.SetTexture(img_decorPlateforme9632); break;
    case 6: sprite.SetTexture(img_decorGlass); break;	
    case 7: sprite.SetTexture(img_decorSupport); break;
    case 8: sprite.SetTexture(img_pipe); sprite.SetCenter(3,0); break;
    case 9: sprite.SetTexture(img_pipe); sprite.SetCenter(35,96); sprite.SetRotation(180); break;
    case 10: sprite.SetTexture(img_oeil); break;
    case 11: sprite.SetTexture(img_ouvertureEffect); break;
    case 12: sprite.SetTexture(img_arbre);break;
    case 13: sprite.SetTexture(img_trou);break;
    case 14: sprite.SetTexture(img_couchetrou);break;
    case 15: sprite.SetTexture(img_arbreDecorsFront);break;
    case 16: sprite.SetTexture(img_arbreDecorsBack);break;
    case 17: sprite.SetTexture(img_decorNoisette);break;
    case 18: sprite.SetTexture(img_arbreDecors2Front);break;
    case 19: sprite.SetTexture(img_arbreDecors2Back);break;
    case 20: sprite.SetTexture(img_arbreDecors3Front);break;
    case 21: sprite.SetTexture(img_arbreDecors4Back);break;
    case 22: sprite.SetTexture(img_arbreDecors4Front);break;
    case 23: sprite.SetTexture(img_arbreDecorsBossFront);break;
    case 24: sprite.SetTexture(img_arbreDecors5Front);break;
    case 25: sprite.SetTexture(img_tuyau); sprite.SetScale(1.05,0);break;
    case 26: sprite.SetTexture(img_arbreDecors6Front); break;
    case 27: sprite.SetTexture(img_arbreDecors2Back); sprite.SetScaleY(-1); break;
    case 28: sprite.SetTexture(img_arbreDecorsEndFront);break;
    case 29: sprite.SetTexture(img_arbreDecorsEndBack1);break;
    case 30: sprite.SetTexture(img_arbreDecorsEndBack2);break;
    // clang-format on
  }
}

void Decor::Draw(smk::Screen& screen) {
  screen.Draw(sprite);
}
