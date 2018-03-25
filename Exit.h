#ifndef RSPWN_BRKOUT_EXIT
#define RSPWN_BRKOUT_EXIT

#include "Definitions.h"

/**
 * This class holds the functions and variable that
 * are needed during the exit state of the game
 */
class Exit {
public:
	/**
	 * Constructor for Exit that initializes its member variables
	 */
	Exit(stack<State>	*gameStateStack,
		StringData		*stringData,
		SDL_Renderer*	renderer,
		Mix_Chunk*	menu_sound,
		Mix_Chunk*	select_sound);

	/**
	 * Empty destructor for Exit
	 */
	~Exit();

	/**
	 * Function to handle input in Menu Screen
	 */
	void HandleExitInput();

	/**
	 * Render exit text
	 */
	void SetExit();
private:

	/**
	 * Holds the input event by the user
	 */
	SDL_Event event;

	/**
	 * Game variables
	 */

	/**
	 * Holds the gameStateStack
	 */
	stack<State>	*gameStateStack = NULL;

	/**
	 * Holds the text data to be displayed
	 */
	StringData		*stringData = NULL;

	/**
	 * SDL variables
	 */
	SDL_Renderer*	renderer = NULL;

	/**
	 * Holds the music variable for menu sound
	 */
	Mix_Chunk*	menu_sound = NULL;

	/**
	 * Holds the music variable for select sound
	 */
	Mix_Chunk*	select_sound = NULL;
};

#endif
