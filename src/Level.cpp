#include "Input.hpp"
#include "Lang.hpp"
#include "Level.hpp"
#include "Shape.hpp"
#include "Text.hpp"
#include "View.hpp"
#include <algorithm>

float InRange(float x, float a, float b) {
  if (x < a)
    return a;
  else if (x > b)
    return b;
  else
    return x;
}

inline bool Space(char c) {
  return isspace(c);
}

inline bool NotSpace(char c) {
  return !isspace(c);
}

std::vector<std::string> SplitString(const std::string text) {
  typedef std::string::const_iterator iter;
  std::vector<std::string> ret;
  iter i = text.begin();
  while (i != text.end()) {
    i = std::find_if(i, text.end(), NotSpace);
    iter j = std::find_if(i, text.end(), Space);
    if (i != text.end()) {
      ret.push_back(std::string(i, j));
      i = j;
    }
  }
  return ret;
}

template <class T>
bool FromString(T& t,
                const std::string& s,
                std::ios_base& (*f)(std::ios_base&)) {
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

Level::Level() {
  heroSelected = 0;
  nbHero = 0;
  fluidViewEnable = true;
  time = 0;
  timeDead = 0;
}

void Level::LoadFromFile(std::string fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "Impossible to open the file: " << fileName << std::endl;
    return;
  }

  std::string ligne;
  while (getline(file, ligne)) {
    std::vector<std::string> split = SplitString(ligne);
    // blocks
    if (split[0] == "b") {
      int x, y, width, height;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      block_list.push_back(Block(x, y, width, height));
    }
    // Hero
    else if (split[0] == "h") {
      float x, y;
      FromString<float>(x, split[1], std::dec);
      FromString<float>(y, split[2], std::dec);
      hero_list.push_back(Hero(x, y));
      nbHero++;
    }
    // invisible Block
    else if (split[0] == "i") {
      int x, y, width, height;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      invBlock_list.push_back(InvisibleBlock(x, y, width, height));
    }
    // FallingBlock
    else if (split[0] == "f") {
      int x, y;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      fallBlock_list.push_back(FallingBlock(x, y));
    }
    // MovableBlock
    else if (split[0] == "m") {
      int x, y;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      movableBlock_list.push_back(MovableBlock(x, y));
    }
    // MovingBlock
    else if (split[0] == "mm") {
      int x, y, width, height;
      float xspeed, yspeed;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      FromString<float>(xspeed, split[5], std::dec);
      FromString<float>(yspeed, split[6], std::dec);
      movBlock_list.push_back(MovingBlock(x, y, width, height, xspeed, yspeed));
    }
    // FinishBlock
    else if (split[0] == "e") {
      int x, y, width, height;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      enddingBlock = FinishBlock(x, y, width, height);
    }
    // setting the view
    else if (split[0] == "v") {
      int xmin, xmax, ymin, ymax;
      FromString<int>(xmin, split[1], std::dec);
      FromString<int>(ymin, split[2], std::dec);
      FromString<int>(xmax, split[3], std::dec);
      FromString<int>(ymax, split[4], std::dec);
      viewXMin = xmin;
      viewYMin = ymin;
      viewXMax = xmax;
      viewYMax = ymax;
      //screen.SetView(view);
      //view.SetSize(640, 480);
    }
    // adding LaserTurret
    else if (split[0] == "l") {
      int x, y, angle, xattach, yattach, mode, angleSpeed;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(angle, split[3], std::dec);
      FromString<int>(xattach, split[4], std::dec);
      FromString<int>(yattach, split[5], std::dec);
      FromString<int>(mode, split[6], std::dec);
      FromString<int>(angleSpeed, split[7], std::dec);
      laserTurret_list.push_back(
          LaserTurret(x, y, angle, xattach, yattach, mode, angleSpeed));
    }
    // adding Glass
    else if (split[0] == "g") {
      int x, y;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      glassBlock_list.push_back(Glass(x, y));
    }
    // adding noDrawBlock
    else if (split[0] == "nd") {
      int x, y, width, height;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      block_list.push_back(Block(x, y, width, height, false));
    }
    // adding Teleporter
    else if (split[0] == "t") {
      int x, y, width, height, xTeleport, yTeleport;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      FromString<int>(xTeleport, split[5], std::dec);
      FromString<int>(yTeleport, split[6], std::dec);
      teleporter_list.push_back(
          Teleporter(x, y, width, height, xTeleport, yTeleport));
      fluidViewEnable = false;
    }
    // adding Electricity
    else if (split[0] == "elec") {
      int x1, y1, x2, y2;
      float ratio;
      int periode;
      int offset;
      FromString<int>(x1, split[1], std::dec);
      FromString<int>(y1, split[2], std::dec);
      FromString<int>(x2, split[3], std::dec);
      FromString<int>(y2, split[4], std::dec);
      FromString<float>(ratio, split[5], std::dec);
      FromString<int>(periode, split[6], std::dec);
      FromString<int>(offset, split[7], std::dec);
      electricity_list.push_back(
          Electricity(x1, y1, x2, y2, ratio, periode, offset));
    }
    // adding cloneurs
    else if (split[0] == "clone") {
      int x1, y1, x2, y2;

      FromString<int>(x1, split[1], std::dec);
      FromString<int>(y1, split[2], std::dec);
      FromString<int>(x2, split[3], std::dec);
      FromString<int>(y2, split[4], std::dec);
      cloneur_list.push_back(Cloner(x1, y1, x2, y2));
    }
    // adding Decor back
    else if (split[0] == "d0") {
      int x, y, img;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(img, split[3], std::dec);
      decorBack_list.push_back(Decor(x, y, img));
    }
    // adding Decor front
    else if (split[0] == "d1") {
      int x, y, img;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(img, split[3], std::dec);
      decorFront_list.push_back(Decor(x, y, img));
    }
    // adding static miroir
    else if (split[0] == "staticMirror") {
      int x1, y1, x2, y2, xattach, yattach;
      FromString<int>(x1, split[1], std::dec);
      FromString<int>(y1, split[2], std::dec);
      FromString<int>(x2, split[3], std::dec);
      FromString<int>(y2, split[4], std::dec);
      FromString<int>(xattach, split[5], std::dec);
      FromString<int>(yattach, split[6], std::dec);
      staticMiroir_list.push_back(
          StaticMirror(x1, y1, x2, y2, xattach, yattach));
    }
    // adding creepers
    else if (split[0] == "creeper") {
      int x, y;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      creeper_list.push_back(Creeper(x, y));
    }
    // adding Arrow launcher
    else if (split[0] == "arrowLauncher") {
      float x, y, orientation;
      FromString<float>(x, split[1], std::dec);
      FromString<float>(y, split[2], std::dec);
      FromString<float>(orientation, split[3], std::dec);
      arrowLauncher_list.push_back(ArrowLauncher(x, y, orientation));
      block_list.push_back(Block(x, y, 32, 32, false));
    }
    // adding ArrowLauncherDetector
    else if (split[0] == "arrowLauncherDetector") {
      int x, y, width, height, mode, ID;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      FromString<int>(mode, split[5], std::dec);
      FromString<int>(ID, split[6], std::dec);
      arrowLauncherDetector_list.push_back(
          ArrowLauncherDetector(x, x + width, y, y + height, mode, ID));
    }
    // adding Pincette
    else if (split[0] == "pincette") {
      pincette_list.push_back(Pincette());
    }
    // adding TextPopup
    else if (split[0] == "textPopup") {
      int m;
      FromString<int>(m, split[1], std::dec);
      textpopup_list.push_back(TextPopup(m));
    }
    // adding Special
    else if (split[0] == "special") {
      int m;
      FromString<int>(m, split[1], std::dec);
      special_list.push_back(Special(m));
    }
    // adding Detector
    else if (split[0] == "detector") {
      int x, y, width, height;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      detector_list.push_back(Detector(x, y, x + width, y + height));
    }
    // adding Pic
    else if (split[0] == "pic") {
      int x, y, angle, nbRequis, comparateur;
      std::vector<int> connexion;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(angle, split[3], std::dec);
      FromString<int>(nbRequis, split[4], std::dec);
      FromString<int>(comparateur, split[5], std::dec);
      unsigned int size = split.size();
      for (unsigned int i = 6; i < size; i++) {
        int detectorId;
        FromString<int>(detectorId, split[i], std::dec);
        connexion.push_back(detectorId);
      }
      pic_list.push_back(Pic(x, y, angle, nbRequis, comparateur, connexion));
    }
    // adding Accelerator
    else if (split[0] == "accelerator") {
      int x, y, width, height, xacc, yacc;
      float viscosite;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(width, split[3], std::dec);
      FromString<int>(height, split[4], std::dec);
      FromString<int>(xacc, split[5], std::dec);
      FromString<int>(yacc, split[6], std::dec);
      FromString<float>(viscosite, split[7], std::dec);
      accelerator_list.push_back(
          Accelerator(x, y, x + width, y + height, xacc, yacc, viscosite));
    }
    // adding Button
    else if (split[0] == "button") {
      int x, y, n;
      FromString<int>(x, split[1], std::dec);
      FromString<int>(y, split[2], std::dec);
      FromString<int>(n, split[3], std::dec);
      button_list.push_back(Button(x, y, n));
    }
  }
  file.close();

  // definition du background;
  spriteBackground.SetTexture(img_background);

  // end of Level variables
  isWin = false;
  isEscape = false;
  isLose = false;

  // setting the view
  if (!hero_list.empty()) {
    xcenter = hero_list[heroSelected].geometry.left;
    ycenter = hero_list[heroSelected].geometry.top;
  }
}

