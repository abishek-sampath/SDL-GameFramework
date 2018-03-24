#include "BulletEntity.h"
#include <exception>

BulletEntity::BulletEntity(SDL_Renderer* renderer, ResourceManager* resourceManager) : GEntity(renderer, resourceManager)
{
    collisionX = 5;
    collisionWidth = 10;
    collisionHeight = 20;

    maxSpeedX = BULLET_MAXSPEED;
}

bool BulletEntity::OnLoad(int width, int height)
{
    texture = resourceManager->loadImg(BULLET_FIRE_IMG, renderer);
    // load below in OnInit()
    this->width = width;
    this->height = height;
    loadBulletExplosionDimensions(BULLET_EXPLODE_ANIM_FILE);
    bulletState = BULLET_STATE_FIRE;
    AnimControl.maxFrames = 1;

    return true;
}


void BulletEntity::OnLoop()
{
    if(moveLeft) {
        accelX = -10;
    }
    else if(moveRight) {
        accelX = 10;
    }

    GEntity::OnLoop();
    if(bulletState == BULLET_STATE_FIRE && speedX != 0) {
        texture = resourceManager->loadImg(BULLET_IMG, renderer);
        bulletState = BULLET_STATE_MOVE;
    }
    else if((bulletState == BULLET_STATE_MOVE) &&
            (speedX == 0)) {
        moveLeft = moveRight = false;
        texture = resourceManager->loadImg(bulletExplodeImage, renderer);
        bulletState = BULLET_STATE_STOP;
    }
}


void BulletEntity::OnCleanup()
{
    bulletExplodeFrames.clear();
    GEntity::OnCleanup();
}


void BulletEntity::OnAnimate()
{
    if(speedX == 0)
    {
        AnimControl.maxFrames = bulletExplodeFrames.size();
        if(AnimControl.GetCurrentFrame() == AnimControl.maxFrames - 1)
        {
            dead = true;
        }
    }

    GEntity::OnAnimate();
}

bool BulletEntity::OnCollision(GEntity* entity)
{
    return true;
}

// render options
void BulletEntity::OnRender()
{
    GEntity::OnRender();
}


void BulletEntity::OnRender(bool isVertical)
{
    //std::cout << "b " << X << ", " << Y << '\n';
    if(bulletState != BULLET_STATE_STOP) {
        //std::cout << "bullet render move\n";
        TextureUtils::OnDraw(texture, renderer,
           X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),
           width, height);
    }
    else {
        //std::cout << "bullet render stop\n";
        SDL_Rect textureRect = bulletExplodeFrames[AnimControl.GetCurrentFrame()];
        TextureUtils::OnDraw(texture, renderer,
                             X- GCamera::CameraControl.GetX(), Y- GCamera::CameraControl.GetY(),
                             width, height,
                             &textureRect,
                             flip);
    }
}


void BulletEntity::OnRender(std::vector<SDL_Rect> &textureRects)
{
    GEntity::OnRender(textureRects);
}


bool BulletEntity::loadBulletExplosionDimensions(std::string animFile)
{
    const char* file = animFile.c_str();
    FILE* fileHandler = fopen(file, "r");
    if(fileHandler == NULL) {
        return false;
    }

    char tempName[255]="";
    fscanf(fileHandler, "%s\n", tempName);
    std::string frameSetImage(tempName);
    if(resourceManager->loadImg(frameSetImage, renderer) == NULL) {
        fclose(fileHandler);
        return false;
    }
    int frameSetSize = 0;
    fscanf(fileHandler, "%d\n", &frameSetSize);
    for(int i=0; i<frameSetSize; i++) {
        SDL_Rect rect;
        fscanf(fileHandler, "%d %d %d %d", &rect.x, &rect.y, &rect.w, &rect.h);
        bulletExplodeFrames.push_back(rect);
        fscanf(fileHandler, "\n");
    }
    fclose(fileHandler);
    bulletExplodeImage = frameSetImage;
    if(bulletExplodeFrames.empty()) {
        std::cout << "1 bullet explodes NULL" << '\n';
    }

    return true;
}
