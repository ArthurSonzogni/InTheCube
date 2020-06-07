// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Resource.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <smk/SoundBuffer.hpp>
#include <smk/Texture.hpp>
#include <vector>

std::string GetEnvironmentVariable(const char* env) {
  auto value = std::getenv(env);
  if (value)
    return value;
  return std::string();
}

std::string ResourcePath() {
  static bool initialized = false;
  static std::string resource_path;
  if (initialized)
    return resource_path;
  initialized = true;

  auto SNAP = GetEnvironmentVariable("SNAP");

  std::vector<std::string> path_list = {
      // Application installed using snapcraft.
      SNAP + "/share/inthecube/resources",

      // Application installed using "sudo make install"
      "/usr/share/inthecube/resources",
      "/usr/local/share/inthecube/resources",

      // Code build and run inside ${CMAKE_CURRENT_DIRECTORY}/build
      "../resources",

      // Code build and run inside ${CMAKE_CURRENT_DIRECTORY}
      "../resources",

      // Code build for WebAssembly.
      "/resources",
  };

  for (auto& path : path_list) {
    std::ifstream file(path + "/inthecube");
    std::string line;
    if (std::getline(file, line) && line == "inthecube") {
      resource_path = path;
    }
  }

  std::cerr << "Resource path = " << resource_path << std::endl;
  return resource_path;
}

std::string SavePath() {
  static bool initialized = false;
  static std::string save_path;

  if (initialized)
    return save_path;
  initialized = true;

#ifdef __EMSCRIPTEN__
  save_path = "/sav";
  return save_path;
#endif

  auto SNAP_USER_COMMON = GetEnvironmentVariable("SNAP_USER_COMMON");
  auto HOME = GetEnvironmentVariable("HOME");

  if (!SNAP_USER_COMMON.empty()) {
    save_path = SNAP_USER_COMMON;
  } else if (!HOME.empty()) {
    save_path = HOME + "/.config/inthecube";
  } else {
    save_path = ".";
  }

  std::cerr << "Save path = " << save_path << std::endl;
  return save_path;
}

// Font
smk::Font font_arial;

// images
smk::Texture img_background;
smk::Texture img_block;
smk::Texture img_block1;
smk::Texture img_block2;
smk::Texture img_block3;
smk::Texture img_block4;
smk::Texture img_hero_left;
smk::Texture img_hero_right;
smk::Texture img_turret;
smk::Texture img_glass;
smk::Texture img_electricitySupport;
smk::Texture img_cloneur;
smk::Texture img_miroir;
smk::Texture img_coeur;
smk::Texture img_creeper;
smk::Texture img_arrow;
smk::Texture img_arrowLauncher;
smk::Texture img_oeil;
smk::Texture img_arbre;
smk::Texture img_arbre_white;
smk::Texture img_pincette;
smk::Texture img_ouvertureEffect;
smk::Texture img_arbre_texture;
smk::Texture img_trou;
smk::Texture img_couchetrou;
smk::Texture img_arbreDecorsFront;
smk::Texture img_arbreDecorsBack;
smk::Texture img_arbreDecors2Front;
smk::Texture img_arbreDecors2Back;
smk::Texture img_arbreDecors3Front;
smk::Texture img_arbreDecors4Back;
smk::Texture img_arbreDecors4Front;
smk::Texture img_arbreDecors5Front;
smk::Texture img_arbreDecors6Front;
smk::Texture img_arbreDecorsBossFront;
smk::Texture img_arbreDecorsEndFront;
smk::Texture img_arbreDecorsEndBack1;
smk::Texture img_arbreDecorsEndBack2;
smk::Texture img_sapin;
smk::Texture img_sapin_bras;
smk::Texture img_button[4];
smk::Texture img_endPanel;
smk::Texture img_credit;
smk::Texture img_accueil;

smk::Texture img_pic;
// interface
smk::Texture img_cadreInput;
smk::Texture img_deleteButton;
smk::Texture img_newGame;
smk::Texture img_frenchFlag;
smk::Texture img_englishFlag;
smk::Texture img_deutschFlag;