glm::vec4 colorNonSelected(200 / 255.f, 200 / 255.f, 100 / 255.f, 1.f);

void Level::Draw(Screen& screen) {
  // set the view
  if (!hero_list.empty()) {
    if (fluidViewEnable) {
      xcenter = (xcenter + 0.1 * hero_list[heroSelected].geometry.left) / 1.1;
      ycenter = (ycenter + 0.1 * hero_list[heroSelected].geometry.top) / 1.1;
    } else {
      xcenter = hero_list[heroSelected].geometry.left;
      ycenter = hero_list[heroSelected].geometry.left;
    }
    if (xcenter < viewXMin + 320)
      xcenter = viewXMin + 320;
    else if (xcenter > viewXMax - 320)
      xcenter = viewXMax - 320;
    if (ycenter < viewYMin + 240)
      ycenter = viewYMin + 240;
    else if (ycenter > viewYMax - 240)
      ycenter = viewYMax - 240;
    view.SetCenter(xcenter, ycenter);
  }

  view.SetSize(640, 480);
  screen.SetView(view);

  // apply the background on the screen;
  bool drawBackGround = true;

  for (std::list<Special>::iterator it = special_list.begin();
       it != special_list.end(); ++it) {
    switch (it->m) {
      case SPECIAL_ARBRE2: {
        drawBackGround = false;
        Sprite spr;
        spr.SetTexture(img_arbre_texture);
        for (int x = xcenter - 320 - int(xcenter / 2.67) % 340;
             x < xcenter + 320; x += 340) {
          for (int y = ycenter - 240 - int(ycenter / 2.67) % 340;
               y < ycenter + 240; y += 340) {
            spr.SetPosition(x, y);
            // screen.Draw(spr);
          }
        }
      } break;
    }
  }

  if (drawBackGround)
    for (int x = xcenter - 320 - int(xcenter / 2.67) % 24; x < xcenter + 320; x += 24) {
      for (int y = ycenter - 240 - int(ycenter / 2.67) % 24; y < ycenter + 240; y += 24) {
        spriteBackground.SetPosition(x, y);
        screen.Draw(spriteBackground);
      }
    }

  for (std::vector<Decor>::iterator it = decorBack_list.begin();
       it != decorBack_list.end(); ++it) {
    (*it).Draw(screen);
  }

  // Special

  for (std::list<Special>::iterator it = special_list.begin();
       it != special_list.end(); ++it) {
    switch (it->m) {
      case SPECIAL_END: {
        int t = it->var[0];
        Sprite spr;
        spr.SetTexture(img_arbreDecorsEndBack2);
        spr.SetColor(glm::vec4(1.0, 1.0, 1.0, t / 255.f));
        screen.Draw(spr);
      } break;
    }
  }

  // Draw static turrets and throw out Laser
  for (std::vector<LaserTurret>::iterator it = laserTurret_list.begin();
       it != laserTurret_list.end(); ++it) {
    (*it).Draw(screen);
    Laser(screen, (*it).x, (*it).y, (*it).angle, 10);
    (*it).UpdateAngle();
  }

  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    (*it).Draw(screen);
  }
  if (!hero_list.empty())
    for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
         it != invBlock_list.end(); ++it) {
      (*it).Draw(screen, hero_list[heroSelected]);
    }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    (*it).Draw(screen);
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    (*it).Draw(screen);
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    (*it).Draw(screen);
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    (*it).Draw(screen);
  }
  for (std::vector<StaticMirror>::iterator it = staticMiroir_list.begin();
       it != staticMiroir_list.end(); ++it) {
    (*it).Draw(screen);
  }

  // Pic
  for (std::vector<Pic>::iterator it = pic_list.begin(); it != pic_list.end();
       ++it) {
    it->sprite.SetPosition(
        it->x + it->avancement * cos(it->angle * 0.0174532925),
        it->y - it->avancement * sin(it->angle * 0.0174532925));
    screen.Draw(it->sprite);
  }

  // Special
  for (std::list<Special>::iterator it = special_list.begin();
       it != special_list.end(); ++it) {
    switch (it->m) {
      case SPECIAL_ARBREBOSS: {
        float timesalvo = it->var[0];
        // Draw the sapin
        Sprite spr;
        spr.SetTexture(img_sapin);
        spr.SetPosition(520, 303);
        spr.Move(-3 * sin(timesalvo / 100.0 * 3.14), 0);
        screen.Draw(spr);

        float angle1 = 270 - 180 * sin(timesalvo / 100.0 * (3.14));
        float angle2 = angle1 * angle1 / 300;

        // Draw the sapin_arm
        spr.SetTexture(img_sapin_bras);
        spr.SetCenter(10, 9);

        spr.SetPosition(520 + 45, 303 + 86);
        spr.SetRotation(angle1);
        screen.Draw(spr);

        spr.Move(30 * cos(angle1 * 0.0174532925),
                 -30 * sin(angle1 * 0.0174532925));
        spr.SetRotation(angle2);
        screen.Draw(spr);

      } break;
      case SPECIAL_END2: {
        int& t = it->var[0];
        int& pos = it->var[1];
        int& mode = it->var[2];
        int& pos2 = it->var[3];
        int& alpha = it->var[4];
        int& color = it->var[5];

        if (t > 254) {
          switch (mode) {
            case 0:
              pos += (400.0 - pos) / 30.0;
              if ((400 - pos) < 30) {
                if (Input::IsKeyHold(GLFW_KEY_SPACE)) {
                  mode = 1;
                }
              }
              break;
            case 1:
              pos2 += (640 - pos2) / 30.0;
              if (640 - pos2 < 30) {
                mode = 2;
              }
              break;
            case 2:
              if (alpha < 255)
                alpha += 5;
              else {
                alpha = 255;
                mode = 3;
              }
              break;
            case 3:
              if (color < 255) {
                color += 2;
              } else {
                if (Input::IsKeyHold(GLFW_KEY_SPACE))
                  isWin = true;
                color = 255;
              }
          }
        } else {
          t++;
        }

        // focus
        Shape rect =
            Shape::Rectangle(0, 0, 6400, 4800, glm::vec4(0, 0, 0, t / 2 / 255));
        screen.Draw(rect);

        // tree
        Sprite spr;
        spr.SetPosition(700, 348);
        spr.SetTexture(img_arbre);
        screen.Draw(spr);

        spr.SetTexture(img_arbre_white);
        spr.SetBlendMode(Blend::Add);
        spr.SetColor(glm::vec4(1.0, 1.0, 1.0, t / 255));
        screen.Draw(spr);

        if (pos > 0) {
          Sprite spr;
          spr.SetTexture(img_endPanel);
          spr.SetPosition(960 - 640 - 360 + pos, 0 + pos2);
          screen.Draw(spr);

          Text str[7];
          str[0].SetString(tr(L"end1"));
          str[1].SetString(tr(L"end2"));
          str[2].SetString(tr(L"end3"));
          str[3].SetString(tr(L"end4"));
          str[4].SetString(tr(L"end5"));
          str[5].SetString(tr(L"end6"));
          str[6].SetString(tr(L"end7"));

          str[0].SetPosition(-15 + pos, 30 + pos2);
          str[1].SetPosition(-15 + pos, 60 + pos2);
          str[2].SetPosition(-15 + pos, 90 + pos2);
          str[3].SetPosition(-15 + pos, 150 + pos2);
          str[4].SetPosition(-15 + pos, 180 + pos2);
          str[5].SetPosition(-15 + pos, 240 + pos2);
          str[6].SetPosition(-15 + pos, 270 + pos2);

          for (int i = 0; i < 7; i++) {
            str[i].SetFont(font_arial);
            str[i].SetColor(glm::vec4(0.0, 0.0, 0.0, 0.0));
            screen.Draw(str[i]);
            str[i].Move(0, 1);
            str[i].SetColor(glm::vec4(60, 60, 60, 255) / 255.f);
            screen.Draw(str[i]);
          }

          Sprite sprCredit;
          sprCredit.SetTexture(img_credit);
          sprCredit.SetPosition(960 - 640, 0);
          sprCredit.SetColor(glm::vec4(color, color, color, alpha) / 255.f);
          screen.Draw(sprCredit);
        }

      } break;
    }
  }

  // Button
  for (std::list<Button>::iterator it = button_list.begin();
       it != button_list.end(); ++it) {
    Sprite spr;
    spr.SetTexture(img_button[it->nb_pressed]);
    spr.SetCenter(8, 8);
    spr.SetPosition(it->geometry.left + 8, it->geometry.top + 8);
    screen.Draw(spr);
  }

  int i = 0;
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (heroSelected != i)
      (*it).sprite.SetColor(colorNonSelected);
    else
      (*it).sprite.SetColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    (*it).Draw(screen);
    i++;
  }

  // Creeper
  for (std::vector<Creeper>::iterator it = creeper_list.begin();
       it != creeper_list.end(); ++it) {
    (*it).Draw(screen);
  }

  // Arrow
  for (std::list<Arrow>::iterator it = arrow_list.begin();
       it != arrow_list.end(); ++it) {
    (*it).Draw(screen);
  }

  // ArrowLauncher
  for (std::vector<ArrowLauncher>::iterator it = arrowLauncher_list.begin();
       it != arrowLauncher_list.end(); ++it) {
    (*it).Draw(screen);
  }

  for (std::vector<Cloner>::iterator it = cloneur_list.begin();
       it != cloneur_list.end(); ++it) {
    (*it).Draw(screen);
    // emit some particules
    if ((*it).enable)
      for (int a = 0; a <= 5; a++) {
        particule_list.push_front(
            particuleCloneur((*it).xstart + rand() % 32, (*it).ystart + 32));
      }
  }

  // Draw particules
  for (std::list<Particule>::iterator it = particule_list.begin();
       it != particule_list.end(); ++it) {
    (*it).Draw(screen);
  }

  // Draw Electricity
  for (std::vector<Electricity>::iterator it = electricity_list.begin();
       it != electricity_list.end(); ++it) {
    int x1 = ((*it).x1);
    int x2 = ((*it).x2);
    int y1 = ((*it).y1);
    int y2 = ((*it).y2);
    Sprite sprite;
    sprite.SetTexture(img_electricitySupport);
    sprite.SetPosition(x1 - 8, y1 - 8);
    screen.Draw(sprite);
    sprite.SetPosition(x2 - 8, y2 - 8);
    screen.Draw(sprite);

    /*
    if (time==100)
    {
            cout<<time<<std::endl;
            cout<<(*it).offset<<std::endl;
            cout<<(*it).periode<<std::endl;
            cout<<(*it).ratio<<std::endl;
            cout<<std::endl;
    }*/

    if (((time + (*it).offset) % ((*it).periode)) <
        (*it).ratio * (*it).periode) {
      if (!(*it).isSound) {
        (*it).sound.Play();
        (*it).isSound = true;
      }
      // collision with an Hero

      int i = 0;
      for (std::vector<Hero>::iterator it = hero_list.begin();
           it != hero_list.end(); ++it) {
        if (IsCollision((*it).geometry.increase(10, 10),
                        Line(x1, y1, x2, y2))) {
          (*it).life -= 4;
        }
        i++;
      }
      DrawElectricity(screen, x1, y1, x2, y2);
      DrawElectricity(screen, x1, y1, x2, y2);
      DrawElectricity(screen, x1, y1, x2, y2);
    } else {
      if ((*it).isSound) {
        (*it).sound.Stop();
        (*it).isSound = false;
      }
    }
  }

  for (auto& pincette : pincette_list)
    pincette.Draw(screen);

  // front decors
  for (std::vector<Decor>::iterator it = decorFront_list.begin();
       it != decorFront_list.end(); ++it) {
    (*it).Draw(screen);
  }

  // drawing life bar
  Sprite Coeur;
  Coeur.SetTexture(img_coeur);
  if (!hero_list.empty()) {
    int nbCoeur = hero_list[heroSelected].life;
    for (int i = 1; i <= nbCoeur; i++) {
      Coeur.SetPosition(xcenter + i * 16 - 320, ycenter + 220);
      screen.Draw(Coeur);
    }
  }

  // Draw popup
  for (std::list<TextPopup>::iterator it = textpopup_list.begin();
       it != textpopup_list.end(); ++it) {
    for (std::vector<Hero>::iterator ithero = hero_list.begin();
         ithero != hero_list.end(); ++ithero) {
      if (IsCollision(it->geometry, ithero->geometry)) {
        it->Draw(screen);
        it = textpopup_list.erase(it);
        it = textpopup_list.begin();
      }
    }
  }
}

