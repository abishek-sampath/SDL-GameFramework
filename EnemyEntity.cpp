#include "EnemyEntity.h"
#include <random>


EnemyEntity::EnemyEntity(SDL_Renderer* renderer, ResourceManager* resourceManager) : GEntity(renderer, resourceManager)
{
    collisionX = 5;
    collisionY = 5;
    collisionWidth = 20;
    collisionHeight = 20;

    maxSpeedX = ENEMY_MAXSPEEDX;
    maxSpeedY = ENEMY_MAXSPEEDY;

    name = ENEMY_NAME;
}


bool EnemyEntity::OnLoad(std::string animFile, int width, int height)
{
    if(loadEnemyAnim(animFile) == false) {
        return false;
    }

    this->width = width;
    this->height = height;

    AnimControl.maxFrames = 0;

    return true;
}


void EnemyEntity::OnLoop()
{
    if(moveLeft) {
        accelX = -0.5;
    }
    else if(moveRight) {
        accelX = 0.5;
    }
    GEntity::OnLoop();

    if(onGround && moveLeft == false && moveRight == false)
    {
        AnimControl.maxFrames = frameSet.size();
        std::knuth_b rand_engine;
        std::bernoulli_distribution d(0.5);
        moveRight = d(rand_engine);
        if(moveRight == false)
        {
            speedX = -0.1;
            moveLeft = true;
            flip = SDL_FLIP_HORIZONTAL;
        } else {
            speedX = 0.1;
        }
    }

    if(onGround && speedX == 0) {
        moveLeft  = !moveLeft;
        moveRight = !moveRight;

        if(flip == SDL_FLIP_NONE) flip = SDL_FLIP_HORIZONTAL;
        else flip = SDL_FLIP_NONE;
    }
}


void EnemyEntity::OnCleanup()
{
    frameSet.clear();
    GEntity::OnCleanup();
}


void EnemyEntity::OnAnimate()
{
    GEntity::OnAnimate();
}


bool EnemyEntity::OnCollision(GEntity* entity)
{
    // TODO
    if(entity->name == BULLET_NAME) {
        this->dead = true;
        return true;
    }

    return false;
}


// render options
void EnemyEntity::OnRender()
{
    GEntity::OnRender();
}


void EnemyEntity::OnRender(bool isVertical)
{
    OnRender(frameSet);
}


void EnemyEntity::OnRender(std::vector<SDL_Rect> &textureRects)
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


bool EnemyEntity::loadEnemyAnim(std::string animFile)
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


GEntity* EnemyEntity::clone() const
{
    return new EnemyEntity(*this);
}
