#include "GEntity.h"
#include "TextureUtils.h"


std::vector<GEntity*>  GEntity::EntityList;

std::vector<GEntityCollision>  GEntityCollision::EntityCollisonList;


GEntityCollision::GEntityCollision()
{
    entityA = NULL;
    entityB = NULL;
}


GEntity::GEntity(SDL_Renderer* renderer, ResourceManager* resourceManager)
{
    this->texture = NULL;
    this->renderer = renderer;
    this->resourceManager = resourceManager;

    X = Y = 0;
    width = height = 0;
    moveLeft = moveRight = false;

    type = ENTITY_TYPE_GENERIC;
    dead = false;
    flags = ENTITY_FLAG_GRAVITY;

    speedX = speedY = 0;
    accelX = accelY = 0;
    maxSpeedX = maxSpeedY = 5;

    currentFrameCol = currentFrameRow = 0;

    collisionX = collisionY = 0;
    collisionWidth = collisionHeight = 0;
}


GEntity::~GEntity()
{

}


bool GEntity::OnLoad(const char* file, int width, int height, int maxFrames)
{
    if((texture = resourceManager->loadImg(file, renderer)) == NULL) {
        return false;
    }

    this->width = width;
    this->height = height;
    AnimControl.maxFrames = maxFrames;

    return true;
}


void GEntity::OnLoop()
{
    // not moving
    if(moveLeft == false && moveRight == false) {
        StopMove();
        // ** -->check this if doesnt work
//        if(speedX == 0 && speedY == 0) {
//            return;
//        }
    }

    if(moveLeft) {
        accelX = -0.25;
    }

    if(moveRight) {
        accelX = 0.25;
    }

    if(flags & ENTITY_FLAG_GRAVITY) {
        accelY = 0.75;
    }

    speedX += accelX * GFPS::FPSControl.GetSpeedFactor();
    speedY += accelY * GFPS::FPSControl.GetSpeedFactor();

    //std::cout << "MAXSPEED : " << maxSpeedX << "\n";
    if(speedX > maxSpeedX)
        speedX = maxSpeedX;
    if(speedX < -maxSpeedX)
        speedX = -maxSpeedX;
    if(speedY > maxSpeedY)
        speedY = maxSpeedY;
    if(speedY < -maxSpeedY)
        speedY = -maxSpeedY;

    OnAnimate();
    OnMove(speedX, speedY);
}


void GEntity::OnRender()
{
    if(texture == NULL) {
        return;
    }
    TextureUtils::OnDraw(texture, renderer,
           X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),
           0, 0,
           width, height);
}


void GEntity::OnRender(bool isVertical)
{
    if(texture == NULL)
    {
        return;
    }
    if(isVertical)
        TextureUtils::OnDraw(texture, renderer,
                             X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),
                             currentFrameCol * width, (currentFrameRow + AnimControl.GetCurrentFrame()) * height,
                             width, height);
    else
        TextureUtils::OnDraw(texture, renderer,
                             X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),
                             (currentFrameRow + AnimControl.GetCurrentFrame()) * width, currentFrameCol * height,
                             width, height);
}


void GEntity::OnRender(std::vector<SDL_Rect> &textureRects)
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
                             &textureRect);
    }
    else
    {
        TextureUtils::OnDraw(texture, renderer,
                             X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),
                             0, 0,
                             width, height);
    }
}


void GEntity::OnCleanup()
{
    texture = NULL;
    renderer = NULL;
    resourceManager = NULL;
}


void GEntity::OnAnimate()
{
    if(moveLeft) {
        currentFrameCol = 0;
    }
    else if(moveRight) {
        currentFrameCol = 1;
    }

    AnimControl.OnAnimate();
}


// to be implemented in an overridden class
void GEntity::OnCollision(GEntity* entity)
{

}