void Level::Step(Screen& screen) {
  // flush event;
  // Event ev;
  // while (screen.GetEvent(ev)) {
  // if (ev.Type == sf::Event::Closed)
  // isEscape = true;
  //}

  /////////////////////////////////
  //        extra key            //
  /////////////////////////////////

  // test if the player will end the game
  // if (screen.GetInput().IsKeyDown(Key::Escape)) {
  // isEscape = true;
  //}
  // test if the player will restart the room
  if (Input::IsKeyPressed(GLFW_KEY_R)) {
    isLose = true;
  }
  if (Input::IsKeyPressed(GLFW_KEY_T)) {
    isWin = true;
  }

  //////////////////////////////////
  //           testing tools      //
  //////////////////////////////////

  time++;
  /////////////////////////////////
  //        Hero  selected       //
  /////////////////////////////////

  // changement de joueur
  static bool spacepressed = false;
  if (!hero_list.empty()) {
    if (Input::IsKeyHold(GLFW_KEY_SPACE)) {
      if (spacepressed == false) {
        spacepressed = true;
        heroSelected = (heroSelected + 1) % nbHero;
      }
    } else
      spacepressed = false;
  }

  int i = 0;

  if (hero_list.empty()) {
    timeDead++;
    if (timeDead > 30)
      isLose = true;
  }

  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    // an Hero is dead?
    if ((*it).life <= 0) {
      // throw Particule (ghost))
      particule_list.push_front(particuleDead(it->x, it->y));

      // we kill him
      hero_list.erase(it);
      nbHero--;

      // selected another alive Hero
      if (heroSelected == i) {
        heroSelected = 0;
      } else {
        if (heroSelected > i)
          heroSelected--;
      }

      break;
    }

    // test if there are a ground under the feets of the Hero
    if (PlaceFree((*it), 0, 2)) {
      // apply gravity
      (*it).yspeed += 1.7;

    } else {
      if ((*it).yspeed < 0)
        (*it).yspeed = 0;

      // test for un jump
      if (i == heroSelected) {
        if (Input::IsKeyHold(GLFW_KEY_W) || Input::IsKeyHold(GLFW_KEY_UP)) {
          (*it).yspeed = -20;
        }
      }
    }

    if (i == heroSelected) {
      // move on the right
      if (Input::IsKeyHold(GLFW_KEY_D) || Input::IsKeyHold(GLFW_KEY_RIGHT)) {
        (*it).sens = false;
        (*it).xspeed += 2;
      }

      // move on the left
      if (Input::IsKeyHold(GLFW_KEY_A) || Input::IsKeyHold(GLFW_KEY_LEFT)) {
        (*it).sens = true;
        (*it).xspeed -= 2;
      }
    }
    // apply friction
    (*it).xspeed *= 0.75;
    (*it).yspeed *= 0.95;

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if ((*it).xspeed != 0) {
      if (!PlaceFree((*it), (*it).xspeed, 0)) {
        float i = (*it).xspeed;
        while (!PlaceFree((*it), i, 0))
          i -= Sign((*it).xspeed);
        (*it).xspeed = i;
      }
    }

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if ((*it).yspeed != 0) {
      if (!PlaceFree((*it), 0, (*it).yspeed)) {
        float i = (*it).yspeed;
        while (!PlaceFree((*it), 0, i))
          i -= Sign((*it).yspeed);
        (*it).yspeed = i;
      }
    }

    (*it).y += (*it).yspeed;
    (*it).x += (*it).xspeed;
    (*it).UpdateGeometry();
    ++i;
  }

  /////////////////////////////////
  //        movingBlocks         //
  /////////////////////////////////

  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    // test if there are an Hero on it.
    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      if (IsCollision((*it).geometry, (*itHero).geometry.shift(0, 2))) {
        if (PlaceFree((*itHero), (*it).xspeed,
                      (*it).yspeed))  // can we shift the levelHero
        {
          (*itHero).x += (*it).xspeed;
          (*itHero).y += (*it).yspeed;
          (*itHero).UpdateGeometry();
        }
      }
    }

    // test if we can apply speed
    if (!PlaceFree((*it), (*it).xspeed, (*it).yspeed)) {
      for (std::vector<Hero>::iterator itHero = hero_list.begin();
           itHero != hero_list.end(); ++itHero) {
        if (IsCollision((*it).geometry.shift((*it).xspeed, (*it).yspeed),
                        (*itHero).geometry))  // collision with levelHero?
        {
          if (PlaceFree((*itHero), (*it).xspeed,
                        (*it).yspeed))  // can we shift the levelHero
          {
            (*itHero).x += (*it).xspeed;
            (*itHero).y += (*it).yspeed;
            (*itHero).UpdateGeometry();
          }
        }
      }
      if (PlaceFree((*it), (*it).xspeed,
                    (*it).yspeed))  // after that, can we move?
      {
        (*it).x += (*it).xspeed;
        (*it).y += (*it).yspeed;
        (*it).UpdateGeometry();
      } else {
        (*it).xspeed *= -1;
        (*it).yspeed *= -1;
      }
    } else {
      (*it).x += (*it).xspeed;
      (*it).y += (*it).yspeed;
      (*it).UpdateGeometry();
    }
  }

  /////////////////////////////////
  //        FallingBlock         //
  /////////////////////////////////

  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if ((*it).etape == 0)  // here the FallingBlock still immobile
    {
      if (!PlaceFree((*it), 0, -1.5)) {
        (*it).etape = 1;
      }
    } else if ((*it).etape > 12)  // here it falls
    {
      (*it).etape++;
      // test if there are a ground under the feets of the FallingBlock
      if (PlaceFree((*it), 0, 1)) {
        // apply gravity
        (*it).yspeed += 1.7;
      } else {
        (*it).yspeed = 0;
      }

      // apply friction
      (*it).yspeed *= 0.95;

      // test if we can apply the speed to the position, if not we reduce it
      // while its too high
      if ((*it).yspeed != 0) {
        if (!PlaceFree((*it), 0, (*it).yspeed)) {
          float i = (*it).yspeed;
          while (!PlaceFree((*it), 0, i))
            i -= Sign((*it).yspeed);
          (*it).yspeed = i;
        }
      }

      (*it).y += (*it).yspeed;
      (*it).UpdateGeometry();
    } else  // here it wait and shake
    {
      (*it).etape++;
    }
  }

  /////////////////////////////////
  //        MovableBlock         //
  /////////////////////////////////
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    // test if there are a ground under the feets of the MovableBlock
    if (PlaceFree((*it), 0, 2)) {
      // apply gravity
      (*it).yspeed += 1.7;
    } else {
      (*it).yspeed = 0;
    }

    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      // move on the right
      if (IsCollision((*it).geometry.shift(-1, 0), (*itHero).geometry)) {
        if (PlaceFree((*it), +1, 0))
          (*it).xspeed += 2;
      }

      // move on the left
      if (IsCollision((*it).geometry.shift(1, 0), (*itHero).geometry)) {
        if (PlaceFree((*it), -1, 0))
          (*it).xspeed -= 2;
      }
    }

    // apply friction
    (*it).xspeed *= 0.4;
    (*it).yspeed *= 0.95;

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if ((*it).xspeed != 0) {
      if (!PlaceFree((*it), (*it).xspeed, 0)) {
        float i = (*it).xspeed;
        while (!PlaceFree((*it), i, 0)) {
          i -= Sign((*it).xspeed);
          if (i * (*it).xspeed <= 0) {
            i = 0;
            break;
          }
        }
        (*it).xspeed = i;
      }
    }

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if ((*it).yspeed != 0) {
      if (!PlaceFree((*it), 0, (*it).yspeed)) {
        float i = (*it).yspeed;
        while (!PlaceFree((*it), 0, i)) {
          i -= Sign((*it).yspeed);
          if (i * (*it).yspeed <= 0) {
            i = 0;
            break;
          }
        }
        (*it).yspeed = i;
      }
    }

    (*it).y += (*it).yspeed;
    (*it).x += (*it).xspeed;
    (*it).UpdateGeometry();
  }

  /////////////////////////////////
  //        Glass                //
  /////////////////////////////////
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    // test if there are a ground under the feets of the Glass
    if (PlaceFree((*it), 0, 1)) {
      // apply gravity
      (*it).yspeed += 1.7;
    } else {
      (*it).yspeed = 0;
    }

    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      // move on the right
      if (IsCollision((*it).geometry.shift(-1, 0), (*itHero).geometry)) {
        if (PlaceFree((*it), +1, 0))
          (*it).xspeed += 2;
      }

      // move on the left
      if (IsCollision((*it).geometry.shift(1, 0), (*itHero).geometry)) {
        if (PlaceFree((*it), -1, 0))
          (*it).xspeed -= 2;
      }
    }

    // apply friction
    (*it).xspeed *= 0.4;
    (*it).yspeed *= 0.95;

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if ((*it).xspeed != 0) {
      if (!PlaceFree((*it), (*it).xspeed, 0)) {
        float i = (*it).xspeed;
        while (!PlaceFree((*it), i, 0)) {
          i -= Sign((*it).xspeed);
          if (i * (*it).xspeed <= 0) {
            i = 0;
            break;
          }
        }
        (*it).xspeed = i;
      }
    }

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if ((*it).yspeed != 0) {
      if (!PlaceFree((*it), 0, (*it).yspeed)) {
        float i = (*it).yspeed;
        while (!PlaceFree((*it), 0, i)) {
          i -= Sign((*it).yspeed);
          if (i * (*it).yspeed <= 0) {
            i = 0;
            break;
          }
        }
        (*it).yspeed = i;
      }
    }

    (*it).y += (*it).yspeed;
    (*it).x += (*it).xspeed;
    (*it).UpdateGeometry();
  }
  /////////////////////////////////
  //        FinishBlock          //
  /////////////////////////////////

  for (std::vector<Hero>::iterator itHero = hero_list.begin();
       itHero != hero_list.end(); ++itHero) {
    if (IsCollision((*itHero).geometry, enddingBlock.geometry)) {
      isWin = true;
    }
  }

  /////////////////////////////////
  //        Detector             //
  /////////////////////////////////
  for (std::vector<Detector>::iterator it = detector_list.begin();
       it != detector_list.end(); ++it) {
    it->detected = false;
    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      if (IsCollision((*itHero).geometry, (*it).geometry)) {
        it->detected = true;
      }
    }
  }

  /////////////////////////////////
  //       Pics                  //
  /////////////////////////////////
  for (std::vector<Pic>::iterator it = pic_list.begin(); it != pic_list.end();
       ++it) {
    int nb = 0;
    for (std::vector<int>::iterator itInt = (it->connexion).begin();
         itInt != (it->connexion).end(); ++itInt) {
      if (detector_list[(*itInt)].detected) {
        nb++;
      }
    }
    bool avancer = false;
    switch (it->comparateur) {
      case 0:
        if (nb < it->nbRequis)
          avancer = true;
        break;
      case 1:
        if (nb == it->nbRequis)
          avancer = true;
        break;
      case 2:
        if (nb > it->nbRequis)
          avancer = true;
        break;
    }

    if (avancer) {
      if (it->avancement < 32)
        it->avancement += 2;
    } else {
      if (it->avancement > 0)
        it->avancement--;
    }

    float rad = float(it->angle) * 0.0174532925;
    float p1x = it->x + (it->avancement + 32) * cos(rad);
    float p1y = it->y - (it->avancement + 32) * sin(rad);
    float p2x = it->x + it->avancement * cos(rad) + 8 * cos(rad + 1.57079633);
    float p2y = it->y - it->avancement * sin(rad) - 8 * sin(rad + 1.57079633);
    float p3x = it->x + it->avancement * cos(rad) - 8 * cos(rad + 1.57079633);
    ;
    float p3y = it->y - it->avancement * sin(rad) + 8 * sin(rad + 1.57079633);
    Line l1(p2x, p2y, p1x, p1y);
    Line l2(p3x, p3y, p1x, p1y);

    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      if (IsCollision(itHero->geometry, l1)) {
        itHero->life = 0;
      } else if (IsCollision(itHero->geometry, l2)) {
        itHero->life = 0;
      }
    }
  }

  /////////////////////////////////
  //        Accelerator         //
  /////////////////////////////////
  for (std::list<Accelerator>::iterator it = accelerator_list.begin();
       it != accelerator_list.end(); ++it) {
    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      if (IsCollision((*itHero).geometry, (*it).geometry)) {
        itHero->xspeed += it->xacc;
        itHero->yspeed += it->yacc;
        itHero->xspeed *= it->viscosite;
        itHero->yspeed *= it->viscosite;
      }
    }
  }

  /////////////////////////////////
  //        Creepers             //
  /////////////////////////////////

  for (std::vector<Creeper>::iterator it = creeper_list.begin();
       it != creeper_list.end(); ++it) {
    if (!CollisionWithAllBlock(Point((*it).x + (*it).xspeed * 7, (*it).y))) {
      (*it).x += (*it).xspeed;
    } else {
      (*it).xspeed *= -1;
    }
    (*it).UpdateGeometry();

    if ((*it).mode == 0) {
      (*it).t++;
      for (std::vector<Hero>::iterator itHero = hero_list.begin();
           itHero != hero_list.end(); ++itHero) {
        if (abs((*itHero).x - (*it).x) + abs((*itHero).y - (*it).y) < 100) {
          (*it).mode = 1;
          (*it).t = 0;
        }
      }
      if (CollisionWithAllBlock((*it).geometry)) {
        (*it).mode = 1;
        (*it).t = 19;
      }
    } else {
      if ((*it).t < 20) {
        (*it).t++;
      } else {
        (*it).mode = 0;
        (*it).t = 0;
        for (int i = 0; i <= 20; i++)
          particule_list.push_front(
              particuleCreeperExplosion((*it).x, (*it).y));

        for (std::vector<Hero>::iterator itHero = hero_list.begin();
             itHero != hero_list.end(); ++itHero) {
          float distance2 =
              square((*itHero).x - (*it).x) + square((*itHero).y - (*it).y);
          (*itHero).xspeed +=
              InRange(1500 * ((*itHero).x - (*it).x) / distance2, -20, 20);
          (*itHero).yspeed +=
              InRange(1500 * ((*itHero).y - (*it).y) / distance2, -20, 20);
          (*itHero).life -= 3 * 10000 / int(distance2);
        }

        Sound explosion;
        // explosion.SetBuffer(SB_explosion);
        sound_list.push_front(explosion);
        (*(sound_list.begin())).Play();
        it = creeper_list.erase(it);
        break;
      }
    }
  }

  //////////////////////
  // Creeper explosion //
  //////////////////////

  for (std::list<Sound>::iterator it = sound_list.begin();
       it != sound_list.end(); ++it) {
    // if ((*it).GetStatus() == Sound::Stopped) {
    // sound_list.erase(it);
    // it = sound_list.begin();
    //}
  }

  /////////////////////////////////
  //        Teleporter           //
  /////////////////////////////////
  for (std::vector<Hero>::iterator itHero = hero_list.begin();
       itHero != hero_list.end(); ++itHero) {
    for (std::vector<Teleporter>::iterator it = teleporter_list.begin();
         it != teleporter_list.end(); ++it) {
      if (IsCollision((*itHero).geometry, (*it).geometry)) {
        // teleport the Hero
        (*itHero).x += (*it).xTeleport;
        (*itHero).y += (*it).yTeleport;
        (*itHero).UpdateGeometry();
      }
    }
  }

  /////////////////////////////////
  //        Cloneurs             //
  /////////////////////////////////

  for (std::vector<Cloner>::iterator it = cloneur_list.begin();
       it != cloneur_list.end(); ++it) {
    if ((*it).enable) {
      for (std::vector<Hero>::iterator itHero = hero_list.begin();
           itHero != hero_list.end(); ++itHero) {
        if (IsCollision(Point((*it).xstart + 16, (*it).ystart + 16),
                        (*itHero).geometry.increase(-8, -8))) {
          (*it).enable = false;
          hero_list.push_back(Hero((*it).xend, (*it).yend));
          nbHero++;
          // emit some particules on the end
          for (int a = 0; a <= 50; a++) {
            particule_list.push_front(
                particuleCloneur((*it).xend + rand() % 32, (*it).yend + 32));
          }

          break;
        }
      }
    }
  }
  ////////////////////////////
  // ArrowLauncherDetector //
  //////////////////////////

  for (std::vector<ArrowLauncherDetector>::iterator it =
           arrowLauncherDetector_list.begin();
       it != arrowLauncherDetector_list.end(); ++it) {
    if (it->mode != 0) {
      if (it->mode <= 2) {
        bool isDetected = false;
        for (std::vector<Hero>::iterator itHero = hero_list.begin();
             itHero != hero_list.end(); ++itHero) {
          if (IsCollision(it->geometry, itHero->geometry)) {
            isDetected = true;
          }
        }
        if (isDetected) {
          if (it->mode == 1)
            it->mode = 0;
          else if (it->mode == 2)
            it->mode = 3;
          int i = 0;
          for (std::vector<ArrowLauncher>::iterator it2 =
                   arrowLauncher_list.begin();
               it2 != arrowLauncher_list.end() and i <= it->launcherID; ++it2) {
            if (i == it->launcherID) {
              arrow_list.push_front(
                  Arrow((*it2).x + 16, (*it2).y + 16,
                        17 * cos((*it2).orientation * .0174532925),
                        -17 * sin((*it2).orientation * .0174532925)));
              it2->sound.Play();
            }
            i++;
          }
        }
      } else if (it->mode == 3) {
        if (it->t++ > 30) {
          it->t = 0;
          it->mode = 2;
        }
      }
    }
  }

  ////////////
  // Arrow///
  //////////
  for (std::list<Arrow>::iterator it = arrow_list.begin();
       it != arrow_list.end(); ++it) {
    (*it).Step();

    if (!it->damage) {
      // burst Particule
      if (abs((*it).xspeed) > 1 or abs((*it).yspeed) > 1)
        particule_list.push_front(particuleArrow(it->x, it->y));

      if (CollisionWithAllBlock((*it).geometry)) {
        if (abs((*it).xspeed) > 1 or abs((*it).yspeed) > 1) {
          for (std::vector<Hero>::iterator itHero = hero_list.begin();
               itHero != hero_list.end(); ++itHero) {
            if (IsCollision((*it).geometry, (*itHero).geometry)) {
              itHero->life -= 100;
              it->yspeed = 0.01;
            }
          }
        }
        it->xspeed = -0.1 * it->xspeed;
        it->yspeed = -0.1 * it->yspeed;
        while (CollisionWithAllBlock((*it).geometry)) {
          it->Step();
        }
        it->xspeed *= -1;
        it->yspeed *= -1;
        it->Step();
        (*it).xspeed = 0;
        (*it).yspeed = 0;
        it->damage = true;
      }
    } else {
      if (!CollisionWithAllBlock((*it).geometry)) {
        it->yspeed += 1.0;
        if (it->alpha > 10)
          it->alpha -= 10;
        else
          it->alpha = 0;
        it->sprite.SetColor(glm::vec4(255, 255, 255, it->alpha) / 255.f);
      }
    }
  }
  /////////////////////////////////
  //        particules           //
  /////////////////////////////////

  for (std::list<Particule>::iterator it = particule_list.begin();
       it != particule_list.end(); ++it) {
    if ((*it).Step()) {
      it = particule_list.erase(it);
      it--;
    }
  }

  // Pincette
  for (std::vector<Pincette>::iterator it = pincette_list.begin();
       it != pincette_list.end(); ++it) {
    (*it).Step();
  }

  //////////////////////
  //     Special      //
  //////////////////////
  for (std::list<Special>::iterator it = special_list.begin();
       it != special_list.end(); ++it) {
    switch (it->m) {
      case SPECIAL_ACC: {
        int& t = it->var[0];
        t = t + 1;
        particule_list.push_front(accParticule(
            318 + 16 + sin(t / 15.) * 4, 1152 + 32, -2 * sin(t / 15.), 60));
        particule_list.push_front(accParticule(
            510 + 16 + sin(t / 15.) * 4, 1088 + 32, -2 * sin(t / 15.), 90));
        particule_list.push_front(accParticule(
            330 + 16 + sin(t / 15.) * 4, 928 + 32, -2 * sin(t / 15.), 110));
        particule_list.push_front(accParticule(
            70 + 16 + sin(t / 15.) * 4, 832 + 32, -2 * sin(t / 15.), 110));
        particule_list.push_front(accParticule(
            70 + 16 + sin(t / 15.) * 4, 512 + 32, -2 * sin(t / 15.), 90));
        particule_list.push_front(accParticule(
            288 + 16 + sin(t / 15.) * 4, 352 + 32, -2 * sin(t / 15.), 90));
        particule_list.push_front(accParticule(
            480 + 16 + sin(t / 15.) * 4, 896 + 32, -2 * sin(t / 15.), 130));
      } break;
      case SPECIAL_ARBRE: {
        int x = hero_list.begin()->x;
        int y = hero_list.begin()->y;
        int& time = it->var[0];
        int& mode = it->var[1];
        int& size = it->var[2];
        if (mode == 0) {
          if ((768 - x) * (768 - x) + (416 - y) * (416 - y) < 40 * 40) {
            time++;
            if (time > 100) {
              TextPopup(2).Draw(screen);
              it->var[1] = 1;
              time = 0;
            }
          } else {
            if (time > 0)
              time--;
          }
        } else {
          time++;
          if (time > 15) {
            size *= 0.98;
            hero_list[0].sprite.SetScale(size / 100.0, size / 100.0);
            hero_list[0].x += (768 - x) / 4;
            hero_list[0].geometry.bottom =
                hero_list[0].geometry.top + 24 * (size + 10) / 110.0;
            // it=special_list.erase(it);
          }
          if (size < 3) {
            isWin = true;
          }
        }
      } break;

      case SPECIAL_ARBRE2: {
        int& time = it->var[0];
        int& size = it->var[1];
        time++;
        hero_list[0].sprite.SetScale(size / 100.0, size / 100.0);
        size += (95 - size) / 10;
      } break;

      case SPECIAL_ARBREBOSS: {
        static int sequence[4][24] = {
            {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
             12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
            {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
             11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
            {23, 0,  16, 17, 2, 20, 22, 1,  15, 6, 3,  19,
             7,  21, 8,  18, 4, 9,  10, 11, 12, 5, 13, 14},
            {0, 1, 2, 0, 1, 2, 0, 1, 2, 6, 6,  7,
             7, 8, 8, 9, 9, 6, 6, 7, 8, 9, 13, 13}};
        int& timeBeforeSalvo = it->var[0];
        int& SalvoId = it->var[1];
        int& i = it->var[2];
        int& timeWait = it->var[3];

        if (timeBeforeSalvo == 30) {
          Sound sound;
          // sound.SetBuffer(SB_boss[SalvoId]);
          sound_list.push_front(sound);
          (*(sound_list.begin())).Play();
        }

        if (timeBeforeSalvo > 0)
          timeBeforeSalvo--;
        else {
          if (timeWait <= 0) {
            timeWait = 2;
            int ii = 0;
            for (std::vector<ArrowLauncher>::iterator it2 =
                     arrowLauncher_list.begin();
                 it2 != arrowLauncher_list.end(); ++it2) {
              if (sequence[SalvoId][i] == ii) {
                arrow_list.push_front(
                    Arrow((*it2).x + 16, (*it2).y + 16,
                          17 * cos((*it2).orientation * .0174532925),
                          -17 * sin((*it2).orientation * .0174532925)));
                it2->sound.Play();
              }
              ii++;
            }
            i++;
            if (i >= 24) {
              timeBeforeSalvo = 100;
              i = 0;
              SalvoId = (SalvoId + 1) % 4;
            }
          } else {
            timeWait--;
          }
        }

        // fire
        static int posFireX[6] = {556,     556 + 28, 566 + 45,
                                  566 - 3, 566 + 35, 566 + 23};
        static int posFireY[6] = {418,      418 + 9,  418 - 9,
                                  418 - 28, 418 - 44, 418 - 91};

        int bougieIndex = 0;
        int nbFire = 0;
        for (std::list<Button>::iterator itbouton = button_list.begin();
             itbouton != button_list.end(); ++itbouton) {
          if (itbouton->nb_pressed == itbouton->nb_pressed_required - 1) {
            int xx =
                posFireX[bougieIndex] - 5 * sin(timeBeforeSalvo / 100.0 * 3.14);
            int yy = posFireY[bougieIndex];
            nbFire++;
            for (int h = 0; h < 4; h++)
              particule_list.push_front(fireParticule(xx, yy));
          }
          bougieIndex++;
        }
        if (nbFire >= 6 and timeBeforeSalvo == 0) {
          int h = img_sapin.height;
          int w = img_sapin.width;
          int x, y;
          for (x = 0; x < w; x += 3)
            for (y = x % 3; y < h; y += 3) {
              glm::vec4 c(1.0, 1.0, 1.0, 1.0);  // img_sapinGetPixel(x, y);
              if (c.a > 10) {
                particule_list.push_front(
                    arbreBossParticule(x + 517, y + 300, c));
              }
            }
          it = special_list.erase(it);
        }

        // destruct Hero
        for (std::vector<Hero>::iterator itHero = hero_list.begin();
             itHero != hero_list.end(); ++itHero) {
          Rectangle r(640 - 100, 640, 480, 480 - 100);
          if (IsCollision(itHero->geometry, r)) {
            itHero->life = -1;
            break;
          }
        }
      } break;

      case SPECIAL_WIND: {
        for (int i = 0; i < 6; i++) {
          particule_list.push_front(
              particuleWind(112 + rand() % 176, 335 + rand() % 17));
          particule_list.push_front(
              particuleWind(562 + rand() % 174, 466 + rand() % 14));
        }

      } break;
      case SPECIAL_END: {
        int& t = it->var[0];
        int& t2 = it->var[1];
        int& t3 = it->var[2];

        Rectangle rect(301, 301 + 32, 160, 160 + 41);
        for (std::vector<Hero>::iterator ithero = hero_list.begin();
             ithero != hero_list.end(); ++ithero) {
          if (IsCollision(rect, ithero->geometry)) {
            ithero->x += (301 + 8 - ithero->x) / 3;
            ithero->y += (160 - ithero->y) / 3;
            ithero->xspeed = 0;
            t++;
          }
        }
        if (t > 100) {
          if (t <= 250)
            t++;
          else
            (t = 251);
          if (t >= 251 and t3 <= 4.1)
            isWin = true;
        }
        if (t > 0) {
          if (t2 <= 0) {
            Sound sound;
            // sound.SetBuffer(SB_start);
            sound_list.push_front(sound);
            (*(sound_list.begin())).Play();
            t2 = t3;
            t3 = 4 + (t3 - 4) * 0.9;
          } else {
            t2--;
          }
        }
      } break;
    }
  }

  ///////////////
  // Button   //
  /////////////

  for (std::list<Button>::iterator it = button_list.begin();
       it != button_list.end(); ++it) {
    bool pressed = false;
    for (std::vector<Hero>::iterator ithero = hero_list.begin();
         ithero != hero_list.end(); ++ithero) {
      if (IsCollision(it->geometry, ithero->geometry)) {
        pressed = true;
      }
    }
    if (pressed) {
      if (not it->isPressed) {
        it->isPressed = true;
        if (it->nb_pressed < it->nb_pressed_required - 1) {
          it->nb_pressed++;
        }
      }
    } else {
      if (it->isPressed) {
        it->isPressed = false;
      }
    }
  }

  for (auto& pincette : pincette_list)
    pincette.Step();
}

bool Level::CollisionWithAllBlock(Rectangle geom) {
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(geom == (*it).geometry))
        return true;
    }
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(geom == (*it).geometry))
        return true;
    }
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(geom == (*it).geometry))
        return true;
    }
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(geom == (*it).geometry))
        return true;
    }
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(geom == (*it).geometry))
        return true;
    }
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(geom == (*it).geometry))
        return true;
    }
  }
  return false;
}

