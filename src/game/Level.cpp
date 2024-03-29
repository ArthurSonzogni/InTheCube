// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Level.hpp"

#include <algorithm>
#include <random>
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Text.hpp>
#include <smk/View.hpp>

#include "game/BackgroundMusic.hpp"
#include "game/Lang.hpp"

auto rng = std::default_random_engine{};

extern BackgroundMusic background_music;

// clang-format off
float InRange(float x, float a, float b) {
  if (x < a) return a;
  if (x > b) return b;
  return x;
}
// clang-format on

void Level::LoadFromFile(std::string fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "Impossible to open the file: " << fileName << std::endl;
    return;
  }

  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string identifier;
    std::getline(ss, identifier, ' ');
    // blocks
    if (identifier == "b") {
      int x, y, width, height;
      ss >> x >> y >> width >> height;
      block_list.emplace_back(x, y, width, height);
    }

    // Hero
    else if (identifier == "h") {
      float x, y;
      ss >> x >> y;
      hero_list.emplace_back(x, y);
      nbHero++;
    }
    // invisible Block
    else if (identifier == "i") {
      int x, y, width, height;
      ss >> x >> y >> width >> height;
      invBlock_list.emplace_back(x, y, width, height);
    }
    // FallingBlock
    else if (identifier == "f") {
      int x, y;
      ss >> x >> y;
      fallBlock_list.emplace_back(x, y);
    }
    // MovableBlock
    else if (identifier == "m") {
      int x, y;
      ss >> x >> y;
      movableBlock_list.emplace_back(x, y);
    }
    // MovingBlock
    else if (identifier == "mm") {
      int x, y, width, height;
      float xspeed, yspeed;
      ss >> x >> y >> width >> height >> xspeed >> yspeed;
      movBlock_list.emplace_back(x, y, width, height, xspeed, yspeed);
    }
    // FinishBlock
    else if (identifier == "e") {
      int x, y, width, height;
      ss >> x >> y >> width >> height;
      enddingBlock = FinishBlock(x, y, width, height);
    }
    // setting the view
    else if (identifier == "v") {
      int xmin, xmax, ymin, ymax;
      ss >> xmin >> ymin >> xmax >> ymax;
      viewXMin = xmin;
      viewYMin = ymin;
      viewXMax = xmax;
      viewYMax = ymax;
    }
    // adding LaserTurret
    else if (identifier == "l") {
      int x, y, angle, xattach, yattach, mode, angleSpeed;
      ss >> x >> y >> angle >> xattach >> yattach >> mode >> angleSpeed;
      laserTurret_list.emplace_back(x, y, angle, xattach, yattach, mode,
                                    angleSpeed);
    }
    // adding Glass
    else if (identifier == "g") {
      int x, y, width, height;
      ss >> x >> y >> width >> height;
      glassBlock_list.push_back(Glass(x, y));
    }
    // adding noDrawBlock
    else if (identifier == "nd") {
      int x, y, width, height;
      ss >> x >> y >> width >> height;
      block_list.push_back(Block(x, y, width, height, false));
    }
    // adding Teleporter
    else if (identifier == "t") {
      int x, y, width, height, xTeleport, yTeleport;
      ss >> x >> y >> width >> height >> xTeleport >> yTeleport;
      teleporter_list.emplace_back(x, y, width, height, xTeleport, yTeleport);
      fluidViewEnable = false;
    }
    // adding Electricity
    else if (identifier == "elec") {
      int x1, y1, x2, y2, periode, offset;
      float ratio;
      ss >> x1 >> y1 >> x2 >> y2 >> ratio >> periode >> offset;
      electricity_list.emplace_back(x1, y1, x2, y2, ratio, periode, offset);
    }
    // adding cloneurs
    else if (identifier == "clone") {
      int x1, y1, x2, y2;
      ss >> x1 >> y1 >> x2 >> y2;
      cloneur_list.emplace_back(x1, y1, x2, y2);
    }
    // adding Decor back
    else if (identifier == "d0") {
      int x, y, img;
      ss >> x >> y >> img;
      decorBack_list.emplace_back(x, y, img);
    }
    // adding Decor front
    else if (identifier == "d1") {
      int x, y, img;
      ss >> x >> y >> img;
      decorFront_list.emplace_back(x, y, img);
    }
    // adding static miroir
    else if (identifier == "staticMirror") {
      int x1, y1, x2, y2, xattach, yattach;
      ss >> x1 >> y1 >> x2 >> y2 >> xattach >> yattach;
      staticMiroir_list.emplace_back(x1, y1, x2, y2, xattach, yattach);
    }
    // adding creepers
    else if (identifier == "creeper") {
      int x, y, width, height;
      ss >> x >> y >> width >> height;
      creeper_list.emplace_back(x, y);
    }
    // adding Arrow launcher
    else if (identifier == "arrowLauncher") {
      float x, y, orientation;
      ss >> x >> y >> orientation;
      arrowLauncher_list.emplace_back(x, y, orientation);
      block_list.emplace_back(x, y, 32, 32, false);
    }
    // adding ArrowLauncherDetector
    else if (identifier == "arrowLauncherDetector") {
      int x, y, width, height, mode, ID;
      ss >> x >> y >> width >> height >> mode >> ID;
      arrowLauncherDetector_list.emplace_back(x, x + width, y, y + height, mode,
                                              ID);
    }
    // adding Pincette
    else if (identifier == "pincette") {
      pincette_list.emplace_back();
    }
    // adding TextPopup
    else if (identifier == "textpopup") {
      int m;
      ss >> m;
      textpopup_list.emplace_back(m);
    }
    // adding Special
    else if (identifier == "special") {
      int m;
      ss >> m;
      special_list.emplace_back(m);
    }
    // adding Detector
    else if (identifier == "detector") {
      int x, y, width, height;
      ss >> x >> y >> width >> height;
      detector_list.emplace_back(x, y, x + width, y + height);
    }
    // adding Pic
    else if (identifier == "pic") {
      int x, y, angle, nbRequis, comparateur;
      ss >> x >> y >> angle >> nbRequis >> comparateur;
      std::vector<int> connexion;
      while (ss) {
        int detectorId;
        ss >> detectorId;
        connexion.push_back(detectorId);
      }
      pic_list.emplace_back(x, y, angle, nbRequis, comparateur, connexion);
    }
    // adding Accelerator
    else if (identifier == "accelerator") {
      int x, y, width, height, xacc, yacc;
      float viscosite;
      ss >> x >> y >> width >> height >> xacc >> yacc >> viscosite;
      accelerator_list.emplace_back(x, y, x + width, y + height, xacc, yacc,
                                    viscosite);
    }
    // adding Button
    else if (identifier == "button") {
      int x, y, n;
      ss >> x >> y >> n;
      button_list.emplace_back(x, y, n);
    }
  }
  file.close();

  spriteBackground = smk::Sprite(img_background);

  int separator_position = 0;
  {
    int i = 0;
    for (auto& it : fileName) {
      ++i;
      if (it == '/' || it == '\\')
        separator_position = i;
    }
  }
  fileName = fileName.substr(separator_position, -1);

  if (fileName == "IntroductionPincette")
    background_music.SetSound(smk::SoundBuffer());
  else if (fileName == "LevelArbreBoss")
    background_music.SetSound(SB_backgroundMusicAction);
  else if (fileName == "LevelEnd")
    background_music.SetSound(SB_end);
  else if (fileName == "LevelEnd2")
    background_music.SetSound(SB_end);
  else
    background_music.SetSound(SB_backgroundMusic);

  // The initial view position.
  auto geometry = hero_list[heroSelected].geometry;
  xcenter = geometry.left;
  ycenter = geometry.top;
}

