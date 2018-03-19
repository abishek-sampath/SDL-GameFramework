#include "GCamera.h"

GCamera GCamera::CameraControl;


GCamera::GCamera()
{
    x = y = 0;
    targetX = targetY = NULL;
    targetMode = TARGET_MODE_NORMAL;
}


void GCamera::OnMove(int moveX, int moveY)
{
    x += moveX;
    y += moveY;
}


int GCamera::GetX()
{
    if(targetX != NULL) {
        if(targetMode == TARGET_MODE_CENTER) {
            return *targetX - (SCREEN_WIDTH / 2);
        }
        return *targetX;
    }
    return x;
}


int GCamera::GetY()
{
    if(targetY != NULL) {
        if(targetMode == TARGET_MODE_CENTER) {
            return *targetY - (SCREEN_WIDTH / 2);
        }
        return *targetY;
    }
    return y;
}


void GCamera::SetPos(int X, int Y)
{
    this->x = X;
    this->y = Y;
}


void GCamera::SetTarget(int* X, int* Y)
{
    targetX = X;
    targetY = Y;
}
