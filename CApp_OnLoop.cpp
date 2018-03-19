#include "CApp.h"

//361

void CApp::OnLoop()
{
    // clear renderer foe next loop
    SDL_RenderClear(renderer);

    for(unsigned int i=0; i < GEntity::entityList.size(); i++) {
        if(!GEntity::entityList[i])
            continue;
        GEntity::entityList[i]->OnLoop();
    }
}





//void CApp::OnLoop()
//{
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_RenderClear(renderer);
//
//    texture = resourceManager->loadImg("images/capguy-walk.png", renderer);
//    SDL_Rect windowRect = {0,0,140,200};
//    SDL_Rect textureRect;
//    textureRect.x = 0;
//    textureRect.y = 0;
//    SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
//    textureRect.w /= 8;
//
//    //Total number of frames of the animation
//        int totalFrames = 8;
//
//        //Amount of delay in milliseconds for each frame
//        int delayPerFrame = 50;
//
//        //SDL_GetTicks() method gives us the time in milliseconds
//
//        //'frame' will give us the index of frame we want to render
//        //For example, if 'frame' is 2, it will give us the third frame
//       int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
//
//    //The index of frame is multiplied by the width of the frame
//        //This will give us the appropriate
//        //frame dimensions from the sprite sheet
//        textureRect.x = frame * textureRect.w;
//
//
//
//    SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);
//}

