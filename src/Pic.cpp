#include "Pic.hpp"
#include <smk/Screen.hpp>
#include "Resource.hpp"

Pic::Pic(int X,
         int Y,
         int Angle,
         int NbRequis,
         int Comparateur,
         std::vector<int> Connexion) {
  x = X;
  y = Y;
  angle = Angle;
  nbRequis = NbRequis;
  comparateur = Comparateur;
  connexion = Connexion;
  avancement = 0;
  sprite.SetTexture(img_pic);
  sprite.SetCenter(0, 8);
  sprite.SetRotation(angle);
}

void Pic::Draw(smk::Screen& screen) {
  sprite.SetPosition(x + avancement * cos(angle * 0.0174532925),
                     y - avancement * sin(angle * 0.0174532925));
  screen.Draw(sprite);
}
