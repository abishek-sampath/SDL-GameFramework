#ifndef RSPWN_BRKOUT_MENU
#define RSPWN_BRKOUT_MENU

#include "Definitions.h"

/**
 * This class implements the Menu screen
 */
class Menu {
public:
	/**
	 * Constructor - Initialize Menu components
	 */
	Menu(stack<State>	*gameStateStack,
		StringData		*stringData,
		SDL_Renderer*	renderer,
		SDL_Color		*blueColor,
		SDL_Color		*yellowColor,
		SDL_Color		*greenColor,
		SDL_Color		*whiteColor,
		Mix_Music*	bg_music,
		Mix_Chunk*	menu_sound,
		Mix_Chunk*	select_sound);

	/**
	 * Destroyer - Free all Menu components
	 */
	~Menu();

	/**
	 * Load language pack, English, French or Spanish
	 */
	bool loadMenuLanguage(int lang_type);

	/**
	 * Function to load Menu option textures
	 */
	void loadMenuTextures();

	/**
	 * Function to handle input in Menu Screen
	 */
	void HandleMenuInput();

	/**
	 * Render Menu text
	 */
	void SetMenu();

	/**
	 * Render menu background
	 */
	void SetMenuBackground();

	/**
	 * Reset previous language texture
	 */
	void ResetLangTexture(short langOption, SDL_Color *color);

	/**
	 * Reset previous menu texture
	 */
	void ResetMenuTexture(short menuOption, SDL_Color *color);

private:

	/**
	 * Points to the background texture
	 */
	SDL_Texture*		menuBackgroundtexture = NULL;

	/**
	 * Holds the input event by the user
	 */
	SDL_Event			event;

	/**
	 * Holds the current menu option index
	 */
	short				currentMenuOption;

	/**
	 * Holds the current language option index
	 */
	short				currentLangOption;

	/**
	 * Flag to see if the menu option was changed
	 */
	bool				menuOptionChanged;

	/**
	 * Flag to see if the language option was changed
	 */
	bool				langOptionChanged;

	// Game variables //

	/**
	 * Points to the gameStateStack
	 */
	stack<State>	*gameStateStack = NULL;

	/**
	 * Points to the text string data to be displayed
	 */
	StringData		*stringData = NULL;

	// SDL variables //

	/**
	 * Points to the SDL renderer
	 */
	SDL_Renderer*	renderer = NULL;

	/**
	 * Points to the SDL window
	 */
	SDL_Window*		window = NULL;

	// Color Variables

	/**
	 * Points to the blue color
	 */
	SDL_Color		*blueColor = NULL;

	/**
	 * Points to the yellow color
	 */
	SDL_Color		*yellowColor = NULL;

	/**
	 * Points to the green color
	 */
	SDL_Color		*greenColor = NULL;

	/**
	 * Points to the white color
	 */
	SDL_Color		*whiteColor = NULL;

	// Music variables

	/**
	 * Points to the background music
	 */
	Mix_Music*	bg_music = NULL;

	/**
	 * Points to the menu sound
	 */
	Mix_Chunk*	menu_sound = NULL;

	/**
	 * Points to the select sound
	 */
	Mix_Chunk*	select_sound = NULL;

};

#endif
