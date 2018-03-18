#ifndef CAPP_H_INCLUDED
#define CAPP_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <unordered_map>

#include "CEvent.h"
#include "CAnimation.h"
#include "CEntity.h"

#include "ResourceManager.h"
#include "TextureUtils.h"
#include "Definitions.h"


class CApp {
private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    CEntity*    Entity1 = NULL;
    CEntity*    Entity2 = NULL;

private:
    CEvent* eventHandler;
    ResourceManager* resourceManager;
    std::unordered_map<int, std::vector<SDL_Rect>> texRectsMap;

public:
    CApp();
    int OnExecute();

public:
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif // CAPP_H_INCLUDED