bool Level::CollisionWithAllBlock(Point p) {
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(p, (*it).geometry))
      return true;
  }
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(p, (*it).geometry))
      return true;
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(p, (*it).geometry))
      return true;
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(p, (*it).geometry))
      return true;
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(p, (*it).geometry))
      return true;
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(p, (*it).geometry))
      return true;
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(p, (*it).geometry))
      return true;
  }
  return false;
}

bool Level::PlaceFree(Hero h, float x, float y) {
  Rectangle shifted = h.geometry.shift(x, y);
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(shifted, (*it).geometry)) {
      if (!(h.geometry == (*it).geometry))
        return false;
    }
  }
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(shifted, (*it).geometry))
      return false;
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(shifted, (*it).geometry))
      return false;
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(shifted, (*it).geometry))
      return false;
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(shifted, (*it).geometry))
      return false;
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(shifted, (*it).geometry))
      return false;
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(shifted, (*it).geometry))
      return false;
  }
  return true;
}

bool Level::PlaceFree(MovingBlock m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(m.geometry == (*it).geometry))
        return false;
    }
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  return true;
}

bool Level::PlaceFree(FallingBlock m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(m.geometry == (*it).geometry))
        return false;
    }
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  return true;
}

bool Level::PlaceFree(MovableBlock m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(m.geometry == (*it).geometry))
        return false;
    }
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  return true;
}

