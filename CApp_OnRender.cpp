#include "CApp.h"
#include <string>
#include <iostream>

void CApp::OnRender()
{
//    for(unsigned int i=0; i < CEntity::entityList.size(); i++) {
//        if(!CEntity::entityList[i])
//            continue;
//        CEntity::entityList[i]->OnRender(texRectsMap[i+1]);
//    }

    GArea::AreaControl.OnRender(GCamera::CameraControl.GetX(),
                                GCamera::CameraControl.GetY());

    SDL_RenderPresent(renderer);
}


//TextureUtils::OnDraw(ANIM_2, renderer, resourceManager,
//           290, 220,100, 50,
//           Anim.GetCurrentFrame()*75, 0, 75, 132);
