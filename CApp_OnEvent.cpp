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
    case SDLK_ESCAPE:
        OnExit();
        break;
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
    case SDLK_SPACE:
        player1->Jump();
        // play sound
        resourceManager->playSoundEffect(PLAYER_JUMP_SOUND);
        //GCamera::CameraControl.OnMove(0, -15);
        break;
    case SDLK_DOWN:
        //GCamera::CameraControl.OnMove(0, 15);
        break;
    case SDLK_LSHIFT:
        player1->maxSpeedX = (P1_MAX_SPEED_X * 1.5);
        player1->maxSpeedY = (P1_MAX_SPEED_Y * 1.2);
        break;
    case SDLK_DELETE:
        player1->health -= 1;
        break;
    case SDLK_x:
    {
        BulletEntity* bullet = (BulletEntity*)bulletTemplate->clone();
        bullet->flags = ENTITY_FLAG_MAPONLY;
        if(player1->flip == SDL_FLIP_NONE)
        {
            bullet->X = (player1->X + player1->width - 20);
            bullet->moveRight = true;
        }
        else
        {
            bullet->X = player1->X - 20;
            bullet->moveLeft = true;
            bullet->flip = SDL_FLIP_HORIZONTAL;
        }
        bullet->Y = (player1->Y + 5);
        GEntity::EntityList.push_back(bullet);
        // play sound
        resourceManager->playSoundEffect(BULLET_FIRE_SOUND);
        break;
    }
    default:
    {}
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
    default:
    {}
    }
}


void CApp::OnExit()
{
    running = false;
    score = -1;
    timeText.str("");
    timeText << "EXIT";
}
