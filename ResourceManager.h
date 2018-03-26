#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include <SDL_image.h>
#include <string>
#include <map>
#include <iostream>

#include "Definitions.h"

/**
 * Implements the resource manager functions
 */
class ResourceManager {

private:
    SDL_Renderer* renderer = NULL;

    /**
	 * private constructor
	 */
    ResourceManager(SDL_Renderer* renderer)
    {
	    this->renderer = renderer;
    }

public:

	/**
	 * Creating a single instance of the ResourceManager
	 */
	static ResourceManager* instance(SDL_Renderer* renderer) {
		static ResourceManager* instance = new ResourceManager(renderer);
		return instance;
	}

	/**
	 * This function laods the image resource onto memory if it does not exist
	 * after which the same image path is returned.
	 */
	SDL_Texture* loadImg(std::string imgFile, SDL_Renderer* renderer) {
		std::map<std::string, SDL_Texture*>::iterator it = imageResourceMap.find(imgFile);
		// if already in the map
		if (it != imageResourceMap.end()) {
			// SDL_Log("Loaded from resource manager.");
			return it->second;
		}
		// if not, load it and add it
		else {
            std::cout << "Loading Image : " << imgFile << "\n";
			SDL_Surface* img = IMG_Load(imgFile.c_str());
			if (img == NULL) {
                printf("Failed to allocate surface\n");
				SDL_Log("Failed to allocate surface");
				return NULL;
			}
			// SDL_Log("Adding ", imgFile.c_str(), "to map");
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
			imageResourceMap.insert(std::pair<std::string, SDL_Texture*>(imgFile, texture));
			SDL_FreeSurface(img);
			return texture;
		}
	}

	/**
	 * This function laods the image resource onto memory if it does not exist
	 * after which the same image path is returned.
	 */
	SDL_Texture* loadImg(std::string imgFile, SDL_Renderer* renderer, int r, int g, int b) {
		std::map<std::string, SDL_Texture*>::iterator it = imageResourceMap.find(imgFile);
		// if already in the map
		if (it != imageResourceMap.end()) {
			// SDL_Log("Loaded from resource manager.");
			return it->second;
		}
		// if not, load it and add it
		else {
			SDL_Surface* img = IMG_Load(imgFile.c_str());
			if (img == NULL) {
                printf("Failed to allocate surface\n");
				SDL_Log("Failed to allocate surface");
				return NULL;
			}
			else {
                //color key the image
                SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, r, g, b));
			}
			// SDL_Log("Adding ", imgFile.c_str(), "to map");
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
			imageResourceMap.insert(std::pair<std::string, SDL_Texture*>(imgFile, texture));
			SDL_FreeSurface(img);
			return texture;
		}
	}



    bool loadFontTexture(FontTexture &texture, std::string text, SDL_Color *color, int fontSize, int wrapLength = SCREEN_WIDTH)
    {
        //Loading success flag
        bool success = true;

        //Open the font
        TTF_Font* font = TTF_OpenFont(GAME_FONT_NAME, fontSize);
        if (font == NULL)
        {
            printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
        else
        {
            //Render text
            //SDL_Color textColor = { 0, 0, 0 };
            if (!texture.loadFromRenderedText(renderer, text, *color, font, wrapLength))
            {
                printf("Failed to render text texture!\n");
                success = false;
            }
        }

        TTF_CloseFont(font);

        return success;
    }



	void clearResource()
	{
	    for(auto&& entry : imageResourceMap) {
            SDL_DestroyTexture(entry.second);
            entry.second = NULL;
	    }
	    imageResourceMap.clear();
	}

private:
	/**
	 * Constructor of ResourceManager, private because it is Singleton
	 */
	ResourceManager() {}

	/**
	 * Destructor of ResourceManager, private because it is Singleton
	 */
	~ResourceManager() {}

	/**
	 * Map to hold loaded resources
	 */
	std::map<std::string, SDL_Texture*> imageResourceMap;
};



#endif // RESOURCEMANAGER_H_INCLUDED