bool Level::PlaceFree(Glass m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry)) {
      if (!(m.geometry == (*it).geometry))
        return false;
    }
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(geom, (*it).geometry))
      return false;
  }
  return true;
}

bool Level::CollisionWithAllBlock(Line l) {
  for (std::vector<Block>::iterator it = block_list.begin();
       it != block_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  for (std::vector<InvisibleBlock>::iterator it = invBlock_list.begin();
       it != invBlock_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  for (std::vector<MovingBlock>::iterator it = movBlock_list.begin();
       it != movBlock_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  for (std::vector<FallingBlock>::iterator it = fallBlock_list.begin();
       it != fallBlock_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  for (std::vector<MovableBlock>::iterator it = movableBlock_list.begin();
       it != movableBlock_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  for (std::vector<StaticMirror>::iterator it = staticMiroir_list.begin();
       it != staticMiroir_list.end(); ++it) {
    if (IsCollision(l, (*it).geometry))
      return true;
  }
  return false;
}

void Level::Laser(Screen& screen,
                  int x,
                  int y,
                  int angle,
                  int recursiveMaxLevel) {
  if (recursiveMaxLevel <= 0)
    return;
  float a = angle * 0.0174532925;
  int max = 1000;
  static int i = 0;
  float l = max;
  int xx = x;
  int yy = y;
  int xxx;
  int yyy;

  // Draw the Laser
  while (l > 0.5) {
    xxx = xx + l * cos(a);
    yyy = yy - l * sin(a);
    if (!CollisionWithAllBlock(Line(xx, yy, xxx, yyy))) {
      for (int r = 1; r <= 4; r += 1) {
        Shape Line =
            Shape::Line(xx, yy, xxx, yyy, r, glm::vec4(50, 0, 0, 0) / 255.f);
        Line.SetBlendMode(Blend::Add);
        screen.Draw(Line);
      }
      xx = xxx;
      yy = yyy;
    }
    l /= 2;
  }

  // we move on more Step
  xxx = xx + 1 * cos(a);
  yyy = yy - 1 * sin(a);
  /*
  for(int r=1;r<=4;r+=1)
  {
          Shape Line=Shape::Line(xx,yy,xxx,yyy,r,Color(50,0,0));
          Line.SetBlendMode(Blend::Add);
          screen.Draw(Line);
  }
  */
  xx = xxx;
  yy = yyy;

  // Draw an halo on the impact of the Laser
  i = rand();
  for (int r = 1; r <= 12 + i % 5; r += 1) {
    Shape circle = Shape::Circle(xx, yy, r, glm::vec4(10, 0, 0, 0) / 255.f);
    circle.SetBlendMode(Blend::Add);
    screen.Draw(circle);
  }

  // checking impact of the Laser with the Hero
  i = 0;
  for (std::vector<Hero>::iterator it = hero_list.begin();
       it != hero_list.end(); ++it) {
    if (IsCollision(Point(xx, yy), (*it).geometry.increase(4, 4))) {
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      (*it).life--;
    }
    i++;
  }
  // checking impact of the Laser with Glass
  for (std::vector<Glass>::iterator it = glassBlock_list.begin();
       it != glassBlock_list.end(); ++it) {
    if (IsCollision(Point(xx, yy), (*it).geometry.increase(5, 5))) {
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));

      (*it).height -= 0.2;
      //(*it).width-=0.2;
      //(*it).x+=0.1;
      (*it).y += 0.2;
      (*it).UpdateGeometry();
      if ((*it).height <= 3) {
        it = glassBlock_list.erase(it);
      }
    }
  }
  // checking impact of the Laser with StaticMirror
  for (std::vector<StaticMirror>::iterator it = staticMiroir_list.begin();
       it != staticMiroir_list.end(); ++it) {
    if (IsCollision(Rectangle(xx - 5, xx + 5, yy - 5, yy + 5),
                    (*it).geometry)) {
      Laser(screen, xx, yy, 2 * (*it).angle - angle,
            recursiveMaxLevel - 1);  // throw reflection
    }
  }
}

void Level::DrawElectricity(Screen& screen, int x1, int y1, int x2, int y2) {
  int x = x1;
  int y = y1;
  int xx, yy;
  int xfinal = x2;
  int yfinal = y2;
  while (abs(x - xfinal) + abs(y - yfinal) > 5) {
    float angle = atan2(yfinal - y, xfinal - x);
    angle += float(rand() % 10 - 20) * 0.2;
    xx = x - 9 * cos(angle);
    yy = y - 9 * sin(angle);
    for (int r = 3; r <= 10; r += 2) {
      Shape line1 =
          Shape::Line(x, y, xx, yy, r, glm::vec4(242, 224, 58, 20 - r) / 255.f,
                      r, glm::vec4(232, 214, 48, 10 - r) / 255.f);
      line1.SetBlendMode(Blend::Add);
      screen.Draw(line1);
    }

    Shape Line =
        Shape::Line(x, y, xx, yy, 2, glm::vec4(252, 234, 68, 255) / 255.f);
    x = xx;
    y = yy;

    screen.Draw(Line);
  }
}
