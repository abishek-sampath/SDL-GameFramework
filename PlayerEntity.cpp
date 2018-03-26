#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(SDL_Renderer* renderer, ResourceManager* resourceManager) : GEntity(renderer, resourceManager)
{
    collisionX = 20;
    collisionY = 0;
    collisionWidth = 45;
    collisionHeight = 0;

    maxSpeedX = P1_MAX_SPEED_X;
    maxSpeedY = P1_MAX_SPEED_Y;

    name = PLAYER_NAME;
    health = PLAYER_MAX_HEALTH;
    knockback = false;
}


bool PlayerEntity::OnLoad(const char* file, int width, int height, int textureWidth, int textureHeight, int maxFrames)
{
    //load health image
    resourceManager->loadImg(PLAYER_HEALTH_IMG, renderer);

    loadFrameDimensions(NORMAL_ANIM_STR, NORMAL_ANIM_FILE);
    std::string imgFile = loadFrameDimensions(JUMP_ANIM_STR, JUMP_ANIM_FILE);
    getFrameSet(JUMP_ANIM_STR);
    if(currentFrameSet->empty() == false) maxFrames = currentFrameSet->size();

    return GEntity::OnLoad(imgFile.c_str(), width, height, 0, 0, maxFrames);
}


void PlayerEntity::OnLoop()
{
    if(health < 1 || Y > GArea::AreaControl.GetAreaHeight())
        dead = true;

    if(moveLeft) {
        accelX = -0.5;
    }
    else if(moveRight) {
        accelX = 0.5;
    }

    GEntity::OnLoop();
    if(speedY == 0) {
        getFrameSet(NORMAL_ANIM_STR);
    }
    if(speedY == 0 && knockback) {
        knockback = false;
        speedX = 0;
        maxSpeedX = P1_MAX_SPEED_X;
        maxSpeedY = P1_MAX_SPEED_Y;
        moveLeft = false;
        moveRight = false;
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
    //render player
    if(texture == NULL)
    {
        return;
    }
    if(AnimControl.GetCurrentFrame() < textureRects.size())
    {
        SDL_Rect textureRect = textureRects[AnimControl.GetCurrentFrame()];
        TextureUtils::OnDraw(texture, renderer,
                             X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),
                             textureRect.w, textureRect.h,
                             &textureRect,
                             flip);
    }

    // render health
    int healthXPos = 10;
    int healthYPos = 10;
    SDL_Texture* healthTexture = resourceManager->loadImg(PLAYER_HEALTH_IMG, renderer);
    for(int i=0; i < health; i++) {
        TextureUtils::OnDraw(healthTexture, renderer, healthXPos, healthYPos, 35, 35);
        healthXPos += 40;
    }
    healthTexture = NULL;
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
//    if(Y < entity->Y) {
//        entity->width *=0.7;
//        entity->height *=0.7;
//        entity->X = 300;
//    } else {
//        PlayerEntity::Jump();
//    }
    if(entity->name == BULLET_NAME) {
        return false;
    }
    if(entity->name == LIFE_NAME) {
        if(!entity->dead) {
            health++;
        }
        return true;
    }
    if(entity->name == ENEMY_NAME) {
        if(!knockback) {
            health--;
            knockback = true;
            Jump();
            speedX = P1_MAX_SPEED_X*5;
            //speedY = -P1_MAX_SPEED_X*2;
            maxSpeedX = P1_MAX_SPEED_X * 10;
            maxSpeedY = P1_MAX_SPEED_Y * 2;
            moveLeft = entity->moveLeft;
            moveRight = entity->moveRight;
            if(moveLeft) {
                speedX = -speedX;
            }
        }
    }
    return false;
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
