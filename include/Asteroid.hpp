#pragma once
#include "Actor.hpp"
#include "RotateAble.hpp"
#include "TranslateAble.hpp"
#include "ViewAble.hpp"

namespace Game
{
  // Base class of all asteroids in the game
  class Asteroid
      : public Actor,
        public RotateAble,
        public TranslateAble,
        public ViewAble
  {
  public:
    // Static factory function to make a new full-size asteroid.
    static Asteroid *MakeAsteroid();
    // Static factory function to make a new reduced-size asteroid.
    static Asteroid *MakeAsteroid(Asteroid *parent);

    // Constructs a new asteroid, to be called by static factory functions.
    Asteroid(float posX, float posY, float dimY, int phaseIndex);
    // Destructs an asteroid.
    ~Asteroid();

    int GetPhaseIndex() { return phaseIndex; }

    // Overrides Actor's Resize() method.
    void Resize() override;
    // Runs the actor's (multiple) ModelAble components.
    void RunModelAble() override;
    // Overrides ViewAble's Run() method.
    void RunViewAble() override;

  private:
    // Phase index -- ie, where asteroid is in destruction sequence.
    int phaseIndex;
  };
}
