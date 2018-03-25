#ifndef GENTITY_H_INCLUDED
#define GENTITY_H_INCLUDED

#include <vector>

#include "GAnimation.h"
#include "GCamera.h"
#include "GArea.h"
#include "GFPS.h"
#include "TextureUtils.h"
#include "ResourceManager.h"

enum
{
    ENTITY_TYPE_GENERIC=0,
    ENTITY_TYPE_PLAYER
};

enum
{
    ENTITY_FLAG_NONE=0,
    ENTITY_FLAG_GRAVITY = 0x00000001,
    ENTITY_FLAG_GHOST = 0x00000002,
    ENTITY_FLAG_MAPONLY = 0x00000004
};

class GEntity
{
public:
    static std::vector<GEntity*> EntityList;

protected:
    GAnimation AnimControl;
    SDL_Texture* texture;
    SDL_Renderer* renderer = NULL;
    ResourceManager* resourceManager = NULL;

public:
    std::string name;
    float   X;
    float   Y;
    int     width;
    int     height;
    int     textureWidth;
    int     textureHeight;
    SDL_RendererFlip flip;
    //int     animState;

public:
    int flags;
    bool moveLeft;
    bool moveRight;

public:
    int type;
    bool dead;
    float maxSpeedX;
    float maxSpeedY;

protected:
    float speedX;
    float speedY;
    float accelX;
    float accelY;
    int currentFrameCol;
    int currentFrameRow;
    int collisionX;
    int collisionY;
    int collisionWidth;
    int collisionHeight;
    bool canJump;
    bool onGround;

public:
    GEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);
    virtual ~GEntity();

public:
    virtual bool OnLoad(const char* file, int width, int height, int textureWidth, int textureHeight, int maxFrames);
    virtual void OnLoop();
    virtual void OnCleanup();
    virtual void OnAnimate();
    virtual bool OnCollision(GEntity* entity);
    // clone method
    virtual GEntity* clone() const;
    // render methods
    virtual void OnRender();    // normal render with texture-rect x=0, y=0
    virtual void OnRender(bool isVertical); // render with texture-rect x and y in horizontal or vertical orders respectively
    virtual void OnRender(std::vector<SDL_Rect> &textureRects); // rencer with texture-rects from the array

public:
    void OnMove(float moveX, float moveY);
    void StopMove();
    bool Jump();

public:
    bool Collides(int oX, int oY, int oW, int oH);
    bool PosValid(int newX, int newY);
    bool PosValidTile(GTile* tile);
    bool PosValidEntity(GEntity* entity, int newX, int newY);
};



class GEntityCollision
{
public:
    static std::vector<GEntityCollision> EntityCollisonList;

public:
    GEntity* entityA;
    GEntity* entityB;

public:
    GEntityCollision();
};

#endif // CENTITY_H_INCLUDED
