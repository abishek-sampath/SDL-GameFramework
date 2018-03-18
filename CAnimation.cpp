#include "CAnimation.h"

CAnimation::CAnimation()
{
    currentFrame = 0;
    maxFrames    = 0;
    frameInc     = 1;
    frameRate    = 100; //milliseconds
    oldTime      = 0;
    oscillate   = false;
}


void CAnimation::OnAnimate()
{
    if((oldTime + frameRate) > SDL_GetTicks()) {
        return;
    }

    oldTime = SDL_GetTicks();
    currentFrame += frameInc;

    if(oscillate) {
        if(frameInc > 0) {
            if(currentFrame >= maxFrames) {
                frameInc = -frameInc;
            }
        }
        else {
            if(currentFrame <= 0) {
                frameInc = -frameInc;
            }
        }
    }
    else {
        if(currentFrame >= maxFrames) {
            currentFrame = 0;
        }
    }
}


void CAnimation::SetFrameRate(int rate)
{
    frameRate = rate;
}


void CAnimation::SetCurrentFrame(int frame)
{
    if(frame < 0 || frame >= maxFrames)
        return;

    currentFrame = frame;
}


int CAnimation::GetCurrentFrame()
{
    return currentFrame;
}
