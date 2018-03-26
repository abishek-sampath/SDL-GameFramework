#ifndef ENEMYENTITY_H_INCLUDED
#define ENEMYENTITY_H_INCLUDED

#include "GEntity.h"

class EnemyEntity : public GEntity
{
public:
    EnemyEntity(SDL_Renderer* renderer, ResourceManager* resourceManager);
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

    bool loadEnemyAnim(std::string animFile);

private:
    std::vector<SDL_Rect> frameSet;
};


#endif // ENEMYENTITY_H_INCLUDED
