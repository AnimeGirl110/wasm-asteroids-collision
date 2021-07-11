#include "Config.hpp"
#include <math.h>
#include "Player.hpp"
#include <SDL2/SDL.h>
#include <stdio.h>

using namespace Game;
using namespace Config::Actor::Player;

Player::Player()
    : Actor(POS_X, POS_Y, ORI,
            ASPECT_RATIO * HEIGHT * world->GetDimMin(),
            HEIGHT * world->GetDimMin()),
      RotateAble(this, 0),
      TranslateAble(this, 0, 0),
      AccTransAble(this, 0, 0),
      ViewAble(this->Actor::pos, this->Actor::ori, this->Actor::dim,
               IMAGE_FILENAME)
{
  printf("    Player::Player()\n");
  // Current Player version has nothing further to do during construction.
}

Player::~Player()
{
  printf("    Player::~Player()\n");
  // Current Player version has nothing further to do during destruction.
}

void Player::Resize()
{
  printf("    Player::Resize()\n");
  float dimY = world->GetDimMin() * HEIGHT;
  SetDim(ASPECT_RATIO * dimY, dimY);
  SetPos(GetPosX() * world->GetDimX() / world->GetDimXPrior(),
         GetPosY() * world->GetDimY() / world->GetDimYPrior());
}

// TODO: Implement RunKeyAble and RunMouseAble

void Player::RunKeyAble()
{
  // controllerRotation = 0;
  // if (KeyAble::keyState[KEY_ROTATE_CCW])
  // {
  //   // rotate counter-clockwise
  //   --controllerRotation;
  // }
  // if (KeyAble::keyState[KEY_ROTATE_CW])
  // {
  //   // rotate clockwise
  //   ++controllerRotation;
  // }

  // keyThrust = 0;
  // if (KeyAble::keyState[KEY_FWD])
  // {
  //   // thrust forward
  //   ++keyThrust;
  // }

  // controllerThrust = (mouseThrust || keyThrust) ? 1 : 0;
}

void Player::RunModelAble()
{
  /* Note that this method is needed due to "diamond inheritance" of the
     ModelAble base class through both RotateAble and TranslateAble classes.
     RunModelAble() on those intermediary classes is virtual, and therefore
     ambiguous, when Player inherits from both. It thus becomes necessary to
     clarify how RunModelAble() should behave if/when called on Player. */
  RotateAble::RunModelAble();
  TranslateAble::RunModelAble();
}

void Player::RunMouseAble()
{
  // switch (event->type)
  // {
  // case SDL_MOUSEBUTTONDOWN:
  //   mouseThrust = 1;
  //   break;
  // case SDL_MOUSEBUTTONUP:
  //   mouseThrust = 0;
  //   break;
  // case SDL_MOUSEMOTION:
  //   Actor::pos.a = atan2(event->motion.y - 0.5f * Config::View::WINDOW_DIM_Y,
  //                        event->motion.x - 0.5f * Config::View::WINDOW_DIM_X);
  //   break;
  // case SDL_MOUSEWHEEL:
  //   // ignore
  //   break;
  // }
}

// #include "Acceleration.hpp"
// #include <math.h>
// #include "Position.hpp"
// #include "ThrustAble.hpp"
// #include <stdio.h>
// #include "Velocity.hpp"

// using namespace Game;

// ThrustAble::ThrustAble(Position &pos, class Velocity &vel, Acceleration &acc,
//                        float magThrust, int *controllerThrust)
//     : controllerThrust(controllerThrust), magThrust(magThrust),
//       acc(acc), pos(pos), vel(vel)
// {
//   printf("    ThrustAble::ThrustAble(pos(%.1f, %.1f), vel(%.1f, %.1f), acc(%.1f, %.1f), %.1f, %d)\n",
//          pos.x, pos.y, vel.x, vel.y, acc.x, acc.y, magThrust, *controllerThrust);
// }

// ThrustAble::~ThrustAble()
// {
//   printf("    ThrustAble::~ThrustAble()\n");
// }

// void ThrustAble::RunModelAble()
// {
//   float accMag = (*controllerThrust) * magThrust;
//   acc.x = accMag * cos(pos.a);
//   acc.y = accMag * sin(pos.a);
//   vel.x += acc.x * timeChange;
//   vel.y += acc.y * timeChange;
//   pos.x += vel.x * timeChange;
//   pos.y += vel.y * timeChange;
// }
