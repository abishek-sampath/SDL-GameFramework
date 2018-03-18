#include "CApp.h"

#undef main


CApp::CApp() {
    // SDL resources
    window = NULL;
    renderer = NULL;

    // User Resources
    resourceManager = NULL;
    eventHandler = NULL;

    running = true;
}

int CApp::OnExecute() {
    if(OnInit() == false) {
        printf("Initialization failed!\n");
        return -1;
    }

    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            OnEvent(&event);
        }

        OnLoop();

        OnRender();
    }

    OnCleanup();

    return 0;
}

int main(int argc, char* argv[])
{
    CApp theApp;
    return theApp.OnExecute();
}
