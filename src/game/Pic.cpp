#include "game/Pic.hpp"
#include <smk/Window.hpp>
#include "game/Resource.hpp"

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
  sprite = smk::Sprite(img_pic);
  sprite.SetCenter(0, 8);
  sprite.SetRotation(angle);
}

void Pic::Draw(smk::Window& window) {
  sprite.SetPosition(x + avancement * cos(angle * 0.0174532925),
                     y - avancement * sin(angle * 0.0174532925));
  window.Draw(sprite);
}
