#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <smk/Sound.hpp>
#include <smk/View.hpp>
#include <smk/Window.hpp>
#include "game/Accelerator.hpp"
#include "game/Arrow.hpp"
#include "game/ArrowLauncher.hpp"
#include "game/ArrowLauncherDetector.hpp"
#include "game/Block.hpp"
#include "game/Button.hpp"
#include "game/Cloner.hpp"
#include "game/Collision.hpp"
#include "game/Creeper.hpp"
#include "game/Decor.hpp"
#include "game/Detector.hpp"
#include "game/Electricity.hpp"
#include "game/FallingBlock.hpp"
#include "game/FinishBlock.hpp"
#include "game/Forme.hpp"
#include "game/Glass.hpp"
#include "game/Hero.hpp"
#include "game/InvisibleBlock.hpp"
#include "game/Laser.hpp"
#include "game/LaserTurret.hpp"
#include "game/MovableBlock.hpp"
#include "game/MovingBlock.hpp"
#include "game/Particule.hpp"
#include "game/Pic.hpp"
#include "game/Pincette.hpp"
#include "game/Special.hpp"
#include "game/StaticMirror.hpp"
#include "game/Teleporter.hpp"
#include "game/TextPopup.hpp"

struct Input {
  enum T {
    None = 0,
    Left = 1,
    Right = 2,
    Up = 4,
    Space = 8,
    Escape = 16,
    Restart = 32,
  };
};

class Level {
 public:
  Level() = default;
  ~Level() = default;

  // 1. Populate the level with objects.
  void LoadFromFile(std::string fileName);

  // 2. Advance in the simulation. 30 times per secondes.
  void Step(Input::T input, smk::Window& window);

  // 3. Draw the current state of the level.
  void Draw(smk::Window& window);

  // Output:
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
  std::vector<Hero> hero_list;

  FinishBlock enddingBlock;

  smk::Sprite spriteBackground;
  int heroSelected = 0;
  int nbHero = 0;
  bool fluidViewEnable = true;
  int time = 0;
  int timeDead = 0;

  std::list<smk::Sound> sound_list;

  // View view;
  float xcenter, ycenter;
  float viewXMin, viewYMin, viewXMax, viewYMax;
  smk::View view_;
  void SetView(smk::Window& window);

  bool CollisionWithAllBlock(Rectangle geom);
  bool CollisionWithAllBlock(Line l);
  bool CollisionWithAllBlock(Point p);
  bool PlaceFree(const Hero& h, float x, float y);
  bool PlaceFree(const MovingBlock& m, float x, float y);
  bool PlaceFree(const FallingBlock& m, float x, float y);
  bool PlaceFree(const MovableBlock& m, float x, float y);
  bool PlaceFree(const Glass& m, float x, float y);

  void EmitLaser(smk::Window& window,
                 float x,
                 float y,
                 float angle,
                 int recursiveMaxLevel = 30);
  std::list<Laser> laser_;
};

#endif /* GAME_LEVEL_HPP */
