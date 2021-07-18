#pragma once
#include <SDL2/SDL.h>
#include "Vec2i.hpp"
#include <vector>

namespace Game
{
  // Class for managing game state (data) in the Model-View-Controller paradigm.
  class Model
  {
  public:
    // Constructs the application's model.
    Model(class MVC *mvc);

    // Add a new laser.
    void AddLaser();
    // Performs actual deletion of any actors marked for deletion.
    void DeleteActors();
    // Adds the laser to vector of lasers requiring deletion.
    void DeleteLaser(class Laser *laser);
    // Called by parent MVC object at end to shut down resources, if any.
    void Finalize();
    // Called by parent MVC object at start to initialize resources, if any.
    bool Initialize();
    // Called when the screen has been resized.
    void Resize();
    // Called each application cycle to run any ModelAble actors.
    void Run();

  private:
    // Delete
    // Make the game's intial actors.
    void MakeInitialActors();

    // Vector of pointers to all asteroid actors in the game.
    std::vector<class Asteroid *> asteroids;
    // Pointer to game's rigid background actor.
    class Background *background;
    // Pointer to game's primary camera.
    class Camera *camera;
    // Reference to the screen's dimensions, stored on the parent MVC object.
    Vec2i &dim;
    // Indicates whether there has already been a prior resize event.
    bool hasBeenResized;
    // Vector of pointers to all laser actors in the game.
    std::vector<class Laser *> lasers;
    // Vector of pointers to all laser actors requiring deletion.
    std::vector<class Laser *> lasersToDelete;
    // Pointer to the model's parent MVC object.
    class MVC *mvc;
    // Pointer to game's player actor.
    class Player *player;
    // Time that the prior game cycle ran.
    Uint32 timePrior;
    // Pointer to game's world.
    class World *world;
  };
}
