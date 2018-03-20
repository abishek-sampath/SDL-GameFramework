#ifndef GCAMERA_H_INCLUDED
#define GCAMERA_H_INCLUDED

#include <SDL.h>
#include "Definitions.h"

enum
{
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};


class GCamera
{
public:
    static GCamera CameraControl;

private:
    int x;
    int y;
    float* targetX;
    float* targetY;

public:
    int targetMode;

public:
    GCamera();
    void OnMove(int moveX,int moveY);
    int GetX();
    int GetY();
    void SetPos(int X, int Y);
    void SetTarget(float* X, float* Y);
};

#endif // GCAMERA_H_INCLUDED
