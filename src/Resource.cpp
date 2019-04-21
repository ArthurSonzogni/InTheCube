#include "Resource.hpp"
#include <smk/Texture.hpp>
#include <smk/SoundBuffer.hpp>

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

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
smk::SoundBuffer SB_backgroundMusic;
smk::SoundBuffer SB_explosion;
smk::SoundBuffer SB_arrowLauncher;
smk::SoundBuffer SB_boss[4];
smk::SoundBuffer SB_backgroundMusicAction;
smk::SoundBuffer SB_start;

void initRessource() {
  font_arial = smk::Font(P "font/arial.ttf", 30);

  img_block = smk::Texture(P "img/img_block.jpg");
  img_block1 = smk::Texture(P "img/img_block1.png");
  img_block2 = smk::Texture(P "img/img_block2.png");
  img_block3 = smk::Texture(P "img/img_block3.png");
  img_block4 = smk::Texture(P "img/img_block4.png");
  img_hero_left = smk::Texture(P "img/img_hero_left.png");
  img_hero_right = smk::Texture(P "img/img_hero_right.png");
  img_background = smk::Texture(P "img/img_background.jpg");
  img_turret = smk::Texture(P "img/img_turret.png");
  img_glass = smk::Texture(P "img/img_glass.png");
  img_electricitySupport = smk::Texture(P "img/electricitySupport.png");
  img_particule_smoothRound =
      smk::Texture(P "img/img_particule_smoothRound.png");
  img_particule_etincelles =
      smk::Texture(P "img/img_particule_etincelles.png");
  img_particule_fire = smk::Texture(P "img/img_particule_fire.png");
  img_cloneur = smk::Texture(P "img/img_cloneur.png");
  img_particule_bubble = smk::Texture(P "img/img_particule_bubble.png");
  img_particule_explosion = smk::Texture(P "img/img_particule_explosion.png");
  img_particule_pixel = smk::Texture(P "img/img_particule_pixel.png");
  img_particule_line = smk::Texture(P "img/img_particule_line.png");
  img_particule_arrow = smk::Texture(P "img/img_particule_arrow.png");
  img_particule_p = smk::Texture(P "img/img_particule_p.png");
  img_miroir = smk::Texture(P "img/img_miroir.png");
  img_coeur = smk::Texture(P "img/img_coeur.png");
  img_creeper = smk::Texture(P "img/img_creeper.png");
  img_arrow = smk::Texture(P "img/img_arrow.png");
  img_arrowLauncher = smk::Texture(P "img/img_arrowLauncher.png");
  img_pic = smk::Texture(P "img/img_pic.png");
  img_oeil = smk::Texture(P "img/img_oeil.png");
  img_arbre = smk::Texture(P "img/img_arbre.png");
  img_arbre_white = smk::Texture(P "img/img_arbre_white.png");
  img_pincette = smk::Texture(P "img/img_pincette.png");
  img_ouvertureEffect = smk::Texture(P "img/img_ouvertureEffect.png");
  img_arbre_texture = smk::Texture(P "img/img_arbre_texture.png");
  img_trou = smk::Texture(P "img/img_trou.png");
  img_couchetrou = smk::Texture(P "img/img_couchetrou.png");
  img_endPanel = smk::Texture(P "img/img_endPanel.png");
  img_arbreDecorsFront = smk::Texture(P "img/decors/arbreDecorsFront.png");
  img_arbreDecorsBack = smk::Texture(P "img/decors/arbreDecorsBack.png");
  img_arbreDecors2Front = smk::Texture(P "img/decors/arbreDecors2Front.png");
  img_arbreDecors2Back = smk::Texture(P "img/decors/arbreDecors2Back.png");
  img_arbreDecors3Front = smk::Texture(P "img/decors/arbreDecors3Front.png");
  img_arbreDecors4Back = smk::Texture(P "img/decors/arbreDecors4Back.png");
  img_arbreDecors4Front = smk::Texture(P "img/decors/arbreDecors4Front.png");
  img_arbreDecors5Front = smk::Texture(P "img/decors/arbreDecors5Front.png");
  img_arbreDecors6Front = smk::Texture(P "img/decors/arbreDecors6Front.png");
  img_arbreDecorsBossFront =
      smk::Texture(P "img/decors/arbreDecorsBossFront.png");
  img_arbreDecorsEndFront = smk::Texture(P "img/decors/endFront.png");
  img_arbreDecorsEndBack1 = smk::Texture(P "img/decors/endBack.png");
  img_arbreDecorsEndBack2 = smk::Texture(P "img/decors/endBack2.png");
  img_sapin = smk::Texture(P "img/img_sapin.png");
  img_sapin_bras = smk::Texture(P "img/img_sapin_bras.png");
  img_button[0] = smk::Texture(P "img/img_button1.png");
  img_button[1] = smk::Texture(P "img/img_button2.png");
  img_button[2] = smk::Texture(P "img/img_button3.png");
  img_button[3] = smk::Texture(P "img/img_button4.png");
  img_credit = smk::Texture(P "img/img_credit.png");
  img_accueil = smk::Texture(P "img/img_accueil.png");
  img_cadreInput = smk::Texture(P "img/cadreInput.png");
  img_deleteButton = smk::Texture(P "img/deleteButton.png");
  img_newGame = smk::Texture(P "img/newGame.png");
  img_frenchFlag = smk::Texture(P "img/img_frenchFlag.png");
  img_englishFlag = smk::Texture(P "img/img_englishFlag.png");
  img_deutschFlag = smk::Texture(P "img/img_deutschFlag.png");
  img_decorLampe = smk::Texture(P "img/img_lampe.png");
  img_decorSpace = smk::Texture(P "img/img_space.png");
  img_decorDirectionnelles =
      smk::Texture(P "img/img_toucheDirectionnelles.png");
  img_decorPilier = smk::Texture(P "img/img_decorPilier.png");
  img_decorPlateforme6432 = smk::Texture(P "img/img_decorPlateforme6432.png");
  img_decorPlateforme9632 = smk::Texture(P "img/img_decorPlateforme9632.png");
  img_decorGlass = smk::Texture(P "img/img_decorGlass.png");
  img_decorSupport = smk::Texture(P "img/img_decorSupport.png");
  img_pipe = smk::Texture(P "img/img_pipe.png");
  img_decorNoisette = smk::Texture(P "img/img_decorNoisette.png");
  img_tuyau = smk::Texture(P "img/img_tuyau.png");

  // initialisation of SoundBuffer
  SB_electricity = smk::SoundBuffer(P "snd/electricity.ogg");
  SB_explosion = smk::SoundBuffer(P "snd/explosion.ogg");
  SB_arrowLauncher = smk::SoundBuffer(P "snd/arrowLauncher.ogg");
  SB_boss[0] = smk::SoundBuffer(P "snd/bossSound1.ogg");
  SB_boss[1] = smk::SoundBuffer(P "snd/bossSound2.ogg");
  SB_boss[2] = smk::SoundBuffer(P "snd/bossSound3.ogg");
  SB_boss[3] = smk::SoundBuffer(P "snd/bossSound4.ogg");
  SB_start = smk::SoundBuffer(P "snd/start.ogg");

  smk::SoundBuffer("../../SFML/examples/pong/resources/ball.wav").Play();
}
