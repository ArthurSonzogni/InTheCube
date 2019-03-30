#include "Texture.hpp"
#include "TextureManager.hpp"
#include "Resource.hpp"

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif


// Font
Font font_arial;

// images
Texture img_background;
Texture img_block;
Texture img_block1;
Texture img_block2;
Texture img_block3;
Texture img_block4;
Texture img_hero_left;
Texture img_hero_right;
Texture img_turret;
Texture img_glass;
Texture img_electricitySupport;
Texture img_cloneur;
Texture img_miroir;
Texture img_coeur;
Texture img_creeper;
Texture img_arrow;
Texture img_arrowLauncher;
Texture img_oeil;
Texture img_arbre;
Texture img_arbre_white;
Texture img_pincette;
Texture img_ouvertureEffect;
Texture img_arbre_texture;
Texture img_trou;
Texture img_couchetrou;
Texture img_arbreDecorsFront;
Texture img_arbreDecorsBack;
Texture img_arbreDecors2Front;
Texture img_arbreDecors2Back;
Texture img_arbreDecors3Front;
Texture img_arbreDecors4Back;
Texture img_arbreDecors4Front;
Texture img_arbreDecors5Front;
Texture img_arbreDecors6Front;
Texture img_arbreDecorsBossFront;
Texture img_arbreDecorsEndFront;
Texture img_arbreDecorsEndBack1;
Texture img_arbreDecorsEndBack2;
Texture img_sapin;
Texture img_sapin_bras;
Texture img_button[4];
Texture img_endPanel;
Texture img_credit;
Texture img_accueil;

Texture img_pic;
// interface
Texture img_cadreInput;
Texture img_deleteButton;
Texture img_newGame;
Texture img_frenchFlag;
Texture img_englishFlag;
Texture img_deutschFlag;

// particule
Texture img_particule_smoothRound;
Texture img_particule_etincelles;
Texture img_particule_bubble;
Texture img_particule_explosion;
Texture img_particule_arrow;
Texture img_particule_fire;
Texture img_particule_pixel;
Texture img_particule_line;
Texture img_particule_p;
// decor Texture
Texture img_decorLampe;
Texture img_decorSpace;
Texture img_decorDirectionnelles;
Texture img_decorPilier;
Texture img_decorPlateforme6432;
Texture img_decorPlateforme9632;
Texture img_decorGlass;
Texture img_decorSupport;
Texture img_pipe;
Texture img_decorNoisette;
Texture img_tuyau;

// music
// SoundBuffer SB_electricity;
// SoundBuffer SB_backgroundMusic;
// SoundBuffer SB_explosion;
// SoundBuffer SB_arrowLauncher;
// SoundBuffer SB_boss[4];
// SoundBuffer SB_backgroundMusicAction;
// SoundBuffer SB_start;

TextureManager manager;

