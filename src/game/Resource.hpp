// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_RESOURCE_HPP
#define GAME_RESOURCE_HPP

#include <list>
#include <smk/Font.hpp>
#include <smk/OpenGL.hpp>
#include <smk/SoundBuffer.hpp>
#include <smk/Texture.hpp>
#include <variant>

std::string ResourcePath();
std::string SavePath();

extern smk::Font font_arial;
extern smk::Texture img_block;
extern smk::Texture img_block1;
extern smk::Texture img_block2;
extern smk::Texture img_block3;
extern smk::Texture img_block4;
extern smk::Texture img_hero_left;
extern smk::Texture img_hero_right;
extern smk::Texture img_background;
extern smk::Texture img_turret;
extern smk::Texture img_glass;
extern smk::Texture img_electricitySupport;
extern smk::Texture img_cloneur;
extern smk::Texture img_miroir;
extern smk::Texture img_coeur;
extern smk::Texture img_creeper;
extern smk::Texture img_arrow;
extern smk::Texture img_arrowLauncher;
extern smk::Texture img_pic;
extern smk::Texture img_button[4];
extern smk::Texture img_endPanel;
extern smk::Texture img_oeil;
extern smk::Texture img_arbre;
extern smk::Texture img_arbre_white;
extern smk::Texture img_pincette;
extern smk::Texture img_ouvertureEffect;
extern smk::Texture img_arbre_texture;
extern smk::Texture img_trou;
extern smk::Texture img_couchetrou;
extern smk::Texture img_arbreDecorsFront;
extern smk::Texture img_arbreDecorsBack;
extern smk::Texture img_arbreDecors2Front;
extern smk::Texture img_arbreDecors2Back;
extern smk::Texture img_arbreDecors3Front;
extern smk::Texture img_arbreDecors4Back;
extern smk::Texture img_arbreDecors4Front;
extern smk::Texture img_arbreDecors5Front;
extern smk::Texture img_arbreDecors6Front;
extern smk::Texture img_arbreDecorsBossFront;
extern smk::Texture img_arbreDecorsEndFront;
extern smk::Texture img_arbreDecorsEndBack1;
extern smk::Texture img_arbreDecorsEndBack2;
extern smk::Texture img_sapin;
extern smk::Texture img_sapin_bras;
extern smk::Texture img_credit;
extern smk::Texture img_accueil;
extern smk::Texture img_cadreInput;
extern smk::Texture img_deleteButton;
extern smk::Texture img_newGame;
extern smk::Texture img_frenchFlag;
extern smk::Texture img_englishFlag;
extern smk::Texture img_deutschFlag;
extern smk::Texture img_decorLampe;
extern smk::Texture img_decorSpace;
extern smk::Texture img_decorDirectionnelles;
extern smk::Texture img_decorPilier;
extern smk::Texture img_decorPlateforme6432;
extern smk::Texture img_decorPlateforme9632;
extern smk::Texture img_decorGlass;
extern smk::Texture img_decorSupport;
extern smk::Texture img_pipe;
extern smk::Texture img_decorNoisette;
extern smk::Texture img_tuyau;
extern smk::Texture img_particule_smoothRound;
extern smk::Texture img_particule_etincelles;
extern smk::Texture img_particule_bubble;
extern smk::Texture img_particule_explosion;
extern smk::Texture img_particule_arrow;
extern smk::Texture img_particule_fire;
extern smk::Texture img_particule_pixel;
extern smk::Texture img_particule_line;
extern smk::Texture img_particule_p;

// list of sounds
extern smk::SoundBuffer SB_electricity;
extern smk::SoundBuffer SB_backgroundMusic;
extern smk::SoundBuffer SB_backgroundMusicAction;
extern smk::SoundBuffer SB_explosion;
extern smk::SoundBuffer SB_arrowLauncher;
extern smk::SoundBuffer SB_boss[4];
extern smk::SoundBuffer SB_start;
extern smk::SoundBuffer SB_intro;
extern smk::SoundBuffer SB_end;

class ResourceInitializer {
 public:
  ResourceInitializer();

  struct Resource {
    smk::Font* font = nullptr;
    smk::Texture* texture = nullptr;
    smk::SoundBuffer* soundbuffer = nullptr;
    std::string* path = nullptr;
    void Load();
  };
  std::list<Resource> resources;
};

#endif  // GAME_RESOURCE_HPP
