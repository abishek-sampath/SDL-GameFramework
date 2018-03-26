#include "CApp.h"

#undef main


CApp::CApp() {
    // SDL resources
    window = NULL;
    renderer = NULL;

    // User Resources
    resourceManager = NULL;

    running = true;
    score = 0;
    beginTime = 0;
    numb_lives_to_gen = PLAYER_MAX_HEALTH - 2;
    generateLives = true;
}


CApp::CApp(SDL_Renderer* renderer, ResourceManager* resourceManager)
{
    // SDL resources
    window = NULL;
    this->renderer = renderer;

    // User Resources
    this->resourceManager = resourceManager;

    running = true;
    score = 0;
    beginTime = 0;
    numb_lives_to_gen = PLAYER_MAX_HEALTH - 2;
    generateLives = true;
}


int CApp::OnExecute() {
    if(OnInit() == false) {
        printf("Initialization failed!\n");
        OnCleanup();
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


    if(score != -1) {
        // START display GameLost
        SDL_RenderClear(renderer);
        SDL_Color	whiteColor = { 0xff, 0xff, 0xff };
        FontTexture endMsgTexture;
        FontTexture endTexture;
        std::stringstream endMsg;
        endMsg << GAME_END_1 << score << GAME_END_2 << timeText.str() << GAME_END_3;
        resourceManager->loadFontTexture(endMsgTexture, endMsg.str(), &whiteColor, FONT_SIZE_SMALL, (SCREEN_WIDTH * 0.9));
        endMsgTexture.render(renderer, (SCREEN_WIDTH * 0.05), (SCREEN_HEIGHT * 0.3));
        resourceManager->loadFontTexture(endTexture, GAME_END, &whiteColor, FONT_SIZE_SMALL, (SCREEN_WIDTH * 0.9));
        endTexture.render(renderer, (SCREEN_WIDTH * 0.05), (SCREEN_HEIGHT * 0.9));
        SDL_RenderPresent(renderer);
        SDL_Event e;
        // remove events during delay
        SDL_Delay(1000);
        SDL_PumpEvents();
        SDL_FlushEvent(SDL_KEYDOWN | SDL_QUIT);
        while(SDL_WaitEvent(&e))
        {
            if (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)
            {
                break;
            }
        }
        // set elaped time in milliseconds
        beginTime = SDL_GetTicks() - beginTime;
        // END display GameLost
    }


    OnCleanup();

    return 0;
}

int main2(int argc, char* argv[])
{
    CApp theApp;
    return theApp.OnExecute();
}



int CApp::GetFinalScore()
{
    return score;
}


Uint32 CApp::GetFinalTime()
{
    return beginTime;
}
