#pragma once
#include "ModelAble.hpp"
#include "Vec2f.hpp"

namespace Game
{
  // Component-class for actors capable of being translationally accelerated.
  class AccTransAble : public ModelAble
  {
  public:
    // Constructs an AccTransAble component.
    AccTransAble(class TranslateAble *translateAble, float accX, float accY);
    // Destructs an AccTransAble component.
    virtual ~AccTransAble();

    // Set acceleration.
    void SetAcc(float accX, float accY) { acc.x = accX; acc.y = accY; }
    // Set x acceleration.
    void SetAccX(float accX) { acc.x = accX; }
    // Set y acceleration.
    void SetAccY(float accY) { acc.y = accY; }

    // Called by ModelAble each application cycle to accelerate the actor.
    virtual void RunModelAble() override;

  private:
    // Pointer to the TranslateAble component that can be accelerated
    class TranslateAble *translateAble;
    // Actor's tranlational acceleration
    Vec2f acc;
  };
}

// TODO: Does the destructor need to be virtual?

// TODO: Does RunModelAble need to be virtual?
