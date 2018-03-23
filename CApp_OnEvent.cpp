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
    case SDLK_LEFT:
        player1->moveLeft = true;
        player1->flip = SDL_FLIP_HORIZONTAL;
        //GCamera::CameraControl.OnMove(-15, 0);
        break;
    case SDLK_RIGHT:
        player1->moveRight = true;
        player1->flip = SDL_FLIP_NONE;
        //GCamera::CameraControl.OnMove(15, 0);
        break;
    case SDLK_UP:
        //GCamera::CameraControl.OnMove(0, -15);
        break;
    case SDLK_DOWN:
        //GCamera::CameraControl.OnMove(0, 15);
        break;
    case SDLK_LSHIFT:
        player1->maxSpeedX = (P1_MAX_SPEED_X * 2);
        player1->maxSpeedY = (P1_MAX_SPEED_Y * 2);
        break;
    case SDLK_SPACE:
        player1->Jump();
        break;
    default: {}
    }
}


void CApp::OnKeyUp(SDL_Keycode &sym, Uint16 &mod)
{
    switch(sym)
    {
    case SDLK_LEFT:
        player1->moveLeft = false;
        break;
    case SDLK_RIGHT:
        player1->moveRight = false;
        break;
    case SDLK_LSHIFT:
        player1->maxSpeedX = P1_MAX_SPEED_X;
        player1->maxSpeedY = P1_MAX_SPEED_Y;
        break;
    default:{}
    }
}


void CApp::OnExit()
{
    running = false;
}
