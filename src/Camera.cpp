#include "Camera.hpp"
#include <stdio.h>

using namespace Game;

Camera::Camera(float posX, float posY, float ori, float dimX, float dimY)
    : Actor(posX, posY, ori, dimX, dimY),
      RotateAble(this, 0),
      TranslateAble(this, 0, 0)
{
  printf("    Camera::Camera()\n");
}

Camera::~Camera()
{
  printf("    Camera::~Camera()\n");
}

void Camera::Resize()
{
  printf("    Camera::Resize()\n");
  SetDim(world->GetDimX(), world->GetDimY());
  // TODO: Adjust the camera's position upon resize.
}

void Camera::RunModelAble()
{
  /* Note that this method is needed due to "diamond inheritance" of the
     ModelAble base class through both RotateAble and TranslateAble classes.
     RunModelAble() on those intermediary classes is virtual, and therefore
     ambiguous, when Camera inherits from both. It thus becomes necessary to
     clarify how RunModelAble() should behave if/when called on Camera. */
  RotateAble::RunModelAble();
  TranslateAble::RunModelAble();
}
