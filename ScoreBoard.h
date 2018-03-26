#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

#include <sstream>

#include "Definitions.h"
#include "ResourceManager.h"


/**
 * This class holds the functions and variable that
 * are needed during the scoreboard state of the game
 */
class ScoreBoard {
public:
	/**
	 * Constructor for ScoreBoard that initializes its member variables
	 */
	ScoreBoard(stack<State>	*gameStateStack,
		SDL_Renderer*	renderer,
		ResourceManager* resourceManager);

	/**
	 * Empty destructor for ScoreBoard
	 */
	~ScoreBoard();

	/**
	 * Function to handle input in ScoreBoard Screen
	 */
	void HandleScoreBoardInput();

	/**
	 * Render ScoreBoard text
	 */
	void SetScoreBoard();
private:

	/**
	 * Holds the input event by the user
	 */
	SDL_Event e;

	/**
	 * Holds the gameStateStack
	 */
	stack<State>	*gameStateStack = NULL;

	/**
	 * SDL variables
	 */
	SDL_Renderer*	renderer = NULL;

	/**
	 * Resource Manager
	 */
	ResourceManager* resourceManager;

};


#endif // SCOREBOARD_H_INCLUDED
