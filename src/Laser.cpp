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
      TranslateAble(this, 0, 0), // TODO: replace with proper values
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
  float dimY = world->GetDimMin() * HEIGHT;
  SetDim(ASPECT_RATIO * dimY, dimY);
  SetPos(GetPosX() * world->GetDimX() / world->GetDimXPrior(),
         GetPosY() * world->GetDimY() / world->GetDimYPrior());
}
