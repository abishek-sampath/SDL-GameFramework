#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(SDL_Renderer* renderer, ResourceManager* resourceManager) : GEntity(renderer, resourceManager)
{
    collisionX = 20;
    collisionY = 0;
    collisionWidth = 35;
    collisionHeight = 0;

    maxSpeedX = maxSpeedY = 10;
}


bool PlayerEntity::OnLoad(const char* file, int width, int height, int textureWidth, int textureHeight, int maxFrames)
{
    return GEntity::OnLoad(file, width, height, textureWidth, textureHeight, maxFrames);
}


void PlayerEntity::OnLoop()
{
    GEntity::OnLoop();
}


void PlayerEntity::OnRender()
{
    GEntity::OnRender();
}


void PlayerEntity::OnRender(bool isVertical)
{
    GEntity::OnRender(isVertical);
}


void PlayerEntity::OnRender(std::vector<SDL_Rect> &textureRects)
{
    GEntity::OnRender(textureRects);
}


void PlayerEntity::OnCleanup()
{
    GEntity::OnCleanup();
}


void PlayerEntity::OnAnimate()
{
    if(speedX != 0) {
        AnimControl.maxFrames = 8;
    }
    else {
        AnimControl.maxFrames = 0;
    }

    GEntity::OnAnimate();
}


bool PlayerEntity::OnCollision(GEntity* entity)
{
    if(Y < entity->Y) {
        entity->width *=0.7;
        entity->height *=0.7;
        entity->X = 300;
    } else {
    Jump();
    }

    return true;
}
