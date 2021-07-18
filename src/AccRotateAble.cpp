#include "AccRotateAble.hpp"
#include <stdio.h>
#include "RotateAble.hpp"

using namespace Game;

AccRotateAble::AccRotateAble(RotateAble *rotateAble, float acc)
    : rotateAble(rotateAble),
      acc(acc)
{
  printf("    AccRotateAble::AccRotateAble()\n");
  // Current AccRotateAble version has nothing further to do in construction.
}

AccRotateAble::~AccRotateAble()
{
  printf("    AccRotateAble::~AccRotateAble()\n");
  // Current AccRotateAble version has nothing further to do in destruction.
}

void AccRotateAble::RunModelAble()
{
  // TimeChange is stored statically on ModelAble.
  rotateAble->ChangeVel(acc * timeChange);
}
