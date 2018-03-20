#ifndef GMAP_H_INCLUDED
#define GMAP_H_INCLUDED

#include <SDL.h>
#include <vector>

#include "GTile.h"
#include "TextureUtils.h"
#include "ResourceManager.h"


class GMap
{
public:
    SDL_Texture* texture;

private:
    SDL_Renderer* renderer;
    ResourceManager* resourceManager;

private:
    std::vector<GTile> tileList;

public:
    GMap(SDL_Renderer* renderer, ResourceManager* resourceManager);
    bool OnLoad(char* file);
    void OnRender(int mapX, int mapY);

public:
    GTile* GetTile(int X, int Y);
};

#endif // GMAP_H_INCLUDED
