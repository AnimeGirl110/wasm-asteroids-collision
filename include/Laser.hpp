#pragma once
#include "Actor.hpp"
#include "CollideAble.hpp"
#include "TranslateAble.hpp"
#include "ViewAble.hpp"

namespace Game
{
  // Base class of all lasers in the game
  class Laser
      : public Actor,
        public CollideAble,
        public TranslateAble,
        public ViewAble
  {
  public:
    // Constructs a new laser.
    Laser(class Player *player);
    // Destructs a laser.
    ~Laser();

    // Overrides Actor's Resize() method.
    void Resize() override;
    // Runs the actor's (multiple) ModelAble components.
    void RunModelAble() override;
    // Overrides ViewAble's RunViewAble() method.
    void RunViewAble() override;

  private:
    // TODO: Private?
  };
}
