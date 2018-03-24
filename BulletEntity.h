#ifndef BULLETENTITY_H_INCLUDED
#define BULLETENTITY_H_INCLUDED

#include "GEntity.h"

enum
{
    BULLET_STATE_FIRE = 0,
    BULLET_STATE_MOVE,
    BULLET_STATE_STOP
};

class BulletEntity : public GEntity
{
public:
    BulletEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);

public:
    bool OnLoad(int width, int height);
    void OnLoop();
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(GEntity* entity);
    // render options
    void OnRender();
    void OnRender(bool isVertical);
    void OnRender(std::vector<SDL_Rect> &textureRects);

    bool loadBulletExplosionDimensions(std::string animFile);

private:
    std::string bulletExplodeImage;
    std::vector<SDL_Rect> bulletExplodeFrames;
    int bulletState;
};

#endif // BULLET_H_INCLUDED
