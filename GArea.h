#ifndef GAREA_H_INCLUDED
#define GAREA_H_INCLUDED

#include "GMap.h"

class GArea
{
public:
    static GArea AreaControl;
    SDL_Renderer* renderer;
    ResourceManager* resourceManager;

public:
    std::vector<GMap> mapList;

private:
    int areaSizeX;
    int areaSizeY;
    SDL_Texture* texture;

public:
    GArea();
    bool OnLoad(const char* file);
    void OnRender(int cameraX, int cameraY);
    void OnCleanup();

public:
    GMap*   GetMap(int X, int Y);
    GTile*  GetTile(int X, int Y);
    int GetAreaWidth();
    int GetAreaHeight();
};

#endif // GAREA_H_INCLUDED
