#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(SDL_Renderer* renderer, ResourceManager* resourceManager) : GEntity(renderer, resourceManager)
{

}


bool PlayerEntity::OnLoad(const char* file, int width, int height, int maxFrames)
{
    return GEntity::OnLoad(file, width, height, maxFrames);
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


void PlayerEntity::OnCollision(GEntity* entity)
{

}
