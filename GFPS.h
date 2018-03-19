#ifndef GFPS_H_INCLUDED
#define GFPS_H_INCLUDED

#include <SDL.h>

class GFPS
{
public:
    static GFPS FPSControl;

private:
    int oldTime;
    int lastTime;
    float speedFactor;
    int numFrames;
    int frames;

public:
    GFPS();
    void OnLoop;
    int GetFPS();
    float GetSpeedFactor();
};

#endif // GFPS_H_INCLUDED
