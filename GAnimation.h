#ifndef GANIMATION_H_INCLUDED
#define GANIMATION_H_INCLUDED

#include <SDL.h>

class GAnimation
{
private:
    int currentFrame;
    int frameInc;

private:
    int frameRate;
    uint64_t oldTime;

public:
    int maxFrames;
    bool oscillate;

public:
    GAnimation();
    void OnAnimate();

public:
    void SetFrameRate(int rate);
    void SetCurrentFrame(int frame);
    int GetCurrentFrame();
};


#endif // GANIMATION_H_INCLUDED