void GEntity::OnMove(float moveX, float moveY)
{
    if(moveX == 0 && moveY == 0) {
        return;
    }

    double newX = 0;
    double newY = 0;

    moveX *= GFPS::FPSControl.GetSpeedFactor();
    moveY *= GFPS::FPSControl.GetSpeedFactor();

    if(moveX != 0) {
        if(moveX > 0)
            newX = GFPS::FPSControl.GetSpeedFactor();
        else
            newX = -GFPS::FPSControl.GetSpeedFactor();
    }

    if(moveY != 0) {
        if(moveY > 0)
            newY = GFPS::FPSControl.GetSpeedFactor();
        else
            newY = -GFPS::FPSControl.GetSpeedFactor();
    }

    while(true) {
        if(flags & ENTITY_FLAG_GHOST) {
            PosValid((int)(X + newX), (int)(Y + newY)); // collision not considered
            X += newX;
            Y += newY;
        }
        else{
            if(PosValid((int)(X + newX), (int)(Y))) {
                X += newX;
            }
            else {
                speedX = 0;
            }

            if(PosValid((int)(X), (int)(Y + newY))) {
                Y += newY;
            }
            else {
                speedY = 0;
            }
        }

        moveX += -newX;
        moveY += -newY;

        if(newX > 0 && moveX <= 0) newX = 0;
        if(newX < 0 && moveX >= 0) newX = 0;

        if(newY > 0 && moveY <= 0) newY = 0;
        if(newY < 0 && moveY >= 0) newY = 0;

        if(moveX == 0) newX = 0;
        if(moveY == 0) newY = 0;

        if(moveX == 0 && moveY == 0)
            break;
        if(newX == 0 && newY == 0)
            break;
    }
}



void GEntity::StopMove()
{
    if(speedX > 0) {
        accelX = -1;
    }
    if(speedX < 0) {
        accelX = 1;
    }
    if(speedX < 2.0f && speedX > -2.0f) {
        accelX = 0;
        speedX = 0;
    }
}


bool GEntity::Collides(int oX, int oY, int oW, int oH)
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    int tX = (int)X + collisionX;
    int tY = (int)Y + collisionY;

    left1 = tX;
    left2 = oX;

    right1 = left1 + width - 1 - collisionWidth;
    right2 = left2 + oW - 1;

    top1 = tY;
    top2 = oY;

    bottom1 = top1 + height - 1 - collisionHeight;
    bottom2 = top2 + oH - 1;

    if (bottom1 < top2) return false;
    if (right1 < left2) return false;
    if (top1 > bottom2) return false;
    if (left1 > right2) return false;

    return true;
}



bool GEntity::PosValid(int newX, int newY)
{
    bool isValid = true;
    int startX  = (newX + collisionX) / TILE_SIZE;
    int startY  = (newY + collisionY) / TILE_SIZE;
    int endX    = ((newX + collisionX) + width - collisionWidth - 1) / TILE_SIZE;
    int endY    = ((newY + collisionY) + height - collisionHeight - 1) / TILE_SIZE;

    for(int tempY = startY; tempY <= endY; tempY++) {
        for(int tempX = startX; tempX <= endX; tempX++) {
            GTile* tile = GArea::AreaControl.GetTile(tempX * TILE_SIZE, tempY * TILE_SIZE);
            if(PosValidTile(tile) == false) {
                isValid = false;
            }
        }
    }

    if( !(flags & ENTITY_FLAG_MAPONLY) ) {
        for(unsigned int i = 0; i < EntityList.size(); i++) {
            if(PosValidEntity(EntityList[i], newX, newY) == false) {
                isValid = false;
            }
        }
    }

    return isValid;
}



bool GEntity::PosValidTile(GTile* tile)
{
    if(tile == NULL) {
        return true;
    }

    if(tile->TypeID == TILE_TYPE_BLOCK) {
        return false;
    }

    return true;
}



bool GEntity::PosValidEntity(GEntity* entity, int newX, int newY)
{
    if(this != entity && entity != NULL && entity->dead == false
       && entity->flags ^ ENTITY_FLAG_MAPONLY
       && entity->Collides(newX + collisionX, newY + collisionY, width - collisionWidth - 1, height - collisionHeight - 1)
            == true) {
                GEntityCollision entityCollision;

                entityCollision.entityA = this;
                entityCollision.entityB = entity;

                GEntityCollision::EntityCollisonList.push_back(entityCollision);

                return false;
            }

            return true;
}
