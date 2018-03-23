#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(SDL_Renderer* renderer, ResourceManager* resourceManager) : GEntity(renderer, resourceManager)
{
    collisionX = 20;
    collisionY = 0;
    collisionWidth = 35;
    collisionHeight = 0;

    maxSpeedX = P1_MAX_SPEED_X;
    maxSpeedY = P1_MAX_SPEED_Y;
}


bool PlayerEntity::OnLoad(const char* file, int width, int height, int textureWidth, int textureHeight, int maxFrames)
{
    loadFrameDimensions(NORMAL_ANIM_STR, NORMAL_ANIM_FILE);
    std::string imgFile = loadFrameDimensions(JUMP_ANIM_STR, JUMP_ANIM_FILE);
    getFrameSet(JUMP_ANIM_STR);
    if(currentFrameSet->empty() == false) maxFrames = currentFrameSet->size();

    return GEntity::OnLoad(imgFile.c_str(), width, height, 0, 0, maxFrames);
}


void PlayerEntity::OnLoop()
{
    GEntity::OnLoop();
    if(speedY == 0) {
        getFrameSet(NORMAL_ANIM_STR);
    }
}


void PlayerEntity::OnRender()
{
    GEntity::OnRender();
}


void PlayerEntity::OnRender(bool isVertical)
{
    if(currentFrameSet == NULL) {
        GEntity::OnRender(isVertical);
    }
    else {
        OnRender(*currentFrameSet);
    }

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
        AnimControl.maxFrames = currentFrameSet->size();
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
        PlayerEntity::Jump();
    }

    return true;
}



std::string PlayerEntity::loadFrameDimensions(std::string frameSetName, std::string frameImageFile)
{
    const char* file = frameImageFile.c_str();
    FILE* fileHandler = fopen(file, "r");
    if(fileHandler == NULL) {
        return NULL;
    }

    char tempName[255]="";
    fscanf(fileHandler, "%s\n", tempName);
    std::string frameSetImage(tempName);
    if(resourceManager->loadImg(frameSetImage, renderer) == NULL) {
        fclose(fileHandler);
        return NULL;
    }
    int frameSetSize = 0;
    fscanf(fileHandler, "%d\n", &frameSetSize);
    std::vector<SDL_Rect> frames;
    for(int i=0; i<frameSetSize; i++) {
        SDL_Rect rect;
        fscanf(fileHandler, "%d %d %d %d", &rect.x, &rect.y, &rect.w, &rect.h);
        frames.push_back(rect);
        fscanf(fileHandler, "\n");
    }
    fclose(fileHandler);
    frameSet.insert(std::pair<std::string, std::vector<SDL_Rect>>(frameSetName, frames));
    frameImages.insert(std::pair<std::string, std::string>(frameSetName, frameSetImage));

    return frameSetImage;
}


void PlayerEntity::getFrameSet(std::string frameSetName)
{
    std::map<std::string, std::vector<SDL_Rect>>::iterator it = frameSet.find(frameSetName);
    // if already in the map
    if (it != frameSet.end()) {
        currentFrameSet = &it->second;
    }
}



bool PlayerEntity::Jump()
{
    if(canJump == false)
        return false;

    speedY = -maxSpeedY;
    getFrameSet(JUMP_ANIM_STR);

    std::map<std::string, std::string>::iterator it = frameImages.find(JUMP_ANIM_STR);
    // if already in the map
    if (it != frameImages.end())
        texture = resourceManager->loadImg(it->second, renderer);

    return true;
}
