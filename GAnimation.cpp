#include "GAnimation.h"

GAnimation::GAnimation()
{
    currentFrame = 0;
    maxFrames    = 0;
    frameInc     = 1;
    frameRate    = 100; //milliseconds
    oldTime      = 0;
    oscillate   = false;
}


void GAnimation::OnAnimate()
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


void GAnimation::SetFrameRate(int rate)
{
    frameRate = rate;
}


void GAnimation::SetCurrentFrame(int frame)
{
    if(frame < 0 || frame >= maxFrames)
        return;

    currentFrame = frame;
}


int GAnimation::GetCurrentFrame()
{
    return currentFrame;
}
