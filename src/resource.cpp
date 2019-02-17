#include "TextureManager.hpp"
#include "resource.hpp"

// images
GLuint img_background;
GLuint img_block;
GLuint img_block1;
GLuint img_block2;
GLuint img_block3;
GLuint img_block4;
GLuint img_hero_left;
GLuint img_hero_right;
GLuint img_turret;
GLuint img_glass;
GLuint img_electricitySupport;
GLuint img_cloneur;
GLuint img_miroir;
GLuint img_coeur;
GLuint img_creeper;
GLuint img_arrow;
GLuint img_arrowLauncher;
GLuint img_oeil;
GLuint img_arbre;
GLuint img_arbre_white;
GLuint img_pincette;
GLuint img_ouvertureEffect;
GLuint img_arbre_texture;
GLuint img_trou;
GLuint img_couchetrou;
GLuint img_arbreDecorsFront;
GLuint img_arbreDecorsBack;
GLuint img_arbreDecors2Front;
GLuint img_arbreDecors2Back;
GLuint img_arbreDecors3Front;
GLuint img_arbreDecors4Back;
GLuint img_arbreDecors4Front;
GLuint img_arbreDecors5Front;
GLuint img_arbreDecors6Front;
GLuint img_arbreDecorsBossFront;
GLuint img_arbreDecorsEndFront;
GLuint img_arbreDecorsEndBack1;
GLuint img_arbreDecorsEndBack2;
GLuint img_sapin;
GLuint img_sapin_bras;
GLuint img_button[4];
GLuint img_endPanel;
GLuint img_credit;
GLuint img_accueil;

GLuint img_pic;
// interface
GLuint img_cadreInput;
GLuint img_deleteButton;
GLuint img_newGame;
GLuint img_frenchFlag;
GLuint img_englishFlag;
GLuint img_deutschFlag;