void Level::Draw(smk::Window& window) {
  window.SetView(view_);

  // clang-format off
  for (int x = xcenter - 320 - int(xcenter / 2.67) % 24; x < xcenter + 320; x += 24) {
  for (int y = ycenter - 240 - int(ycenter / 2.67) % 24; y < ycenter + 240; y += 24) {
      spriteBackground.SetPosition(x, y);
      window.Draw(spriteBackground);
    }
  }

  for (auto& it : special_list) it.DrawBackground(window, xcenter, ycenter);
  for (auto& it : decorBack_list) it.Draw(window);
  for (auto& it : special_list) it.DrawOverDecoration(window);
  // clang-format on

  // Draw static turrets and throw out Laser
  for (auto& it : laserTurret_list) {
    it.Draw(window);
    EmitLaser(window, it.x, it.y, it.angle, 10);
  }

  // clang-format off
  for (auto& it : block_list) it.Draw(window);
  for (auto& it : invBlock_list) it.Draw(window, hero_list[heroSelected]);
  for (auto& it : movBlock_list) it.Draw(window);
  for (auto& it : fallBlock_list) it.Draw(window);
  for (auto& it : movableBlock_list) it.Draw(window);
  for (auto& it : glassBlock_list) it.Draw(window);
  for (auto& it : staticMiroir_list) it.Draw(window);
  for (auto& it : pic_list) it.Draw(window);
  for (auto& it : special_list) it.DrawForeground(window, isWin);
  for (auto& it : button_list) it.Draw(window);
  int i = 0;
  for (auto& it : hero_list) it.Draw(window, heroSelected == i++);
  for (auto& it : creeper_list) it.Draw(window);
  for (auto& it : arrow_list) it.Draw(window);
  for (auto& it : arrowLauncher_list) it.Draw(window);
  for (auto& it : cloneur_list) it.Draw(window);
  for (auto& it : particule_list) it.Draw(window);
  for (auto& it : electricity_list) it.Draw(window);
  for (auto& it : laser_) it.Draw(window);
  for (auto& pincette : pincette_list) pincette.Draw(window);
  for (auto& it : decorFront_list) it.Draw(window);

  // drawing life bar
  auto coeur = smk::Sprite(img_coeur);
  if (!hero_list.empty()) {
    for (int i = 1; i <= hero_list[heroSelected].life; i++) {
      coeur.SetPosition(xcenter + i * 16 - 320, ycenter + 220);
      window.Draw(coeur);
    }
  }

  for(auto& it : drawn_textpopup_list) it.Draw(window);
  // clang-format on
  laser_.clear();
}

