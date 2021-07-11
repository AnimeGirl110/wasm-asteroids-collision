#include <algorithm>
#include "Camera.hpp"
#include "Math.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Vec2f.hpp"
#include "ViewAble.hpp"

using namespace Game;

// Static variables must be initialized in cpp code outside of hpp declaration.
Camera *ViewAble::camera = nullptr;
SDL_Renderer *ViewAble::renderer = nullptr;
std::unordered_map<char const *, SDL_Texture *> ViewAble::textures;
std::vector<ViewAble *> ViewAble::viewAbles;

void ViewAble::DestroyTextures()
{
  printf("      ViewAble::DestroyTextures()\n");
  for (auto texture : textures)
  {
    SDL_DestroyTexture(texture.second);
  }
  textures.clear();
  for (auto viewAble : viewAbles)
  {
    viewAble->NullifyTexture();
  }
}

void ViewAble::RunAll()
{
  // printf("RENDERER: %p\n", renderer); // TODO: Remove after testing.
  for (auto viewAble : viewAbles)
  {
    viewAble->RunViewAble();
  }
}

void ViewAble::SetCamera(Camera *camera)
{
  printf("          ViewAble::SetCamera()\n");
  ViewAble::camera = camera;
}

void ViewAble::SetRenderer(SDL_Renderer *renderer)
{
  printf("    ViewAble::SetRenderer()\n");
  // Replace the old renderer with the new one.
  ViewAble::renderer = renderer;
  // Destroy all existing textures.
  DestroyTextures();
  // Recreate all textures.
  for (auto viewAble : viewAbles)
  {
    viewAble->SetTexture();
  }
}

ViewAble::ViewAble(Vec2f &pos, float &ori, Vec2f &dim,
                   char const *fileName)
    : dim(dim),
      fileName(fileName),
      ori(ori),
      pos(pos),
      texture(nullptr),
      sourceRect(nullptr)
{
  printf("    ViewAble::ViewAble()\n");
  // Set the texture according to fileName.
  SetTexture();
  // Add the new viewAble to the end of the static collection of viewAbles.
  viewAbles.emplace_back(this);
}

// Deletion of viewAble triggers this destructor, so don't do "delete" op here.
ViewAble::~ViewAble()
{
  printf("    ViewAble::~ViewAble()\n");
  auto it = std::find(viewAbles.begin(), viewAbles.end(), this);
  if (it != viewAbles.end())
  {
    // This quick deletion trick works so long as the vector isn't "ordered."
    std::iter_swap(it, viewAbles.end() - 1);
    viewAbles.pop_back();
  }
}

void ViewAble::RunViewAble()
{
  // Define the viewAble's bounding destination rectangle.
  SDL_Rect const destinationRect{
      (int)(0.5 * (camera->GetDimX() - dim.x) + pos.x - camera->GetPosX()),
      (int)(0.5 * (camera->GetDimY() - dim.y) + pos.y - camera->GetPosY()),
      (int)dim.x, (int)dim.y};
  // Draw the viewAble.
  if (SDL_RenderCopyEx(
          renderer, texture, sourceRect, &destinationRect,
          (ori - camera->GetOri()) * Math::DEG_PER_RAD,
          NULL, SDL_FLIP_NONE) != 0)
  {
    SDL_Log("ERROR - SDL_RenderCopyEx: %s\n", SDL_GetError());
  }
  // TODO: Ensure this orientation feature works properly.
}

void ViewAble::RunViewAbleAt(float posX, float posY)
{
  // Define the viewAble's bounding destination rectangle.
  SDL_Rect const destinationRect{
      (int)(0.5 * (camera->GetDimX() - dim.x) + posX - camera->GetPosX()),
      (int)(0.5 * (camera->GetDimY() - dim.y) + posY - camera->GetPosY()),
      (int)dim.x, (int)dim.y};
  // Draw the viewAble.
  if (SDL_RenderCopyEx(
          renderer, texture, sourceRect, &destinationRect,
          (ori - camera->GetOri()) * Math::DEG_PER_RAD,
          NULL, SDL_FLIP_NONE) != 0)
  {
    SDL_Log("ERROR - SDL_RenderCopyEx: %s\n", SDL_GetError());
  }
  // TODO: Ensure this orientation feature works properly.
}

void ViewAble::SetSourceRect(int x, int y, int width, int height)
{
  printf("      ViewAble::SetSourceRect()\n");
  sourceRect->x = x;
  sourceRect->y = y;
  sourceRect->w = width;
  sourceRect->h = height;
}

void ViewAble::SetTexture()
{
  printf("      ViewAble::SetTexture(%s)\n", fileName);
  // Check to see if the same fileName has already been turned into a texture.
  auto it = textures.find(fileName);
  if (it != textures.end())
  {
    // If the texture already exists, just use it instead of creating new one.
    texture = it->second;
  }
  else
  {
    // Load the image file to a surface temporarily.
    SDL_Surface *surface = IMG_Load(fileName);
    if (!surface)
    {
      SDL_Log("ERROR -- IMG_Load(%s)", fileName);
      texture = nullptr;
      return;
    }

    // Use the surface to create a texture.
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    // Free the temporary surface (as it is no longer needed).
    SDL_FreeSurface(surface);
    if (!texture)
    {
      SDL_Log("ERROR -- SDL_CreateTextureFromSurface(%s)", fileName);
      texture = nullptr;
      return;
    }

    // Store the texture in the textures map using fileName as the key.
    textures.emplace(fileName, texture);
  }
}
