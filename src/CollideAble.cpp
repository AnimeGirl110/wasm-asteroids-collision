#include "Actor.hpp"
#include <stdio.h>
#include "CollideAble.hpp"

using namespace Game;

CollideAble::CollideAble(Actor *actor)
    : actor(actor),
      collisionRadius(actor->GetDimMin())
{
  printf("    CollideAble::CollideAble()\n");
  // Current CollideAble version has nothing further to do in construction.
}

CollideAble::~CollideAble()
{
  printf("    CollideAble::~CollideAble()\n");
  // Current CollideAble version has nothing further to do in destruction.
}

bool CollideAble::RunCollideAble(CollideAble *collideAbleA, CollideAble *collideAbleB)
{
  float rSum = collideAbleA->GetCollisionRadius() + collideAbleB->GetCollisionRadius();
  float rSumSquare = rSum * rSum;
  float dx = collideAbleA->GetPosX() - collideAbleB->GetPosX();
  float dy = collideAbleA->GetPosY() - collideAbleB->GetPosY();
  float dSquare = dx * dx + dy * dy;
  return dSquare < rSumSquare;
}