void Level::Step(Input::T input, smk::Window& window) {
  std::shuffle(std::begin(fallBlock_list), std::end(fallBlock_list), rng);

  SetView(window);

  /////////////////////////////////
  //        extra key            //
  /////////////////////////////////

  // test if the player will end the game
  isEscape = input & Input::Escape;
  isLose = input & Input::Restart;

  // if (window.input().IsKeyPressed(GLFW_KEY_T)) {
  // isWin = true;
  //}
  // if (window.input().IsKeyPressed(GLFW_KEY_Y)) {
  // isPrevious = true;
  //}

  // Drawn popup
  for (auto it = drawn_textpopup_list.begin(); it != drawn_textpopup_list.end();
       ++it) {
    if (it->Step(window))
      drawn_textpopup_list.erase(it);
    return;
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
    if (input & Input::Space) {
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

  for (auto it = hero_list.begin(); it != hero_list.end(); ++it) {
    auto& hero = *it;

    if (hero.in_laser) {
      hero.life--;
      hero.in_laser = false;
    }

    // an Hero is dead?
    if (hero.life <= 0) {
      // throw Particule (ghost))
      particule_list.push_front(particuleDead(hero.x, hero.y));

      // we kill him
      it = hero_list.erase(it);
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
    if (PlaceFree(hero, 0, 2)) {
      // apply gravity
      hero.yspeed += 1.7;

    } else {
      if (hero.yspeed < 0)
        hero.yspeed = 0;

      // test for un jump
      if (i == heroSelected) {
        if (input & Input::Up)
          hero.yspeed = -20;
      }
    }

    if (i == heroSelected) {
      // move on the right
      if (input & Input::Right) {
        hero.sens = false;
        hero.xspeed += 2;
      }

      // move on the left
      if (input & Input::Left) {
        hero.sens = true;
        hero.xspeed -= 2;
      }
    }
    // apply friction
    hero.xspeed *= 0.75;
    hero.yspeed *= 0.95;

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if (hero.xspeed != 0) {
      if (!PlaceFree(hero, hero.xspeed, 0)) {
        float i = hero.xspeed;
        while (!PlaceFree(hero, i, 0))
          i -= Sign(hero.xspeed);
        hero.xspeed = i;
      }
    }

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if (hero.yspeed != 0) {
      if (!PlaceFree(hero, 0, hero.yspeed)) {
        float i = hero.yspeed;
        while (!PlaceFree(hero, 0, i))
          i -= Sign(hero.yspeed);
        hero.yspeed = i;
      }
    }

    hero.y += hero.yspeed;
    hero.x += hero.xspeed;

    hero.UpdateGeometry();
    ++i;
  }

  /////////////////////////////////
  //        movingBlocks         //
  /////////////////////////////////

  for (auto& block : movBlock_list) {
    // If there is a moving block under the hero, make the hero move with the
    // block.
    for (auto& hero : hero_list) {
      if (IsCollision(block.geometry, hero.geometry.shift(0, 2))) {
        if (PlaceFree(hero, block.xspeed, block.yspeed)) {
          hero.x += block.xspeed;
          hero.y += block.yspeed;
          hero.UpdateGeometry();
        }
      }
    }

    // Move the moving block.
    if (PlaceFree(block, block.xspeed, block.yspeed)) {
      block.x += block.xspeed;
      block.y += block.yspeed;
      block.UpdateGeometry();
    } else {
      // Is block blocked by the hero? If yes, try to move the hero.
      for (auto& hero : hero_list) {
        if (IsCollision(block.geometry.shift(block.xspeed, block.yspeed),
                        hero.geometry)) {
          // The moving block is blocked by the hero. Try to move the hero.
          if (PlaceFree(hero, block.xspeed, block.yspeed)) {
            hero.x += block.xspeed;
            hero.y += block.yspeed;
            hero.UpdateGeometry();
          }
        }
      }

      // Are we unblocked?
      if (PlaceFree(block, block.xspeed, block.yspeed)) {
        block.x += block.xspeed;
        block.y += block.yspeed;
        block.UpdateGeometry();
      } else {
        block.xspeed *= -1;
        block.yspeed *= -1;
        block.UpdateGeometry();
      }
    }
  }

  /////////////////////////////////
  //        FallingBlock         //
  /////////////////////////////////

  for (auto& it : fallBlock_list) {
    if (it.etape == 0)  // here the FallingBlock still immobile
    {
      if (!PlaceFree(it, 0, -1.5)) {
        it.etape = 1;
      }
    } else if (it.etape > 12)  // here it falls
    {
      it.etape++;
      // test if there are a ground under the feets of the FallingBlock
      if (PlaceFree(it, 0, 1)) {
        // apply gravity
        it.yspeed += 1.7;
      } else {
        it.yspeed = 0;
      }

      // apply friction
      it.yspeed *= 0.95;

      // test if we can apply the speed to the position, if not we reduce it
      // while its too high
      if (it.yspeed != 0) {
        if (!PlaceFree(it, 0, it.yspeed)) {
          float i = it.yspeed;
          while (!PlaceFree(it, 0, i))
            i -= Sign(it.yspeed);
          it.yspeed = i;
        }
      }

      it.y += it.yspeed;
      it.UpdateGeometry();
    } else  // here it wait and shake
    {
      it.etape++;
    }
  }

  /////////////////////////////////
  //        MovableBlock         //
  /////////////////////////////////
  for (auto& it : movableBlock_list) {
    // test if there are a ground under the feets of the MovableBlock
    if (PlaceFree(it, 0, 2)) {
      // apply gravity
      it.yspeed += 1.7;
    } else {
      it.yspeed = 0;
    }

    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      // move on the right
      if (IsCollision(it.geometry.shift(-1, 0), (*itHero).geometry)) {
        if (PlaceFree(it, +1, 0))
          it.xspeed += 2;
      }

      // move on the left
      if (IsCollision(it.geometry.shift(1, 0), (*itHero).geometry)) {
        if (PlaceFree(it, -1, 0))
          it.xspeed -= 2;
      }
    }

    // apply friction
    it.xspeed *= 0.4;
    it.yspeed *= 0.95;

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if (it.xspeed != 0) {
      if (!PlaceFree(it, it.xspeed, 0)) {
        float i = it.xspeed;
        while (!PlaceFree(it, i, 0)) {
          i -= Sign(it.xspeed);
          if (i * it.xspeed <= 0) {
            i = 0;
            break;
          }
        }
        it.xspeed = i;
      }
    }

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if (it.yspeed != 0) {
      if (!PlaceFree(it, 0, it.yspeed)) {
        float i = it.yspeed;
        while (!PlaceFree(it, 0, i)) {
          i -= Sign(it.yspeed);
          if (i * it.yspeed <= 0) {
            i = 0;
            break;
          }
        }
        it.yspeed = i;
      }
    }

    it.y += it.yspeed;
    it.x += it.xspeed;
    it.UpdateGeometry();
  }

  /////////////////////////////////
  //        Glass                //
  /////////////////////////////////
  for (auto& it : glassBlock_list) {
    // test if there are a ground under the feets of the Glass
    if (PlaceFree(it, 0, 1)) {
      // apply gravity
      it.yspeed += 1.7;
    } else {
      it.yspeed = 0;
    }

    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      // move on the right
      if (IsCollision(it.geometry.shift(-1, 0), (*itHero).geometry)) {
        if (PlaceFree(it, +1, 0))
          it.xspeed += 2;
      }

      // move on the left
      if (IsCollision(it.geometry.shift(1, 0), (*itHero).geometry)) {
        if (PlaceFree(it, -1, 0))
          it.xspeed -= 2;
      }
    }

    // apply friction
    it.xspeed *= 0.4;
    it.yspeed *= 0.95;

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if (it.xspeed != 0) {
      if (!PlaceFree(it, it.xspeed, 0)) {
        float i = it.xspeed;
        while (!PlaceFree(it, i, 0)) {
          i -= Sign(it.xspeed);
          if (i * it.xspeed <= 0) {
            i = 0;
            break;
          }
        }
        it.xspeed = i;
      }
    }

    // test if we can apply the speed to the position, if not we reduce it while
    // its too high
    if (it.yspeed != 0) {
      if (!PlaceFree(it, 0, it.yspeed)) {
        float i = it.yspeed;
        while (!PlaceFree(it, 0, i)) {
          i -= Sign(it.yspeed);
          if (i * it.yspeed <= 0) {
            i = 0;
            break;
          }
        }
        it.yspeed = i;
      }
    }

    it.y += it.yspeed;
    it.x += it.xspeed;
    it.UpdateGeometry();
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
  for (auto& it : detector_list) {
    it.detected = false;
    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      if (IsCollision((*itHero).geometry, it.geometry)) {
        it.detected = true;
      }
    }
  }

  /////////////////////////////////
  //       Pics                  //
  /////////////////////////////////
  for (auto& it : pic_list) {
    int nb = 0;
    for (std::vector<int>::iterator itInt = (it.connexion).begin();
         itInt != (it.connexion).end(); ++itInt) {
      if (detector_list[(*itInt)].detected) {
        nb++;
      }
    }
    bool avancer = false;
    switch (it.comparateur) {
      case 0:
        if (nb < it.nbRequis)
          avancer = true;
        break;
      case 1:
        if (nb == it.nbRequis)
          avancer = true;
        break;
      case 2:
        if (nb > it.nbRequis)
          avancer = true;
        break;
    }

    if (avancer) {
      if (it.avancement < 32)
        it.avancement += 2;
    } else {
      if (it.avancement > 0)
        it.avancement--;
    }

    float rad = float(it.angle) * 0.0174532925;
    float p1x = it.x + (it.avancement + 32) * cos(rad);
    float p1y = it.y - (it.avancement + 32) * sin(rad);
    float p2x = it.x + it.avancement * cos(rad) + 8 * cos(rad + 1.57079633);
    float p2y = it.y - it.avancement * sin(rad) - 8 * sin(rad + 1.57079633);
    float p3x = it.x + it.avancement * cos(rad) - 8 * cos(rad + 1.57079633);
    float p3y = it.y - it.avancement * sin(rad) + 8 * sin(rad + 1.57079633);
    Line l1 = {{p2x, p2y}, {p1x, p1y}};
    Line l2 = {{p3x, p3y}, {p1x, p1y}};

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
  for (auto& it : accelerator_list) {
    for (std::vector<Hero>::iterator itHero = hero_list.begin();
         itHero != hero_list.end(); ++itHero) {
      if (IsCollision((*itHero).geometry, it.geometry)) {
        itHero->xspeed += it.xacc;
        itHero->yspeed += it.yacc;
        itHero->xspeed *= it.viscosite;
        itHero->yspeed *= it.viscosite;
      }
    }
  }

  /////////////////////////////////
  //        Creepers             //
  /////////////////////////////////

  for (auto creeper = creeper_list.begin(); creeper != creeper_list.end();) {
    if (!CollisionWithAllBlock(
            Point(creeper->x + creeper->xspeed * 7, creeper->y))) {
      creeper->x += creeper->xspeed;
    } else {
      creeper->xspeed *= -1;
    }
    creeper->UpdateGeometry();

    if (creeper->mode == 0) {
      creeper->t++;
      for (std::vector<Hero>::iterator itHero = hero_list.begin();
           itHero != hero_list.end(); ++itHero) {
        if (std::abs((*itHero).x - creeper->x) + std::abs((*itHero).y - creeper->y) <
            100) {
          creeper->mode = 1;
          creeper->t = 0;
        }
      }
      if (CollisionWithAllBlock(creeper->geometry)) {
        creeper->mode = 1;
        creeper->t = 19;
      }
    } else {
      if (creeper->t < 20) {
        creeper->t++;
      } else {
        creeper->mode = 0;
        creeper->t = 0;
        for (int i = 0; i <= 20; i++)
          particule_list.push_front(
              particuleCreeperExplosion(creeper->x, creeper->y));

        for (std::vector<Hero>::iterator itHero = hero_list.begin();
             itHero != hero_list.end(); ++itHero) {
          float distance2 = square((*itHero).x - creeper->x) +
                            square((*itHero).y - creeper->y);
          (*itHero).xspeed +=
              InRange(1500 * ((*itHero).x - creeper->x) / distance2, -20, 20);
          (*itHero).yspeed +=
              InRange(1500 * ((*itHero).y - creeper->y) / distance2, -20, 20);
          (*itHero).life -= 3 * 10000 / int(distance2);
        }

        auto explosion = smk::Sound(SB_explosion);
        explosion.Play();
        sound_list.push_front(std::move(explosion));
        creeper = creeper_list.erase(creeper);
        continue;
      }
    }
    ++creeper;
  }

  /////////////////////////////////
  //        Cloneurs             //
  /////////////////////////////////

  for (auto& it : cloneur_list) {
    if (it.enable) {
      for (int a = 0; a <= 1; a++) {
        particule_list.push_front(
            particuleCloneur(it.xstart + rand() % 32, it.ystart + 32));
      }
      for (std::vector<Hero>::iterator itHero = hero_list.begin();
           itHero != hero_list.end(); ++itHero) {
        if (IsCollision(Point(it.xstart + 16, it.ystart + 16),
                        (*itHero).geometry.increase(-8, -8))) {
          it.enable = false;
          hero_list.push_back(Hero(it.xend, it.yend));
          nbHero++;
          // emit some particules on the end
          for (int a = 0; a <= 50; a++) {
            particule_list.push_front(
                particuleCloneur(it.xend + rand() % 32, it.yend + 32));
          }

          break;
        }
      }
    }
  }
  ////////////////////////////
  // ArrowLauncherDetector //
  //////////////////////////

  for (auto& arrow_launcher_detector : arrowLauncherDetector_list) {
    if (arrow_launcher_detector.mode != 0) {
      if (arrow_launcher_detector.mode <= 2) {
        bool isDetected = false;
        for (std::vector<Hero>::iterator itHero = hero_list.begin();
             itHero != hero_list.end(); ++itHero) {
          if (IsCollision(arrow_launcher_detector.geometry, itHero->geometry)) {
            isDetected = true;
          }
        }
        if (isDetected) {
          if (arrow_launcher_detector.mode == 1)
            arrow_launcher_detector.mode = 0;
          else if (arrow_launcher_detector.mode == 2)
            arrow_launcher_detector.mode = 3;
          int i = 0;
          for (auto& arrow_launcher : arrowLauncher_list) {
            if (i == arrow_launcher_detector.launcherID) {
              arrow_list.push_front(
                  Arrow({arrow_launcher.x + 16, arrow_launcher.y + 16},
                        {+17 * cos(arrow_launcher.orientation * .0174532925),
                         -17 * sin(arrow_launcher.orientation * .0174532925)}));
              arrow_launcher.sound.Play();
            }
            i++;
          }
        }
      } else if (arrow_launcher_detector.mode == 3) {
        if (arrow_launcher_detector.t++ > 30) {
          arrow_launcher_detector.t = 0;
          arrow_launcher_detector.mode = 2;
        }
      }
    }
  }

  ////////////
  // Arrow///
  //////////
  for (auto& it : arrow_list) {
    it.Step();
    if (it.damage) {
      if (!CollisionWithAllBlock(it.position)) {
        it.speed.y += 1.0;
        it.alpha -= std::min(10, it.alpha);
      }
      continue;
    }

    // burst Particule
    if (glm::length(it.speed) > 1.f)
      particule_list.push_front(particuleArrow(it.position.x, it.position.y));

    if (!CollisionWithAllBlock(it.position))
      continue;

    if (glm::length(it.speed) > 1.f) {
      for (std::vector<Hero>::iterator itHero = hero_list.begin();
           itHero != hero_list.end(); ++itHero) {
        if (IsCollision(it.position, (*itHero).geometry)) {
          itHero->life -= 100;
          it.speed.y = 0.01;
        }
      }
    }
    it.speed.x = -0.1 * it.speed.x;
    it.speed.y = -0.1 * it.speed.y;
    while (CollisionWithAllBlock(it.position))
      it.Step();
    it.speed *= -1;
    it.Step();
    it.speed = {0.f, 0.f};
    it.damage = true;
  }
  /////////////////////////////////
  //        particules           //
  /////////////////////////////////

  for (auto particule = particule_list.begin();
       particule != particule_list.end();) {
    if (particule->Step())
      particule = particule_list.erase(particule);
    else
      ++particule;
  }

  // Pincette
  for (auto& it : pincette_list)
    it.Step();
  for (auto& special : special_list)
    special.Step(*this);

  ///////////////
  // Button   //
  /////////////

  for (auto& it : button_list) {
    bool pressed = false;
    for (std::vector<Hero>::iterator ithero = hero_list.begin();
         ithero != hero_list.end(); ++ithero) {
      if (IsCollision(it.geometry, ithero->geometry)) {
        pressed = true;
      }
    }
    if (pressed) {
      if (not it.isPressed) {
        it.isPressed = true;
        if (it.nb_pressed < it.nb_pressed_required - 1) {
          it.nb_pressed++;
        }
      }
    } else {
      if (it.isPressed) {
        it.isPressed = false;
      }
    }
  }

  for (auto& pincette : pincette_list)
    pincette.Step();

  // Draw static turrets and throw out Laser
  for (auto& it : laserTurret_list) {
    it.Step();
  }

  for (auto it = glassBlock_list.begin(); it != glassBlock_list.end(); ++it) {
    auto& glass = *it;
    if (!glass.in_laser)
      continue;
    glass.in_laser = false;
    glass.height -= 0.2;
    glass.y += 0.2;
    glass.UpdateGeometry();
    if (glass.height <= 3)
      it = glassBlock_list.erase(it);
  }

  /////////////////////////////////
  //        Teleporter           //
  /////////////////////////////////
  for (std::vector<Hero>::iterator itHero = hero_list.begin();
       itHero != hero_list.end(); ++itHero) {
    for (auto& it : teleporter_list) {
      if (IsCollision((*itHero).geometry, it.geometry)) {
        // teleport the Hero
        (*itHero).x += it.xTeleport;
        (*itHero).y += it.yTeleport;
        (*itHero).UpdateGeometry();
        SetView(window);
      }
    }
  }
  for (auto& it : electricity_list) {
    it.Step(time);

    if (it.is_active()) {
      // collision with an Hero
      for (auto& hero : hero_list) {
        if (IsCollision(hero.geometry.increase(10, 10),
                        Line{{it.x1, it.y1}, {it.x2, it.y2}})) {
          hero.life -= 4;
        }
      }
    }
  }

  // TextPopup.
  for (auto it = textpopup_list.begin(); it != textpopup_list.end();) {
    for (auto& hero : hero_list) {
      if (IsCollision(it->geometry, hero.geometry)) {
        drawn_textpopup_list.push_back(*it);
        it = textpopup_list.erase(it);
      } else {
        ++it;
      }
    }
  }
}

bool Level::CollisionWithAllBlock(Rectangle geom) {
  for (auto& it : block_list)
    if (IsCollision(geom, it.geometry))
      if (!(geom == it.geometry))
        return true;
  for (auto& it : invBlock_list)
    if (IsCollision(geom, it.geometry))
      if (!(geom == it.geometry))
        return true;
  for (auto& it : movBlock_list)
    if (IsCollision(geom, it.geometry))
      if (!(geom == it.geometry))
        return true;
  for (auto& it : fallBlock_list)
    if (IsCollision(geom, it.geometry))
      if (!(geom == it.geometry))
        return true;
  for (auto& it : movableBlock_list)
    if (IsCollision(geom, it.geometry))
      if (!(geom == it.geometry))
        return true;
  for (auto& it : glassBlock_list)
    if (IsCollision(geom, it.geometry))
      if (!(geom == it.geometry))
        return true;
  return false;
}

bool Level::CollisionWithAllBlock(Point p) {
  for (auto& it : hero_list)
    if (IsCollision(p, it.geometry))
      return true;
  for (auto& it : block_list)
    if (IsCollision(p, it.geometry))
      return true;
  for (auto& it : invBlock_list)
    if (IsCollision(p, it.geometry))
      return true;
  for (auto& it : movBlock_list)
    if (IsCollision(p, it.geometry))
      return true;
  for (auto& it : fallBlock_list)
    if (IsCollision(p, it.geometry))
      return true;
  for (auto& it : movableBlock_list)
    if (IsCollision(p, it.geometry))
      return true;
  for (auto& it : glassBlock_list)
    if (IsCollision(p, it.geometry))
      return true;
  return false;
}

bool Level::PlaceFree(const Hero& h, float x, float y) {
  Rectangle shifted = h.geometry.shift(x, y);
  // clang-format off
  for (auto& it : block_list)        if (IsCollision(shifted, it.geometry)) return false;
  for (auto& it : invBlock_list)     if (IsCollision(shifted, it.geometry)) return false;
  for (auto& it : movBlock_list)     if (IsCollision(shifted, it.geometry)) return false;
  for (auto& it : fallBlock_list)    if (IsCollision(shifted, it.geometry)) return false;
  for (auto& it : movableBlock_list) if (IsCollision(shifted, it.geometry)) return false;
  for (auto& it : glassBlock_list)   if (IsCollision(shifted, it.geometry)) return false;
  for (auto& it : hero_list)         if (IsCollision(shifted, it.geometry))  if (!(h.geometry == it.geometry)) return false;
  return true;
  // clang-format on
}

bool Level::PlaceFree(const MovingBlock& m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  for (auto& it : block_list)
    if (IsCollision(geom, it.geometry))
      return false;
  for (auto& it : invBlock_list)
    if (IsCollision(geom, it.geometry))
      return false;
  for (auto& it : fallBlock_list)
    if (IsCollision(geom, it.geometry))
      return false;
  for (auto& it : movableBlock_list)
    if (IsCollision(geom, it.geometry))
      return false;
  for (auto& it : hero_list)
    if (IsCollision(geom, it.geometry))
      return false;
  for (auto& it : glassBlock_list)
    if (IsCollision(geom, it.geometry))
      return false;
  for (auto& it : movBlock_list)
    if (IsCollision(geom, it.geometry))
      if (!(m.geometry == it.geometry))
        return false;
  return true;
}

bool Level::PlaceFree(const FallingBlock& m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  // clang-format off
  for (auto& it : block_list)        if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : invBlock_list)     if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : movBlock_list)     if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : movableBlock_list) if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : glassBlock_list)   if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : hero_list)         if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : fallBlock_list)    if (IsCollision(geom, it.geometry)) if (!(m.geometry == it.geometry)) return false;
  return true;
  // clang-format on
}