// particule
GLuint img_particule_smoothRound;
GLuint img_particule_etincelles;
GLuint img_particule_bubble;
GLuint img_particule_explosion;
GLuint img_particule_arrow;
GLuint img_particule_fire;
GLuint img_particule_pixel;
GLuint img_particule_line;
GLuint img_particule_p;
// decor GLuint
GLuint img_decorLampe;
GLuint img_decorSpace;
GLuint img_decorDirectionnelles;
GLuint img_decorPilier;
GLuint img_decorPlateforme6432;
GLuint img_decorPlateforme9632;
GLuint img_decorGlass;
GLuint img_decorSupport;
GLuint img_pipe;
GLuint img_decorNoisette;
GLuint img_tuyau;

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
  img_block = manager.loadTexture("img/img_block.jpg");
  img_block1 = manager.loadTexture("img/img_block1.png");
  img_block2 = manager.loadTexture("img/img_block2.png");
  img_block3 = manager.loadTexture("img/img_block3.png");
  img_block4 = manager.loadTexture("img/img_block4.png");
  img_hero_left = manager.loadTexture("img/img_hero_left.png");
  img_hero_right = manager.loadTexture("img/img_hero_right.png");
  img_background = manager.loadTexture("img/img_background.jpg");
  img_turret = manager.loadTexture("img/img_turret.png");
  img_glass = manager.loadTexture("img/img_glass.png");
  img_electricitySupport = manager.loadTexture("img/electricitySupport.png");
  img_particule_smoothRound = manager.loadTexture("img/img_particule_smoothRound.png");
  img_particule_etincelles = manager.loadTexture("img/img_particule_etincelles.png");
  img_particule_fire = manager.loadTexture("img/img_particule_fire.png");
  img_cloneur = manager.loadTexture("img/img_cloneur.png");
  img_particule_bubble = manager.loadTexture("img/img_particule_bubble.png");
  img_particule_explosion = manager.loadTexture("img/img_particule_explosion.png");
  img_particule_pixel = manager.loadTexture("img/img_particule_pixel.png");
  img_particule_line = manager.loadTexture("img/img_particule_line.png");
  img_particule_arrow = manager.loadTexture("img/img_particule_arrow.png");
  img_particule_p = manager.loadTexture("img/img_particule_p.png");
  img_miroir = manager.loadTexture("img/img_miroir.png");
  img_coeur = manager.loadTexture("img/img_coeur.png");
  img_creeper = manager.loadTexture("img/img_creeper.png");
  img_arrow = manager.loadTexture("img/img_arrow.png");
  img_arrowLauncher = manager.loadTexture("img/img_arrowLauncher.png");
  img_pic = manager.loadTexture("img/img_pic.png");
  img_oeil = manager.loadTexture("img/img_oeil.png");
  img_arbre = manager.loadTexture("img/img_arbre.png");
  img_arbre_white = manager.loadTexture("img/img_arbre_white.png");
  img_pincette = manager.loadTexture("img/img_pincette.png");
  img_ouvertureEffect = manager.loadTexture("img/img_ouvertureEffect.png");
  img_arbre_texture = manager.loadTexture("img/img_arbre_texture.png");
  img_trou = manager.loadTexture("img/img_trou.png");
  img_couchetrou = manager.loadTexture("img/img_couchetrou.png");
  img_endPanel = manager.loadTexture("img/img_endPanel.png");
  img_arbreDecorsFront = manager.loadTexture("img/decors/arbreDecorsFront.png");
  img_arbreDecorsBack = manager.loadTexture("img/decors/arbreDecorsBack.png");
  img_arbreDecors2Front = manager.loadTexture("img/decors/arbreDecors2Front.png");
  img_arbreDecors2Back = manager.loadTexture("img/decors/arbreDecors2Back.png");
  img_arbreDecors3Front = manager.loadTexture("img/decors/arbreDecors3Front.png");
  img_arbreDecors4Back = manager.loadTexture("img/decors/arbreDecors4Back.png");
  img_arbreDecors4Front = manager.loadTexture("img/decors/arbreDecors4Front.png");
  img_arbreDecors5Front = manager.loadTexture("img/decors/arbreDecors5Front.png");
  img_arbreDecors6Front = manager.loadTexture("img/decors/arbreDecors6Front.png");
  img_arbreDecorsBossFront = manager.loadTexture("img/decors/arbreDecorsBossFront.png");
  img_arbreDecorsEndFront = manager.loadTexture("img/decors/endFront.png");
  img_arbreDecorsEndBack1 = manager.loadTexture("img/decors/endBack.png");
  img_arbreDecorsEndBack2 = manager.loadTexture("img/decors/endBack2.png");
  img_sapin = manager.loadTexture("img/img_sapin.png");
  img_sapin_bras = manager.loadTexture("img/img_sapin_bras.png");
  img_button[0] = manager.loadTexture("img/img_button1.png");
  img_button[1] = manager.loadTexture("img/img_button2.png");
  img_button[2] = manager.loadTexture("img/img_button3.png");
  img_button[3] = manager.loadTexture("img/img_button4.png");
  img_credit = manager.loadTexture("img/img_credit.png");
  img_accueil = manager.loadTexture("img/img_accueil.png");
  img_cadreInput = manager.loadTexture("img/cadreInput.png");
  img_deleteButton = manager.loadTexture("img/deleteButton.png");
  img_newGame = manager.loadTexture("img/newGame.png");
  img_frenchFlag = manager.loadTexture("img/img_frenchFlag.png");
  img_englishFlag = manager.loadTexture("img/img_englishFlag.png");
  img_deutschFlag = manager.loadTexture("img/img_deutschFlag.png");
  img_decorLampe = manager.loadTexture("img/img_lampe.png");
  img_decorSpace = manager.loadTexture("img/img_space.png");
  img_decorDirectionnelles = manager.loadTexture("img/img_toucheDirectionnelles.png");
  img_decorPilier = manager.loadTexture("img/img_decorPilier.png");
  img_decorPlateforme6432 =
      manager.loadTexture("img/img_decorPlateforme6432.png");
  img_decorPlateforme9632 =
      manager.loadTexture("img/img_decorPlateforme9632.png");
  img_decorGlass = manager.loadTexture("img/img_decorGlass.png");
  img_decorSupport = manager.loadTexture("img/img_decorSupport.png");
  img_pipe = manager.loadTexture("img/img_pipe.png");
  img_decorNoisette = manager.loadTexture("img/img_decorNoisette.png");
  img_tuyau = manager.loadTexture("img/img_tuyau.png");

  // initialisation of SoundBuffer
  //SB_electricity = manager.loadTexture("snd/electricity.ogg");
  //SB_explosion = manager.loadTexture("snd/explosion.ogg");
  //SB_arrowLauncher = manager.loadTexture("snd/arrowLauncher.ogg");
  //SB_boss[0] = manager.loadTexture("snd/bossSound1.ogg");
  //SB_boss[1] = manager.loadTexture("snd/bossSound2.ogg");
  //SB_boss[2] = manager.loadTexture("snd/bossSound3.ogg");
  //SB_boss[3] = manager.loadTexture("snd/bossSound4.ogg");
  //SB_start = manager.loadTexture("snd/start.ogg");
  // initialisation of the RenderWindow
  // screen.Create (sf::VideoMode(640,480, 32), "In the Cube");
  // screen.SetFramerateLimit(30);
  // screen.UseVerticalSync(true);
}