// particule
smk::Texture img_particule_smoothRound;
smk::Texture img_particule_etincelles;
smk::Texture img_particule_bubble;
smk::Texture img_particule_explosion;
smk::Texture img_particule_arrow;
smk::Texture img_particule_fire;
smk::Texture img_particule_pixel;
smk::Texture img_particule_line;
smk::Texture img_particule_p;

// decor Texture
smk::Texture img_decorLampe;
smk::Texture img_decorSpace;
smk::Texture img_decorDirectionnelles;
smk::Texture img_decorPilier;
smk::Texture img_decorPlateforme6432;
smk::Texture img_decorPlateforme9632;
smk::Texture img_decorGlass;
smk::Texture img_decorSupport;
smk::Texture img_pipe;
smk::Texture img_decorNoisette;
smk::Texture img_tuyau;

// music
smk::SoundBuffer SB_electricity;
smk::SoundBuffer SB_explosion;
smk::SoundBuffer SB_arrowLauncher;
smk::SoundBuffer SB_boss[4];
smk::SoundBuffer SB_backgroundMusic;
smk::SoundBuffer SB_backgroundMusicAction;
smk::SoundBuffer SB_start;
smk::SoundBuffer SB_end;
smk::SoundBuffer SB_intro;

std::map<smk::Font*, std::string> font_resources{
    {&font_arial, "/font/arial.ttf"},
};

std::map<smk::Texture*, std::string> image_resources{
    {&img_block, "/img/img_block.jpg"},
    {&img_block1, "/img/img_block1.png"},
    {&img_block2, "/img/img_block2.png"},
    {&img_block3, "/img/img_block3.png"},
    {&img_block4, "/img/img_block4.png"},
    {&img_hero_left, "/img/img_hero_left.png"},
    {&img_hero_right, "/img/img_hero_right.png"},
    {&img_background, "/img/img_background.jpg"},
    {&img_turret, "/img/img_turret.png"},
    {&img_glass, "/img/img_glass.png"},
    {&img_electricitySupport, "/img/electricitySupport.png"},
    {&img_particule_smoothRound, "/img/img_particule_smoothRound.png"},
    {&img_particule_etincelles, "/img/img_particule_etincelles.png"},
    {&img_particule_fire, "/img/img_particule_fire.png"},
    {&img_cloneur, "/img/img_cloneur.png"},
    {&img_particule_bubble, "/img/img_particule_bubble.png"},
    {&img_particule_explosion, "/img/img_particule_explosion.png"},
    {&img_particule_pixel, "/img/img_particule_pixel.png"},
    {&img_particule_line, "/img/img_particule_line.png"},
    {&img_particule_arrow, "/img/img_particule_arrow.png"},
    {&img_particule_p, "/img/img_particule_p.png"},
    {&img_miroir, "/img/img_miroir.png"},
    {&img_coeur, "/img/img_coeur.png"},
    {&img_creeper, "/img/img_creeper.png"},
    {&img_arrow, "/img/img_arrow.png"},
    {&img_arrowLauncher, "/img/img_arrowLauncher.png"},
    {&img_pic, "/img/img_pic.png"},
    {&img_oeil, "/img/img_oeil.png"},
    {&img_arbre, "/img/img_arbre.png"},
    {&img_arbre_white, "/img/img_arbre_white.png"},
    {&img_pincette, "/img/img_pincette.png"},
    {&img_ouvertureEffect, "/img/img_ouvertureEffect.png"},
    {&img_arbre_texture, "/img/img_arbre_texture.png"},
    {&img_trou, "/img/img_trou.png"},
    {&img_couchetrou, "/img/img_couchetrou.png"},
    {&img_endPanel, "/img/img_endPanel.png"},
    {&img_arbreDecorsFront, "/img/decors/arbreDecorsFront.png"},
    {&img_arbreDecorsBack, "/img/decors/arbreDecorsBack.png"},
    {&img_arbreDecors2Front, "/img/decors/arbreDecors2Front.png"},
    {&img_arbreDecors2Back, "/img/decors/arbreDecors2Back.png"},
    {&img_arbreDecors3Front, "/img/decors/arbreDecors3Front.png"},
    {&img_arbreDecors4Back, "/img/decors/arbreDecors4Back.png"},
    {&img_arbreDecors4Front, "/img/decors/arbreDecors4Front.png"},
    {&img_arbreDecors5Front, "/img/decors/arbreDecors5Front.png"},
    {&img_arbreDecors6Front, "/img/decors/arbreDecors6Front.png"},
    {&img_arbreDecorsBossFront, "/img/decors/arbreDecorsBossFront.png"},
    {&img_arbreDecorsEndFront, "/img/decors/endFront.png"},
    {&img_arbreDecorsEndBack1, "/img/decors/endBack.png"},
    {&img_arbreDecorsEndBack2, "/img/decors/endBack2.png"},
    {&img_sapin, "/img/img_sapin.png"},
    {&img_sapin_bras, "/img/img_sapin_bras.png"},
    {&img_button[0], "/img/img_button1.png"},
    {&img_button[1], "/img/img_button2.png"},
    {&img_button[2], "/img/img_button3.png"},
    {&img_button[3], "/img/img_button4.png"},
    {&img_credit, "/img/img_credit.png"},
    {&img_accueil, "/img/img_accueil.png"},
    {&img_cadreInput, "/img/cadreInput.png"},
    {&img_deleteButton, "/img/deleteButton.png"},
    {&img_newGame, "/img/newGame.png"},
    {&img_frenchFlag, "/img/img_frenchFlag.png"},
    {&img_englishFlag, "/img/img_englishFlag.png"},
    {&img_deutschFlag, "/img/img_deutschFlag.png"},
    {&img_decorLampe, "/img/img_lampe.png"},
    {&img_decorSpace, "/img/img_space.png"},
    {&img_decorDirectionnelles, "/img/img_toucheDirectionnelles.png"},
    {&img_decorPilier, "/img/img_decorPilier.png"},
    {&img_decorPlateforme6432, "/img/img_decorPlateforme6432.png"},
    {&img_decorPlateforme9632, "/img/img_decorPlateforme9632.png"},
    {&img_decorGlass, "/img/img_decorGlass.png"},
    {&img_decorSupport, "/img/img_decorSupport.png"},
    {&img_pipe, "/img/img_pipe.png"},
    {&img_decorNoisette, "/img/img_decorNoisette.png"},
    {&img_tuyau, "/img/img_tuyau.png"},
};