bool Level::PlaceFree(const MovableBlock& m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  // clang-format off
  for (auto& it : block_list)        if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : invBlock_list)     if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : movBlock_list)     if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : fallBlock_list)    if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : glassBlock_list)   if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : hero_list)         if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : movableBlock_list) if (IsCollision(geom, it.geometry)) if (!(m.geometry == it.geometry))
        return false;
  // clang-format on
  return true;
}

bool Level::PlaceFree(const Glass& m, float x, float y) {
  Rectangle geom = m.geometry.shift(x, y);
  // clang-format off
  for (auto& it : block_list)        if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : invBlock_list)     if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : movBlock_list)     if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : movableBlock_list) if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : fallBlock_list)    if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : hero_list)         if (IsCollision(geom, it.geometry)) return false;
  for (auto& it : glassBlock_list)   if (IsCollision(geom, it.geometry)) if (!(m.geometry == it.geometry)) return false;
  // clang-format on
  return true;
}

bool Level::CollisionWithAllBlock(Line l) {
  // clang-format off
  for (auto& it : block_list)        if (IsCollision(l, it.geometry)) return true;
  for (auto& it : invBlock_list)     if (IsCollision(l, it.geometry)) return true;
  for (auto& it : movBlock_list)     if (IsCollision(l, it.geometry)) return true;
  for (auto& it : fallBlock_list)    if (IsCollision(l, it.geometry)) return true;
  for (auto& it : movableBlock_list) if (IsCollision(l, it.geometry)) return true;
  for (auto& it : glassBlock_list)   if (IsCollision(l, it.geometry)) return true;
  for (auto& it : hero_list)         if (IsCollision(l, it.geometry)) return true;
  for (auto& it : staticMiroir_list) if (IsCollision(l, it.geometry)) return true;
  return false;
  // clang-format on
}

