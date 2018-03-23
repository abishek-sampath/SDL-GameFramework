#ifndef TEXTUREUTILS_H_INCLUDED
#define TEXTUREUTILS_H_INCLUDED

#include <SDL.h>
#include "ResourceManager.h"

class TextureUtils
{

public:

    static bool OnDraw(std::string file, SDL_Renderer* renderer, ResourceManager* resourceManager,
                int X, int Y, int W, int H)
    {
        SDL_Texture* texture = resourceManager->loadImg(file, renderer);
        if(texture == NULL)
        {
            return false;
        }
        SDL_Rect rect;
        rect.x = X;
        rect.y = Y;
        rect.w = W;
        rect.h = H;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        return true;
    }


    static bool OnDraw(std::string file, SDL_Renderer* renderer, ResourceManager* resourceManager,
                int X, int Y, int W, int H, int X2, int Y2, int W2, int H2)
    {
        SDL_Texture* texture = resourceManager->loadImg(file, renderer);
        if(texture == NULL)
        {
            return false;
        }
        SDL_Rect windowRect;
        windowRect.x = X;
        windowRect.y = Y;
        windowRect.w = W;
        windowRect.h = H;
        SDL_Rect textureRect;
        textureRect.x = X2;
        textureRect.y = Y2;
        textureRect.w = W2;
        textureRect.h = H2;

        SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);
        return true;
    }


    static bool OnDraw(SDL_Texture* texture, SDL_Renderer* renderer,
                int X, int Y, int W, int H, int X2, int Y2, int W2, int H2)
    {
        if(texture == NULL)
        {
            return false;
        }
        SDL_Rect windowRect;
        windowRect.x = X;
        windowRect.y = Y;
        windowRect.w = W;
        windowRect.h = H;
        SDL_Rect textureRect;
        textureRect.x = X2;
        textureRect.y = Y2;
        textureRect.w = W2;
        textureRect.h = H2;

        SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);
        return true;
    }


    static bool OnDraw(SDL_Texture* texture, SDL_Renderer* renderer,
                int X, int Y, int W, int H, SDL_Rect* textureRect, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        if(texture == NULL)
        {
            return false;
        }
        SDL_Rect windowRect;
        windowRect.x = X;
        windowRect.y = Y;
        windowRect.w = textureRect->w;
        windowRect.h = textureRect->h;

        SDL_RenderCopyEx(renderer, texture, textureRect, &windowRect,  0, NULL, flip);
        return true;
    }


};

#endif // TEXTUREUTILS_H_INCLUDED
