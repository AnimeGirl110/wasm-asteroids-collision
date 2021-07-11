#pragma once
#include "ModelAble.hpp"

namespace Game
{
  // Component-class for actors capable of being rotationally accelerated.
  class AccRotateAble : public ModelAble
  {
  public:
    // Constructs an AccRotateAble component.
    AccRotateAble(class RotateAble *rotateAble, float acc);
    // Destructs an AccRotateAble component.
    virtual ~AccRotateAble();

    // Set acceleration.
    void SetAcc(float acc) { this->acc = acc; }

    // Called by ModelAble each application cycle to accelerate the actor.
    virtual void RunModelAble() override;

  private:
    // Pointer to the RotateAble component that can be accelerated
    class RotateAble *rotateAble;
    // Actor's rotational acceleration
    float acc;
  };
}

// TODO: Does the destructor need to be virtual?

// TODO: Does RunModelAble need to be virtual?
