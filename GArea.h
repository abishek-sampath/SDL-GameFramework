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
    int areaSize;
    SDL_Texture* texture;

public:
    GArea();
    bool OnLoad(const char* file);
    void OnRender(int cameraX, int cameraY);
    void OnCleanup();
};

#endif // GAREA_H_INCLUDED