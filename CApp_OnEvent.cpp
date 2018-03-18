#include "CApp.h"

void CApp::OnEvent(SDL_Event* event)
{
    if(event->type == SDL_QUIT) {
        running = false;
        return;
    }

    // other events
    eventHandler->OnEvent(event);
}
