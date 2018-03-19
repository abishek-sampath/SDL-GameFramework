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
    static std::vector<GEntity*> entityList;

protected:
    GAnimation Anim_Control;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    ResourceManager* resourceManager = NULL;

public:
    float   X;
    float   Y;
    int     width;
    int     height;
    //int     animState;
    bool moveLeft;
    bool moveRight;

public:
    int type;
    int flags;
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

public:
    GEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);
    virtual ~GEntity();

public:
    virtual bool OnLoad(const char* file, int width, int height, int maxFrames);
    virtual void OnLoop();
    virtual void OnCleanup();
    // render methods
    virtual void OnRender();    // normal render with texture-rect x=0, y=0
    virtual void OnRender(bool isVertical); // render with texture-rect x and y in horizontal or vertical orders respectively
    virtual void OnRender(std::vector<SDL_Rect> &textureRects); // rencer with texture-rects from the array
};

#endif // CENTITY_H_INCLUDED
