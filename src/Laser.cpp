#include "Config.hpp"
#include "Laser.hpp"
#include "Player.hpp"
#include <stdio.h>

using namespace Game;
using namespace Config::Actor::Laser;

Laser::Laser(Player *player)
    : Actor(player->GetPosX(), player->GetPosY(), player->GetOri(),
            ASPECT_RATIO * HEIGHT * world->GetDimMin(),
            HEIGHT * world->GetDimMin()),
      TranslateAble(this, TRANS_SPEED, player->GetOri()),
      ViewAble(this->Actor::pos, this->Actor::ori, this->Actor::dim,
               IMAGE_FILENAME)
{
  printf("    Laser::Laser()\n");
  // Current Laser version has nothing further to do during construction.
}

Laser::~Laser()
{
  printf("    Laser::~Laser()\n");
  // Current Laser version has nothing further to do during destruction.
}

// TODO: Need to destroy laser when it reaches the edge of screen.

// TODO: Need to create lasers at appropriate times.

void Laser::Resize()
{
  printf("    Laser::Resize()\n");
  float dimMinRatio = world->GetDimMin() / world->GetDimMinPrior();
  float dimY = GetDimY() * dimMinRatio;
  SetDim(ASPECT_RATIO * dimY, dimY);
  SetPos(GetPosX() * world->GetDimX() / world->GetDimXPrior(),
         GetPosY() * world->GetDimY() / world->GetDimYPrior());
  SetSpeed(GetSpeed() * dimMinRatio);

  // float dimY = world->GetDimMin() * HEIGHT;
  // SetDim(ASPECT_RATIO * dimY, dimY);
  // SetPos(GetPosX() * world->GetDimX() / world->GetDimXPrior(),
  //        GetPosY() * world->GetDimY() / world->GetDimYPrior());
}

void Laser::RunModelAble()
{
  /* Note that this method is needed due to "diamond inheritance" of the
     ModelAble base class through both RotateAble and TranslateAble classes.
     RunModelAble() on those intermediary classes is virtual, and therefore
     ambiguous, when Asteroid inherits from both. It thus becomes necessary to
     clarify how RunModelAble() should behave if/when called on Asteroid. */
  // RotateAble::RunModelAble();
  TranslateAble::RunModelAble();
  // Detect laser out of bounds.
  if (Actor::pos.x > world->GetMaxX() + Actor::dimMax ||
      Actor::pos.x < world->GetMinX() - Actor::dimMax ||
      Actor::pos.y > world->GetMaxY() + Actor::dimMax ||
      Actor::pos.y < world->GetMinY() - Actor::dimMax)
  {
    model->DeleteLaser(this);
    // TODO: This is causing an error. Need to wait until the current loop
    // of modelAbles finishes running before model is deleted.
    // isRemovable = true;
  }
}

void Laser::RunViewAble()
{
  ViewAble::RunViewAble();
  // TODO: Is this method necessary?
}