void initRessource() {
  font_arial = Font(P"font/arial.ttf", 30);

  img_block = manager.LoadTexture(P"img/img_block.jpg");
  img_block1 = manager.LoadTexture(P"img/img_block1.png");
  img_block2 = manager.LoadTexture(P"img/img_block2.png");
  img_block3 = manager.LoadTexture(P"img/img_block3.png");
  img_block4 = manager.LoadTexture(P"img/img_block4.png");
  img_hero_left = manager.LoadTexture(P"img/img_hero_left.png");
  img_hero_right = manager.LoadTexture(P"img/img_hero_right.png");
  img_background = manager.LoadTexture(P"img/img_background.jpg");
  img_turret = manager.LoadTexture(P"img/img_turret.png");
  img_glass = manager.LoadTexture(P"img/img_glass.png");
  img_electricitySupport = manager.LoadTexture(P"img/electricitySupport.png");
  img_particule_smoothRound = manager.LoadTexture(P"img/img_particule_smoothRound.png");
  img_particule_etincelles = manager.LoadTexture(P"img/img_particule_etincelles.png");
  img_particule_fire = manager.LoadTexture(P"img/img_particule_fire.png");
  img_cloneur = manager.LoadTexture(P"img/img_cloneur.png");
  img_particule_bubble = manager.LoadTexture(P"img/img_particule_bubble.png");
  img_particule_explosion = manager.LoadTexture(P"img/img_particule_explosion.png");
  img_particule_pixel = manager.LoadTexture(P"img/img_particule_pixel.png");
  img_particule_line = manager.LoadTexture(P"img/img_particule_line.png");
  img_particule_arrow = manager.LoadTexture(P"img/img_particule_arrow.png");
  img_particule_p = manager.LoadTexture(P"img/img_particule_p.png");
  img_miroir = manager.LoadTexture(P"img/img_miroir.png");
  img_coeur = manager.LoadTexture(P"img/img_coeur.png");
  img_creeper = manager.LoadTexture(P"img/img_creeper.png");
  img_arrow = manager.LoadTexture(P"img/img_arrow.png");
  img_arrowLauncher = manager.LoadTexture(P"img/img_arrowLauncher.png");
  img_pic = manager.LoadTexture(P"img/img_pic.png");
  img_oeil = manager.LoadTexture(P"img/img_oeil.png");
  img_arbre = manager.LoadTexture(P"img/img_arbre.png");
  img_arbre_white = manager.LoadTexture(P"img/img_arbre_white.png");
  img_pincette = manager.LoadTexture(P"img/img_pincette.png");
  img_ouvertureEffect = manager.LoadTexture(P"img/img_ouvertureEffect.png");
  img_arbre_texture = manager.LoadTexture(P"img/img_arbre_texture.png");
  img_trou = manager.LoadTexture(P"img/img_trou.png");
  img_couchetrou = manager.LoadTexture(P"img/img_couchetrou.png");
  img_endPanel = manager.LoadTexture(P"img/img_endPanel.png");
  img_arbreDecorsFront = manager.LoadTexture(P"img/decors/arbreDecorsFront.png");
  img_arbreDecorsBack = manager.LoadTexture(P"img/decors/arbreDecorsBack.png");
  img_arbreDecors2Front = manager.LoadTexture(P"img/decors/arbreDecors2Front.png");
  img_arbreDecors2Back = manager.LoadTexture(P"img/decors/arbreDecors2Back.png");
  img_arbreDecors3Front = manager.LoadTexture(P"img/decors/arbreDecors3Front.png");
  img_arbreDecors4Back = manager.LoadTexture(P"img/decors/arbreDecors4Back.png");
  img_arbreDecors4Front = manager.LoadTexture(P"img/decors/arbreDecors4Front.png");
  img_arbreDecors5Front = manager.LoadTexture(P"img/decors/arbreDecors5Front.png");
  img_arbreDecors6Front = manager.LoadTexture(P"img/decors/arbreDecors6Front.png");
  img_arbreDecorsBossFront = manager.LoadTexture(P"img/decors/arbreDecorsBossFront.png");
  img_arbreDecorsEndFront = manager.LoadTexture(P"img/decors/endFront.png");
  img_arbreDecorsEndBack1 = manager.LoadTexture(P"img/decors/endBack.png");
  img_arbreDecorsEndBack2 = manager.LoadTexture(P"img/decors/endBack2.png");
  img_sapin = manager.LoadTexture(P"img/img_sapin.png");
  img_sapin_bras = manager.LoadTexture(P"img/img_sapin_bras.png");
  img_button[0] = manager.LoadTexture(P"img/img_button1.png");
  img_button[1] = manager.LoadTexture(P"img/img_button2.png");
  img_button[2] = manager.LoadTexture(P"img/img_button3.png");
  img_button[3] = manager.LoadTexture(P"img/img_button4.png");
  img_credit = manager.LoadTexture(P"img/img_credit.png");
  img_accueil = manager.LoadTexture(P"img/img_accueil.png");
  img_cadreInput = manager.LoadTexture(P"img/cadreInput.png");
  img_deleteButton = manager.LoadTexture(P"img/deleteButton.png");
  img_newGame = manager.LoadTexture(P"img/newGame.png");
  img_frenchFlag = manager.LoadTexture(P"img/img_frenchFlag.png");
  img_englishFlag = manager.LoadTexture(P"img/img_englishFlag.png");
  img_deutschFlag = manager.LoadTexture(P"img/img_deutschFlag.png");
  img_decorLampe = manager.LoadTexture(P"img/img_lampe.png");
  img_decorSpace = manager.LoadTexture(P"img/img_space.png");
  img_decorDirectionnelles = manager.LoadTexture(P"img/img_toucheDirectionnelles.png");
  img_decorPilier = manager.LoadTexture(P"img/img_decorPilier.png");
  img_decorPlateforme6432 =
      manager.LoadTexture(P"img/img_decorPlateforme6432.png");
  img_decorPlateforme9632 =
      manager.LoadTexture(P"img/img_decorPlateforme9632.png");
  img_decorGlass = manager.LoadTexture(P"img/img_decorGlass.png");
  img_decorSupport = manager.LoadTexture(P"img/img_decorSupport.png");
  img_pipe = manager.LoadTexture(P"img/img_pipe.png");
  img_decorNoisette = manager.LoadTexture(P"img/img_decorNoisette.png");
  img_tuyau = manager.LoadTexture(P"img/img_tuyau.png");

  // initialisation of SoundBuffer
  //SB_electricity = manager.LoadTexture(P"snd/electricity.ogg");
  //SB_explosion = manager.LoadTexture(P"snd/explosion.ogg");
  //SB_arrowLauncher = manager.LoadTexture(P"snd/arrowLauncher.ogg");
  //SB_boss[0] = manager.LoadTexture(P"snd/bossSound1.ogg");
  //SB_boss[1] = manager.LoadTexture(P"snd/bossSound2.ogg");
  //SB_boss[2] = manager.LoadTexture(P"snd/bossSound3.ogg");
  //SB_boss[3] = manager.LoadTexture(P"snd/bossSound4.ogg");
  //SB_start = manager.LoadTexture(P"snd/start.ogg");
  // initialisation of the RenderWindow
  // screen.Create (sf::VideoMode(640,480, 32), "In the Cube");
  // screen.SetFramerateLimit(30);
  // screen.UseVerticalSync(true);
}
