#ifndef CENTITY_H_INCLUDED
#define CENTITY_H_INCLUDED

#include <vector>

#include "CAnimation.h"
#include "ResourceManager.h"

class CEntity
{
public:
    static std::vector<CEntity*> entityList;

private:
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    ResourceManager* resourceManager = NULL;


protected:
    CAnimation Anim_Control;

public:
    float   X;
    float   Y;
    int     width;
    int     height;
    int     animState;

public:
    CEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);
    virtual ~CEntity();

public:
    virtual bool OnLoad(const char* file, int width, int height, int maxFrames);
    virtual void OnLoop();
    virtual void OnCleanup();
    // render methods
    virtual void OnRender();    // normal render with texture-rect x=0, y=0
    virtual void OnRender(bool isVertical); // render with texture-rect x and y in horizontal or vertical orders respectively
    virtual void OnRender(std::vector<SDL_Rect> &textureRects); // rencer with texture-rects from the array
};

#endif // CENTITY_H_INCLUDED
