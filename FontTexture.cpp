#include "FontTexture.h"

/**
 * Initializes variables
 */
FontTexture::FontTexture()
{
	//Initialize
	fontTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

/**
 * Deallocates memory
 */
FontTexture::~FontTexture()
{
	//Deallocate
	freeFontTexture();
}

/**
 * Creates image from font string
 */
bool FontTexture::loadFromRenderedText(SDL_Renderer* renderer, std::string &textureText, SDL_Color &textColor, TTF_Font* font)
{
	//Get rid of preexisting texture
	freeFontTexture();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		fontTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (fontTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return fontTexture != NULL;
}

/**
 * Deallocates texture
 */
void FontTexture::freeFontTexture()
{
	//Free texture if it exists
	if (fontTexture != NULL)
	{
		SDL_DestroyTexture(fontTexture);
		fontTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

/**
 * Set color modulation
 */
void FontTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(fontTexture, red, green, blue);
}

/**
 * Set color modulation
 */
void FontTexture::setColor(SDL_Color &color)
{
	setColor(color.r, color.g, color.b);
}

/**
 * Set blending function
 */
void FontTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(fontTexture, blending);
}

/**
 * Modulate texture alpha
 */
void FontTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(fontTexture, alpha);
}

/**
 * Renders texture at given point
 */
void FontTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, fontTexture, clip, &renderQuad, angle, center, flip);
}

/**
 * Gets image width dimension
 */
int FontTexture::getWidth()
{
	return mWidth;
}

/**
 * Gets image height dimension
 */
int FontTexture::getHeight()
{
	return mHeight;
}

