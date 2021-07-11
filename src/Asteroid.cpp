#include "Asteroid.hpp"
#include "Config.hpp"
#include "Math.hpp"
#include <SDL2/SDL.h>
#include <stdio.h>

using namespace Game;
using namespace Math;
using namespace Config::Actor::Asteroid;

Asteroid *Asteroid::MakeAsteroid()
{
  printf("\n    Asteroid::MakeAsteroid()\n");
  float x, y, rr;
  float dimMin = world->GetDimMin();
  float dimY = dimMin * HEIGHTS[0] * GetRandomFloat(1.0f, HEIGHT_RND_FACTOR);
  float spawnRadius = SPAWNING_FACTOR * dimMin;
  float spawnRadiusSq = spawnRadius * spawnRadius;
  do
  {
    x = GetRandomFloat(world->GetMinX(), world->GetMaxX());
    y = GetRandomFloat(world->GetMinY(), world->GetMaxY());
    rr = x * x + y * y;
  } while (rr < spawnRadiusSq);
  printf("\n  + NEW ASTEROID\n");
  return new Asteroid(x, y, dimY, 0);
}

Asteroid *Asteroid::MakeAsteroid(Asteroid *parent)
{
  printf("\n    Asteroid::MakeAsteroid(parent)\n");
  int phaseIndex = parent->GetPhaseIndex() + 1;
  if (phaseIndex == NUM_PHASES)
  {
    return nullptr;
  }
  printf("\n  + NEW ASTEROID\n");
  return new Asteroid(
      parent->GetPosX(), parent->GetPosY(),
      world->GetDimMin() * HEIGHTS[phaseIndex] *
          GetRandomFloat(1.0f, HEIGHT_RND_FACTOR),
      phaseIndex);
}

// TODO: Randomize latter-phase asteroids' size, position, etc.

Asteroid::Asteroid(float posX, float posY, float dimY, int phaseIndex)
    : Actor(posX, posY, GetRandomFloat(0, PI2), ASPECT_RATIO * dimY, dimY),
      RotateAble(this, GetRandomFloat(-MAX_ANGULAR_SPEED, MAX_ANGULAR_SPEED)),
      TranslateAble(
          this,
          world->GetDimMin() * GetRandomFloat(MIN_TRANS_SPEED, MAX_TRANS_SPEED),
          GetRandomFloat(0, PI2)),
      ViewAble(this->Actor::pos, this->Actor::ori, this->Actor::dim,
               IMAGE_FILENAME),
      phaseIndex(phaseIndex)
{
  printf("    Asteroid::Asteroid()\n");
  // Current Asteroid version has nothing further to do during construction.
}

Asteroid::~Asteroid()
{
  printf("    Asteroid::~Asteroid()\n");
  // Current Asteroid version has nothing further to do during destruction.
}

void Asteroid::Resize()
{
  printf("    Asteroid::Resize()\n");
  float dimMinRatio = world->GetDimMin() / world->GetDimMinPrior();
  float dimY = GetDimY() * dimMinRatio;
  SetDim(ASPECT_RATIO * dimY, dimY);
  SetPos(GetPosX() * world->GetDimX() / world->GetDimXPrior(),
         GetPosY() * world->GetDimY() / world->GetDimYPrior());
  SetSpeed(GetSpeed() * dimMinRatio);
}

void Asteroid::RunModelAble()
{
  /* Note that this method is needed due to "diamond inheritance" of the
     ModelAble base class through both RotateAble and TranslateAble classes.
     RunModelAble() on those intermediary classes is virtual, and therefore
     ambiguous, when Asteroid inherits from both. It thus becomes necessary to
     clarify how RunModelAble() should behave if/when called on Asteroid. */
  RotateAble::RunModelAble();
  TranslateAble::RunModelAble();
  // Detect asteroid moving out of bounds, and wrap around if needed.
  if (Actor::pos.x > world->GetMaxX() - Actor::dimMax && GetVelX() > 0)
  {
    // Asteroid is travelling rightward, so move it to left side.
    ChangePosX(-world->GetDimX());
  }
  if (Actor::pos.x < world->GetMinX() + Actor::dimMax && GetVelX() < 0)
  {
    // Asteroid is travelling leftward, so move it to right side.
    ChangePosX(world->GetDimX());
  }
  if (Actor::pos.y > world->GetMaxY() - Actor::dimMax && GetVelY() > 0)
  {
    // Asteroid is travelling downward, so move it to top side.
    ChangePosY(-world->GetDimY());
  }
  if (Actor::pos.y < world->GetMinY() + Actor::dimMax && GetVelY() < 0)
  {
    // Asteroid is travelling upward, so move it to bottom side.
    ChangePosY(world->GetDimY());
  }
}

void Asteroid::RunViewAble()
{
  ViewAble::RunViewAble();
  if (Actor::pos.x > world->GetMaxX() - Actor::dimMax)
  {
    // Asteroid is on right side.
    RunViewAbleAt(Actor::pos.x - world->GetDimX(), Actor::pos.y);
    if (Actor::pos.y > world->GetMaxY() - Actor::dimMax)
    {
      // Asteroid is on lower-right corner.
      RunViewAbleAt(Actor::pos.x, Actor::pos.y - world->GetDimY());
      RunViewAbleAt(Actor::pos.x - world->GetDimX(),
                    Actor::pos.y - world->GetDimY());
    }
    else if (Actor::pos.y < world->GetMinY() + Actor::dimMax)
    {
      // Asteroid is on upper-right corner.
      RunViewAbleAt(Actor::pos.x, Actor::pos.y + world->GetDimY());
      RunViewAbleAt(Actor::pos.x - world->GetDimX(),
                    Actor::pos.y + world->GetDimY());
    }
  }
  else if (Actor::pos.x < world->GetMinX() + Actor::dimMax)
  {
    // Asteroid is on left side.
    RunViewAbleAt(Actor::pos.x + world->GetDimX(), Actor::pos.y);
    if (Actor::pos.y > world->GetMaxY() - Actor::dimMax)
    {
      // Asteroid is on lower-left corner.
      RunViewAbleAt(Actor::pos.x, Actor::pos.y - world->GetDimY());
      RunViewAbleAt(Actor::pos.x + world->GetDimX(),
                    Actor::pos.y - world->GetDimY());
    }
    else if (Actor::pos.y < world->GetMinY() + Actor::dimMax)
    {
      // Asteroid is on upper-left corner.
      RunViewAbleAt(Actor::pos.x, Actor::pos.y + world->GetDimY());
      RunViewAbleAt(Actor::pos.x + world->GetDimX(),
                    Actor::pos.y + world->GetDimY());
    }
  }
  else
  {
    if (Actor::pos.y > world->GetMaxY() - Actor::dimMax)
    {
      // Asteroid is on bottom side.
      RunViewAbleAt(Actor::pos.x, Actor::pos.y - world->GetDimY());
    }
    else if (Actor::pos.y < world->GetMinY() + Actor::dimMax)
    {
      // Asteroid is on upper side.
      RunViewAbleAt(Actor::pos.x, Actor::pos.y + world->GetDimY());
    }
  }
}