std::map<smk::SoundBuffer*, std::string> sound_resources{
    {&SB_electricity, "/snd/electricity.ogg"},
    {&SB_backgroundMusic, "/snd/backgroundMusic.ogg"},
    {&SB_backgroundMusicAction, "/snd/actionMusic.ogg"},
    {&SB_explosion, "/snd/explosion.ogg"},
    {&SB_arrowLauncher, "/snd/arrowLauncher.ogg"},
    {&SB_boss[0], "/snd/bossSound1.ogg"},
    {&SB_boss[1], "/snd/bossSound2.ogg"},
    {&SB_boss[2], "/snd/bossSound3.ogg"},
    {&SB_boss[3], "/snd/bossSound4.ogg"},
    {&SB_start, "/snd/start.ogg"},
    {&SB_end, "/snd/end.ogg"},
    {&SB_intro, "/snd/intro.ogg"},
};

ResourceInitializer::ResourceInitializer() {
  for (auto& it : font_resources)
    resources.emplace_back(Resource{it.first, nullptr, nullptr, &it.second});
  for (auto& it : image_resources)
    resources.emplace_back(Resource{nullptr, it.first, nullptr, &it.second});
  for (auto& it : sound_resources)
    resources.emplace_back(Resource{nullptr, nullptr, it.first, &it.second});
}

void ResourceInitializer::Resource::Load() {
  // clang-format off
  if (font) *font = smk::Font(ResourcePath() + *path, 30);
  if (texture) *texture = smk::Texture(ResourcePath() + *path);
  if (soundbuffer) *soundbuffer = smk::SoundBuffer(ResourcePath() + *path);
  // clang-format on
}
