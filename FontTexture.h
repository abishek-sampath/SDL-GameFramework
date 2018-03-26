#ifndef RSPWN_BRKOUT_FONTTEX
#define RSPWN_BRKOUT_FONTTEX

//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

/**
 * Texture wrapper class
 */
class FontTexture
{
public:
	/**
	 * Initializes variables
	 */
	FontTexture();

	/**
	 * Deallocates memory
	 */
	~FontTexture();

	/**
	 * Creates image from font string
	 */
	bool loadFromRenderedText(SDL_Renderer* renderer, std::string textureText,
		SDL_Color &textColor, TTF_Font* font, int wrapLength);

	/**
	 * Deallocates texture
	 */
	void freeFontTexture();

	/**
	 * Set color modulation
	 */
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	/**
	 * Set color modulation
	 */
	void setColor(SDL_Color &color);

	/**
	 * Set blending function
	 */
	void setBlendMode(SDL_BlendMode blending);

	/**
	 * Set alpha modulation
	 */
	void setAlpha(Uint8 alpha);

	/**
	 * Renders texture at given point
	 */
	void render(SDL_Renderer* renderer, int x, int y,
		SDL_Rect* clip = NULL, double angle = 0.0,
		SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/**
	 * Gets image width dimension
	 */
	int getWidth();

	/**
	 * Gets image height dimension
	 */
	int getHeight();

private:
	/**
	 * The actual hardware texture
	 */
	SDL_Texture * fontTexture;

	/**
	 * Image width dimensions
	 */
	int mWidth;

	/**
	 * Image height dimensions
	 */
	int mHeight;
};



#endif
