#include "Actor.hpp"
#include "Asteroid.hpp"
#include "Background.hpp"
#include "Camera.hpp"
#include "Config.hpp"
#include "Laser.hpp"
#include "Model.hpp"
#include "ModelAble.hpp"
#include "MVC.hpp"
#include "Player.hpp"
#include <stdio.h>
#include "World.hpp"

using namespace Game;
using namespace Config::Model;

Model::Model(MVC *mvc)
    : background(nullptr),
      camera(nullptr),
      dim(mvc->GetDim()),
      hasBeenResized(false),
      mvc(mvc),
      player(nullptr),
      timePrior(0),
      world(nullptr)
{
  printf("  Model::Model()\n");
  // Current version of Model has nothing further to do during construction.
}

void Model::AddLaser(float posX, float posY, float ori)
{
  // TODO
  (void)posX;
  (void)posY;
  (void)ori;
}

void Model::Finalize()
{
  printf("\n  Model::Finalize()\n");

  // Delete the background
  if (background)
  {
    printf("\n  - DELETE BACKGROUND\n");
    delete background;
    background = nullptr;
  }

  // Delete the primary camera
  printf("\n  - DELETE CAMERA\n");
  if (camera)
  {
    delete camera;
    camera = nullptr;
  }

  // Delete the player
  if (player)
  {
    printf("\n  - DELETE PLAYER\n");
    delete player;
    player = nullptr;
  }

  // Delete the world
  if (world)
  {
    printf("\n  - DELETE WORLD\n");
    delete world;
    world = nullptr;
  }

  // TODO: Are the asteroids and lasers to be deleted here????????
}

bool Model::Initialize()
{
  printf("  Model::Initialize()\n");
  // Current version of Model has nothing further to do during initialization.
  return true;
}

void Model::MakeInitialActors()
{
  printf("    Model::MakeInitialActors()\n");

  // Create the world, using the screen's full dimensions as recorded.
  printf("\n  + NEW WORLD\n");
  world = new World((float)dim.x, (float)dim.y);
  // Inform all actors of their world.
  Actor::SetWorld(world);

  // Create the game's primary camera, also using the screen's full dimensions.
  printf("\n  + NEW CAMERA\n");
  camera = new Camera(0, 0, 0, (float)dim.x, (float)dim.y);
  // Inform mvc of the camera. Mvc passes it to view, which passes to viewAbles.
  mvc->SetCamera(camera);

  // Create the game's background.
  printf("\n  + NEW BACKGROUND\n");
  background = new Background();

  // Create the player.
  printf("\n  + NEW PLAYER\n");
  player = new Player();

  // Create the asteroids.
  for (int i = 0; i < NUM_ASTEROIDS; ++i)
  {
    // Static factory function MakeAsteroid() will take care of randomizations.
    asteroids.emplace_back(Asteroid::MakeAsteroid());
  }
}

void Model::Resize()
{
  printf("  Model::Resize()\n");
  if (hasBeenResized)
  {
    world->Resize((float)dim.x, (float)dim.y);
    camera->Resize();
    background->Resize();
    player->Resize();
    for (auto asteroid : asteroids)
    {
      asteroid->Resize();
    }
    for (auto laser : lasers)
    {
      laser->Resize();
    }
  }
  else
  {
    hasBeenResized = true;
    MakeInitialActors();
  }
}

void Model::Run()
{
  // Calculate the actual timeChange.
  int timeChange = SDL_GetTicks() - timePrior;
  // Cap the timeChange to LOOP_TIME_MAX specified in config file.
  if (timeChange > LOOP_TIME_MAX)
  {
    timeChange = LOOP_TIME_MAX;
  }
  // Update modelAbles with the timeChange.
  ModelAble::RunAll(timeChange);
  // Update timePrior to current time.
  timePrior = SDL_GetTicks();
}
