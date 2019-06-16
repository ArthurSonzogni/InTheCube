#ifndef __NIVEAU_H__
#define __NIVEAU_H__

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <string>

#include <smk/Screen.hpp>
#include <smk/View.hpp>
#include <smk/Sound.hpp>
#include "Accelerator.hpp"
#include "Arrow.hpp"
#include "ArrowLauncher.hpp"
#include "ArrowLauncherDetector.hpp"
#include "Block.hpp"
#include "Button.hpp"
#include "Cloner.hpp"
#include "Collision.hpp"
#include "Creeper.hpp"
#include "Decor.hpp"
#include "Detector.hpp"
#include "Electricity.hpp"
#include "FallingBlock.hpp"
#include "FinishBlock.hpp"
#include "Forme.hpp"
#include "Glass.hpp"
#include "Hero.hpp"
#include "InvisibleBlock.hpp"
#include "Laser.hpp"
#include "LaserTurret.hpp"
#include "MovableBlock.hpp"
#include "MovingBlock.hpp"
#include "Particule.hpp"
#include "Pic.hpp"
#include "Pincette.hpp"
#include "Special.hpp"
#include "StaticMirror.hpp"
#include "Teleporter.hpp"
#include "TextPopup.hpp"

class Level {
 public:
  Level();
  ~Level();

  // 1. Populate the level with objects.
  void LoadFromFile(std::string fileName);

  // 2. Advance in the simulation. 30 times per secondes.
  void Step(smk::Screen& screen);

  // 3. Draw the current state of the level.
  void Draw(smk::Screen& screen);

  bool isPrevious = false;
  bool isWin = false;
  bool isLose = false;
  bool isEscape = false;

 private:
  friend Special;
  std::list<Accelerator> accelerator_list;
  std::list<Arrow> arrow_list;
  std::list<Button> button_list;
  std::list<Particule> particule_list;
  std::list<Special> special_list;
  std::list<TextPopup> textpopup_list;
  std::list<TextPopup> drawn_textpopup_list;
  std::vector<ArrowLauncher> arrowLauncher_list;
  std::vector<ArrowLauncherDetector> arrowLauncherDetector_list;
  std::vector<Block> block_list;
  std::vector<Cloner> cloneur_list;
  std::vector<Creeper> creeper_list;
  std::vector<Decor> decorBack_list;
  std::vector<Decor> decorFront_list;
  std::vector<Detector> detector_list;
  std::vector<Electricity> electricity_list;
  std::vector<FallingBlock> fallBlock_list;
  std::vector<Glass> glassBlock_list;
  std::vector<InvisibleBlock> invBlock_list;
  std::vector<LaserTurret> laserTurret_list;
  std::vector<MovableBlock> movableBlock_list;
  std::vector<MovingBlock> movBlock_list;
  std::vector<Pic> pic_list;
  std::vector<Pincette> pincette_list;
  std::vector<StaticMirror> staticMiroir_list;
  std::vector<Teleporter> teleporter_list;

  FinishBlock enddingBlock;

  smk::Sprite spriteBackground;
  std::vector<Hero> hero_list;
  int heroSelected;
  int nbHero;

  bool fluidViewEnable;
  int time;
  int timeDead;

  std::list<smk::Sound> sound_list;

  // View view;
  float xcenter, ycenter;
  float viewXMin, viewYMin, viewXMax, viewYMax;
  smk::View view_;
  void SetView();

  bool CollisionWithAllBlock(Rectangle geom);
  bool CollisionWithAllBlock(Line l);
  bool CollisionWithAllBlock(Point p);
  bool PlaceFree(const Hero& h, float x, float y);
  bool PlaceFree(const MovingBlock& m, float x, float y);
  bool PlaceFree(const FallingBlock& m, float x, float y);
  bool PlaceFree(const MovableBlock& m, float x, float y);
  bool PlaceFree(const Glass& m, float x, float y);

  void EmitLaser(smk::Screen& screen,
                 float x,
                 float y,
                 float angle,
                 int recursiveMaxLevel = 30);
  std::list<Laser> laser_;

  static smk::Sound back_music_;
  static int back_music_users_;
};

#endif /* __NIVEAU_H__ */
