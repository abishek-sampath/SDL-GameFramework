#ifndef CANIMATION_H_INCLUDED
#define CANIMATION_H_INCLUDED

#include <SDL.h>

class CAnimation
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
    CAnimation();
    void OnAnimate();

public:
    void SetFrameRate(int rate);
    void SetCurrentFrame(int frame);
    int GetCurrentFrame();
};


#endif // CANIMATION_H_INCLUDED
