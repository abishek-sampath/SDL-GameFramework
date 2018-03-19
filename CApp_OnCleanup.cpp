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
    for(unsigned int i=0; i < CEntity::entityList.size(); i++) {
        if(!CEntity::entityList[i])
            continue;
        CEntity::entityList[i]->OnCleanup();
    }
    CEntity::entityList.clear();

    // cleanup SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}
