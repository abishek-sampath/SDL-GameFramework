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
	std::map<int, std::string> propsResourceMap;

public:
    GMap(SDL_Renderer* renderer, ResourceManager* resourceManager);
    bool OnLoad(const char* file);
    void OnRender(int mapX, int mapY);
    bool loadAllProps(char* propFile);
    bool loadAllProps(char* propFile, int r, int g, int b);

public:
    GTile* GetTile(int X, int Y);
    SDL_Texture* getPropTexture(int prop);
};

#endif // GMAP_H_INCLUDED
