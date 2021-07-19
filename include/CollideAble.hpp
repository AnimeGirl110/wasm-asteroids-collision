#pragma once
#include "Vec2f.hpp"

namespace Game
{
  // Component-class for actors capable of colliding (hitbox)
  class CollideAble
  {
  public:
    // Determines if this CollideAble is colliding with another.
    static bool RunCollideAble(CollideAble *collideAbleA, CollideAble *collideAbleB);
    //TODO: Do we need a static RunAll()?

    // Constructs a CollideAble component.
    CollideAble(class Actor *actor);
    // Destructs a CollideAble component.
    virtual ~CollideAble();

    float GetPosX() { return actor->GetPosX(); }
    float GetPosY() { return actor->GetPosY(); }

    float GetCollisionRadius()
    {
      return collisionRadius;
    }

    // Resizes the collision radius.
    void Resize();

  private:
    // Pointer to the actor that possesses this component.
    class Actor *actor;
    // Size of collision radius.
    float collisionRadius;
  };
}

// TODO: Does the destructor need to be virtual?