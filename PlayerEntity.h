#ifndef PLAYERENTITY_H_INCLUDED
#define PLAYERENTITY_H_INCLUDED

#include "GEntity.h"

class PlayerEntity : public GEntity
{
public:
    PlayerEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);
    bool OnLoad(const char* file, int width, int height, int maxFrames);
    void OnLoop();
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(GEntity* entity);
    // different render options
    void OnRender();
    void OnRender(bool isVertical);
    void OnRender(std::vector<SDL_Rect> &textureRects);
};

#endif // PLAYERENTITY_H_INCLUDED