void Level::EmitLaser(smk::Window& window,
                      float x,
                      float y,
                      float angle,
                      int recursiveMaxLevel) {
  if (recursiveMaxLevel <= 0)
    return;
  float a = angle * 0.0174532925;
  int max = 1000;
  float l = max;
  float xx = x + 2 * cos(a);
  float yy = y - 2 * sin(a);

  // Draw the Laser
  while (l > 0.5) {
    float xxx = xx + l * cos(a);
    float yyy = yy - l * sin(a);
    if (!CollisionWithAllBlock(Line{{xx, yy}, {xxx, yyy}})) {
      for (int r = 1; r <= 4; r += 1) {
        auto line = smk::Shape::Line({xx, yy}, {xxx, yyy}, r);
        line.SetColor(glm::vec4(0.2, 0, 0, 0));
        line.SetBlendMode(smk::BlendMode::Add);
        window.Draw(line);
      }
      xx = xxx;
      yy = yyy;
    }
    l /= 2;
  }

  // we move on more Step
  xx = xx + 1 * cos(a);
  yy = yy - 1 * sin(a);

  laser_.push_back(Laser{glm::vec2(x, y), glm::vec2(xx, yy)});

  // checking impact of the Laser with the Hero
  for (auto& it : hero_list) {
    if (IsCollision(Point(xx, yy), it.geometry.increase(4, 4))) {
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnHero(xx, yy, x, y));
      it.in_laser = true;
    }
  }
  // checking impact of the Laser with Glass
  for (auto it = glassBlock_list.begin(); it != glassBlock_list.end(); ++it) {
    auto& glass = *it;
    if (IsCollision(Point(xx, yy), glass.geometry.increase(5, 5))) {
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));
      particule_list.push_front(particuleLaserOnGlass(xx, yy, x, y));

      glass.in_laser = true;
    }
  }

  // checking impact of the Laser with StaticMirror
  for (auto& it : staticMiroir_list) {
    if (IsCollision(Rectangle(xx - 5, xx + 5, yy - 5, yy + 5), it.geometry)) {
      EmitLaser(window, xx, yy, 2 * it.angle - angle,
                recursiveMaxLevel - 1);  // throw reflection
    }
  }
}

void Level::SetView(smk::Window& window) {
  if (!hero_list.empty()) {
    auto geometry = hero_list[heroSelected].geometry;
    if (fluidViewEnable) {
      xcenter += 0.1 * (geometry.left - xcenter);
      ycenter += 0.1 * (geometry.top - ycenter);
    } else {
      xcenter = geometry.left;
      ycenter = geometry.left;
    }
    xcenter = std::max(viewXMin + 320, xcenter);
    xcenter = std::min(viewXMax - 320, xcenter);
    ycenter = std::max(viewYMin + 240, ycenter);
    ycenter = std::min(viewYMax - 240, ycenter);
    view_.SetCenter(xcenter, ycenter);
  }

  (void)window;
  view_.SetSize(640, 480);
}
