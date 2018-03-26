#ifndef LIFEUPGRADEENTITY_H_INCLUDED
#define LIFEUPGRADEENTITY_H_INCLUDED

#include "GEntity.h"

class LifeUpgradeEntity : public GEntity
{
public:
    LifeUpgradeEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);
    bool OnLoad(std::string animFile, int width, int height);
    void OnLoop();
    void OnCleanup();
    void OnAnimate();
    bool OnCollision(GEntity* entity);
    // clone method
    GEntity* clone() const;
    // render options
    void OnRender();
    void OnRender(bool isVertical);
    void OnRender(std::vector<SDL_Rect> &textureRects);

    bool loadLifeAnim(std::string animFile);

private:
    bool lifeUsed;
    std::vector<SDL_Rect> frameSet;
};

#endif // LIFEUPGRADEENTITY_H_INCLUDED
