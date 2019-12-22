#include "Special.hpp"

#include "Lang.hpp"
#include "Level.hpp"
#include "Resource.hpp"
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Sound.hpp>
#include <smk/Text.hpp>

Special::Special(int M) {
  m = M;
  switch (m) {
    case SPECIAL_ARBRE:
      var.push_back(0);
      var.push_back(0);
      var.push_back(100);
      break;
    case SPECIAL_ARBRE2:
      var.push_back(0);
      var.push_back(100 * 4);
      break;
    case SPECIAL_ARBREBOSS:
      var.push_back(50);  // time before a salvo
      var.push_back(0);   // salvo id
      var.push_back(0);   // arrow witch is throw
      var.push_back(0);   // time to wait before throwing an arrow.
      break;
    case SPECIAL_WIND:
      break;
    case SPECIAL_END:
      var.push_back(0);
      var.push_back(0);
      var.push_back(60);
      break;
    case SPECIAL_END2:
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      break;
    case SPECIAL_ACC:
      var.push_back(0);
      break;
  }
}

void Special::Step(Level& level) {
  if (erased) return;
  switch (m) {
    case SPECIAL_ACC: {
      int& t = var[0];
      t = t + 1;
      // clang format off
      level.particule_list.push_front(accParticule( 318 + 16 + sin(t / 15.) * 4, 1152 + 32, -2 * sin(t / 15.), 60));
      level.particule_list.push_front(accParticule( 510 + 16 + sin(t / 15.) * 4, 1088 + 32, -2 * sin(t / 15.), 90));
      level.particule_list.push_front(accParticule( 330 + 16 + sin(t / 15.) * 4, 928 + 32, -2 * sin(t / 15.), 110));
      level.particule_list.push_front(accParticule( 70 + 16 + sin(t / 15.) * 4, 832 + 32, -2 * sin(t / 15.), 110));
      level.particule_list.push_front(accParticule( 70 + 16 + sin(t / 15.) * 4, 512 + 32, -2 * sin(t / 15.), 90));
      level.particule_list.push_front(accParticule( 288 + 16 + sin(t / 15.) * 4, 352 + 32, -2 * sin(t / 15.), 90));
      level.particule_list.push_front(accParticule( 480 + 16 + sin(t / 15.) * 4, 896 + 32, -2 * sin(t / 15.), 130));
      // clang format on
    } break;
    case SPECIAL_ARBRE: {
      int x = level.hero_list[0].x;
      int y = level.hero_list[0].y;
      int& time = var[0];
      int& mode = var[1];
      int& size = var[2];
      if (mode == 0) {
        if ((768 - x) * (768 - x) + (416 - y) * (416 - y) < 40 * 40) {
          time++;
          if (time > 60) {
            level.drawn_textpopup_list.push_back(TextPopup(2));
            mode = 1;
            time = 0;
          }
        } else if (time > 0)
          time--;
      } else {
        time++;
        if (time > 15) {
          size *= 0.98;
          level.hero_list[0].sprite.SetScale(size / 100.0, size / 100.0);
          level.hero_list[0].x += (768 - x) *0.01;
          level.hero_list[0].geometry.bottom =
          level.hero_list[0].geometry.top + 24 * (size + 10) / 110.0;
        }
        if (size < 3) {
          level.isWin = true;
        }
      }
    } break;

    case SPECIAL_ARBRE2: {
      int& time = var[0];
      int& size = var[1];
      time++;
      level.hero_list[0].sprite.SetScale(size / 100.0, size / 100.0);
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
      int& timeBeforeSalvo = var[0];
      int& SalvoId = var[1];
      int& i = var[2];
      int& timeWait = var[3];

      if (timeBeforeSalvo == 30) {
        smk::Sound sound;
        sound.SetBuffer(SB_boss[SalvoId]);
        level.sound_list.push_front(std::move(sound));
        (*(level.sound_list.begin())).Play();
      }

      if (timeBeforeSalvo > 0)
        timeBeforeSalvo--;
      else {
        if (timeWait <= 0) {
          timeWait = 2;
          int ii = 0;
          for(auto& arrow_launcher : level.arrowLauncher_list) {
            if (sequence[SalvoId][i] == ii) {
              level.arrow_list.push_front(
                  Arrow(arrow_launcher.x + 16, arrow_launcher.y + 16,
                        17 * cos(arrow_launcher.orientation * .0174532925),
                        -17 * sin(arrow_launcher.orientation * .0174532925)));
              arrow_launcher.sound.Play();
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
      for (std::list<Button>::iterator itbouton = level.button_list.begin();
           itbouton != level.button_list.end(); ++itbouton) {
        if (itbouton->nb_pressed == itbouton->nb_pressed_required - 1) {
          int xx =
              posFireX[bougieIndex] - 5 * sin(timeBeforeSalvo / 100.0 * 3.14);
          int yy = posFireY[bougieIndex];
          nbFire++;
          for (int h = 0; h < 4; h++)
            level.particule_list.push_front(fireParticule(xx, yy));
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
              level.particule_list.push_front(
                  arbreBossParticule(x + 517, y + 300, c));
            }
          }
        erased = true;
      }

      // destruct Hero
      for (std::vector<Hero>::iterator itHero = level.hero_list.begin();
           itHero != level.hero_list.end(); ++itHero) {
        Rectangle r(640 - 100, 640, 480, 480 - 100);
        if (IsCollision(itHero->geometry, r)) {
          itHero->life = -1;
          break;
        }
      }
    } break;

    case SPECIAL_WIND: {
      for (int i = 0; i < 6; i++) {
        level.particule_list.push_front(
            particuleWind(112 + rand() % 176, 335 + rand() % 17));
        level.particule_list.push_front(
            particuleWind(562 + rand() % 174, 466 + rand() % 14));
      }

    } break;
    case SPECIAL_END: {
      int& t = var[0];
      int& t2 = var[1];
      int& t3 = var[2];

      Rectangle rect(301, 301 + 32, 160, 160 + 41);
      for (std::vector<Hero>::iterator ithero = level.hero_list.begin();
           ithero != level.hero_list.end(); ++ithero) {
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
          level.isWin = true;
      }
      if (t > 0) {
        if (t2 <= 0) {
          smk::Sound sound;
          sound.SetBuffer(SB_start);
          sound.Play();
          level.sound_list.push_front(std::move(sound));
          t2 = t3;
          t3 = 4 + (t3 - 4) * 0.9;
        } else {
          t2--;
        }
      }
    } break;
  }
}

void Special::DrawBackground(smk::Window& window,
                             float xcenter,
                             float ycenter) {
  if (erased) return;
  if (m == SPECIAL_ARBRE2) {
    smk::Sprite sprite;
    sprite.SetTexture(img_arbre_texture);
    // clang-format off
    for (int x = xcenter - 320 - int(xcenter / 2.67) % 340; x < xcenter + 320; x += 340)
    for (int y = ycenter - 240 - int(ycenter / 2.67) % 340; y < ycenter + 240; y += 340) {
      sprite.SetPosition(x, y);
      window.Draw(sprite);
    }
    // clang-format on
  }
}

void Special::DrawOverDecoration(smk::Window& window) {
  if (erased) return;
  if (m == SPECIAL_END) {
    int t = var[0];
    smk::Sprite spr;
    spr.SetTexture(img_arbreDecorsEndBack2);
    spr.SetColor(glm::vec4(1.0, 1.0, 1.0, t / 255.f));
    window.Draw(spr);
  }
}

void Special::DrawForeground(smk::Window& window, bool& isWin) {
  if (erased) return;
  switch (m) {
    case SPECIAL_ARBREBOSS: {
      float timesalvo = var[0];
      // Draw the sapin
      smk::Sprite spr;
      spr.SetTexture(img_sapin);
      spr.SetPosition(520, 303);
      spr.Move(-3 * sin(timesalvo / 100.0 * 3.14), 0);
      window.Draw(spr);

      float angle1 = 270 - 180 * sin(timesalvo / 100.0 * (3.14));
      float angle2 = angle1 * angle1 / 300;

      // Draw the sapin_arm
      spr.SetTexture(img_sapin_bras);
      spr.SetCenter(10, 9);

      spr.SetPosition(520 + 45, 303 + 86);
      spr.SetRotation(angle1);
      window.Draw(spr);

      spr.Move(30 * cos(angle1 * 0.0174532925),
               -30 * sin(angle1 * 0.0174532925));
      spr.SetRotation(angle2);
      window.Draw(spr);

    } break;
    case SPECIAL_END2: {
      int& t = var[0];
      int& pos = var[1];
      int& mode = var[2];
      int& pos2 = var[3];
      int& alpha = var[4];
      int& color = var[5];

      if (t > 254) {
        switch (mode) {
          case 0:
            pos += (400.0 - pos) / 30.0;
            if ((400 - pos) < 30) {
              if (window.input().IsKeyHold(GLFW_KEY_SPACE)) {
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
              if (window.input().IsKeyHold(GLFW_KEY_SPACE))
                isWin = true;
              color = 255;
            }
        }
      } else {
        t++;
      }

      // focus
      auto rect = smk::Shape::Square();
      rect.SetScale(6400,4800);
      rect.SetColor({0, 0, 0, t / 2 / 255});
      window.Draw(rect);

      // tree
      smk::Sprite spr;
      spr.SetPosition(700, 348);
      spr.SetTexture(img_arbre);
      window.Draw(spr);

      spr.SetTexture(img_arbre_white);
      spr.SetBlendMode(smk::BlendMode::Add);
      spr.SetColor(glm::vec4(1.0, 1.0, 1.0, t / 255.f));
      window.Draw(spr);

      if (pos > 0) {
        smk::Sprite spr;
        spr.SetTexture(img_endPanel);
        spr.SetPosition(960 - 640 - 360 + pos, 0 + pos2);
        window.Draw(spr);

        smk::Text str[7];
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
          window.Draw(str[i]);
          str[i].Move(0, 1);
          str[i].SetColor(glm::vec4(60, 60, 60, 255) / 255.f);
          window.Draw(str[i]);
        }

        smk::Sprite sprCredit;
        sprCredit.SetTexture(img_credit);
        sprCredit.SetPosition(960 - 640, 0);
        sprCredit.SetColor(glm::vec4(color, color, color, alpha) / 255.f);
        window.Draw(sprCredit);
      }

    } break;
  }
}
