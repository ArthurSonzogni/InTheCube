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
#include "LaserTurret.hpp"
#include "MovableBlock.hpp"
#include "MovingBlock.hpp"
#include "Particule.hpp"
#include "Pic.hpp"
#include "Pincette.hpp"
#include <smk/Screen.hpp>
#include "Special.hpp"
#include "StaticMirror.hpp"
#include "Teleporter.hpp"
#include "TextPopup.hpp"
#include <smk/View.hpp>

class Level {
 public:
  std::list<Accelerator> accelerator_list;
  std::list<Arrow> arrow_list;
  std::list<Button> button_list;
  std::list<Particule> particule_list;
  std::list<Special> special_list;
  std::list<TextPopup> textpopup_list;
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
  bool isWin;
  bool isLose;
  bool isEscape;

  smk::Sprite spriteBackground;
  std::vector<Hero> hero_list;
  int heroSelected;
  int nbHero;

  int xcenter;
  int ycenter;
  bool fluidViewEnable;
  int time;
  int timeDead;

  std::list<smk::Sound> sound_list;

  // View view;
  int viewXMin, viewYMin, viewXMax, viewYMax;
  smk::View view;

  void Draw(smk::Screen& screen);
  void Step(smk::Screen& screen);
  Level();
  void LoadFromFile(std::string fileName);
  bool CollisionWithAllBlock(Rectangle geom);
  bool CollisionWithAllBlock(Line l);
  bool CollisionWithAllBlock(Point p);
  bool PlaceFree(Hero h, float x, float y);
  bool PlaceFree(MovingBlock m, float x, float y);
  bool PlaceFree(FallingBlock m, float x, float y);
  bool PlaceFree(MovableBlock m, float x, float y);
  bool PlaceFree(Glass m, float x, float y);

  void Laser(smk::Screen& screen, int x, int y, int angle, int recursiveMaxLevel = 30);
  void DrawElectricity(smk::Screen& screen, int x1, int y1, int x2, int y2);
};

#endif /* __NIVEAU_H__ */
