#include "CApp.h"

void CApp::OnCleanup()
{
//    for(auto&& textRects : texRectsMap) {
//        textRects.second.clear();
//    }

    GArea::AreaControl.OnCleanup();

    // cleanup resource manager
    resourceManager->clearResource();

    // cleanup entities
    for(unsigned int i=0; i < GEntity::entityList.size(); i++) {
        if(!GEntity::entityList[i])
            continue;
        GEntity::entityList[i]->OnCleanup();
    }
    GEntity::entityList.clear();

    // cleanup SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}
