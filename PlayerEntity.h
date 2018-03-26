#ifndef PLAYERENTITY_H_INCLUDED
#define PLAYERENTITY_H_INCLUDED

#include "GEntity.h"

class PlayerEntity : public GEntity
{
public:
    PlayerEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);
    bool OnLoad(int width, int height, int maxFrames);
    void OnLoop();
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(GEntity* entity);
    // clone method
    //GEntity* clone() const;
    bool Jump();
    // different render options
    void OnRender();
    void OnRender(bool isVertical);
    void OnRender(std::vector<SDL_Rect> &textureRects);

    //loading and getting animation frames
    std::string loadFrameDimensions(std::string frameSetName, std::string frameImageFile);
    void getFrameSet(std::string frameSetName);

private:
    std::vector<SDL_Rect>* currentFrameSet;
    std::map<std::string, std::string> frameImages;
    std::map<std::string, std::vector<SDL_Rect>> frameSet;

public:
    int health;
    bool knockback;
};

#endif // PLAYERENTITY_H_INCLUDED
