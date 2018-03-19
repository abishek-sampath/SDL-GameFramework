#include "CApp.h"

void CApp::OnEvent(SDL_Event* event)
{
//    if(event->type == SDL_QUIT) {
//        running = false;
//        return;
//    }
//
//    // other events
//    eventHandler->OnEvent(event);
    GEvent::OnEvent(event);
}


void CApp::OnKeyDown(SDL_Keycode &sym, Uint16 &mod)
{
    switch(sym)
    {
//    case SDLK_UP:
//        GCamera::CameraControl.OnMove(0, 10);
//        break;
//    case SDLK_DOWN:
//        GCamera::CameraControl.OnMove(0, -10);
//        break;
//    case SDLK_LEFT:
//        GCamera::CameraControl.OnMove(10, 0);
//        break;
//    case SDLK_RIGHT:
//        GCamera::CameraControl.OnMove(-10, 0);
//        break;
    default: {

        }
    }
}


void CApp::OnExit()
{
    running = false;
}
