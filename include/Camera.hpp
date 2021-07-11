#pragma once
#include "Actor.hpp"
#include "RotateAble.hpp"
#include "TranslateAble.hpp"

namespace Game
{
  // Camera "sees" the portion of the model world to be graphically rendered.
  class Camera
      : public Actor,
        public RotateAble,
        public TranslateAble
  {
  public:
    // Constructs a new Camera.
    Camera(float posX, float posY, float ori, float dimX, float dimY);
    // Destructs a Camera.
    ~Camera();

    // Get x-dimension.
    float GetDimX() { return dim.x; }
    // Get y-dimension.
    float GetDimY() { return dim.y; }
    // Get orientation.
    float GetOri() { return ori; }
    // Get x-position.
    float GetPosX() { return pos.x; }
    // Get y-position.
    float GetPosY() { return pos.y; }

    // Overrides Actor's Resize() method.
    void Resize() override;
    // Runs the actor's (multiple) ModelAble components.
    void RunModelAble() override;
  };
}
