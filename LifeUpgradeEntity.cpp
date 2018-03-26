#include "LifeUpgradeEntity.h"


LifeUpgradeEntity::LifeUpgradeEntity(SDL_Renderer* renderer, ResourceManager* resourceManager) : GEntity(renderer, resourceManager)
{
    collisionX = 5;
    collisionWidth = 5;

    name = LIFE_NAME;
    lifeUsed = false;

    flags = ENTITY_FLAG_MAPONLY;
}


bool LifeUpgradeEntity::OnLoad(std::string animFile, int width, int height)
{
    if(loadLifeAnim(animFile) == false) {
        return false;
    }

    this->width = width;
    this->height = height;

    AnimControl.maxFrames = frameSet.size();

    return true;
}


void LifeUpgradeEntity::OnLoop()
{
    GEntity::OnLoop();
}


void LifeUpgradeEntity::OnCleanup()
{
    frameSet.clear();
    GEntity::OnCleanup();
}


void LifeUpgradeEntity::OnAnimate()
{
//    if(lifeUsed) {
//        AnimControl.maxFrames = frameSet.size();
//        if(AnimControl.GetCurrentFrame() == AnimControl.maxFrames - 1)
//        {
//            dead = true;
//        }
//    }

    GEntity::OnAnimate();
}


bool LifeUpgradeEntity::OnCollision(GEntity* entity)
{
    if(entity->name == PLAYER_NAME && lifeUsed == false) {
        lifeUsed = true;
        width *= 4;
        height *= 4;
        Y -= 40;
        AnimControl.maxFrames = 0;
        dead = true;
    }
    if(entity->name == ENEMY_NAME) {
        dead = true;
    }

    return false;
}


// render options
void LifeUpgradeEntity::OnRender()
{
    GEntity::OnRender();
}


void LifeUpgradeEntity::OnRender(bool isVertical)
{
    OnRender(frameSet);
}


void LifeUpgradeEntity::OnRender(std::vector<SDL_Rect> &textureRects)
{
    if(texture == NULL)
    {
        return;
    }
    if(AnimControl.GetCurrentFrame() < textureRects.size())
    {
        SDL_Rect textureRect = textureRects[AnimControl.GetCurrentFrame()];
        TextureUtils::OnDraw(texture, renderer,
                             X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),
                             width, height,
                             &textureRect,
                             flip);
    }
}


bool LifeUpgradeEntity::loadLifeAnim(std::string animFile)
{
    const char* file = animFile.c_str();
    FILE* fileHandler = fopen(file, "r");
    if(fileHandler == NULL) {
        return false;
    }

    char tempName[255]="";
    fscanf(fileHandler, "%s\n", tempName);
    std::string imgFile(tempName);
    if((texture = resourceManager->loadImg(imgFile, renderer)) == NULL) {
        fclose(fileHandler);
        return false;
    }
    int frameSetSize = 0;
    fscanf(fileHandler, "%d\n", &frameSetSize);
    for(int i=0; i<frameSetSize; i++) {
        SDL_Rect rect;
        fscanf(fileHandler, "%d %d %d %d", &rect.x, &rect.y, &rect.w, &rect.h);
        frameSet.push_back(rect);
        fscanf(fileHandler, "\n");
    }
    fclose(fileHandler);

    return true;
}


GEntity* LifeUpgradeEntity::clone() const
{
    return new LifeUpgradeEntity(*this);
}
