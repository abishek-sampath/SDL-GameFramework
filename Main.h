#ifndef RSPWN_BRKOUT_MAIN
#define RSPWN_BRKOUT_MAIN

#include "Menu.h"
#include "ScoreBoard.h"
#include "CApp.h"
#include "Exit.h"
#include "Definitions.h"

#undef main

// Instance Variables //
/**
 * Points to the menu object
 */
Menu*	menuObj		= NULL;

/**
 * Points to the menu object
 */
ScoreBoard*	scoreObj	= NULL;

/**
 * Points to the exit object
 */
Exit*	exitObj		= NULL;


// game variables //

/**
 * Holds the gameStateStack
 */
stack<State>	*gameStateStack;

/**
 * Holds the string text data to be displayed
 */
StringData*		stringData;

// SDL variables //

/**
 * Points to the SDL renderer object
 */
SDL_Renderer*	renderer = NULL;

/**
 * Points to the SDL window object
 */
SDL_Window*		window = NULL;

/**
 * Points to the Resource Manager
 */
ResourceManager* resourceManager = NULL;

// Color Variables //

/**
 * Holds the values for blue color
 */
SDL_Color	blueColor = { 0x00, 0x00, 0xdd };

/**
 * Holds the values for yellow color
 */
SDL_Color	yellowColor = { 0x00, 0xdd, 0xdd };

/**
 * Holds the values for green color
 */
SDL_Color	greenColor = { 0x00, 0xdd, 0x00 };

/**
 * Holds the values for white color
 */
SDL_Color	whiteColor = { 0xff, 0xff, 0xff };

// Music variables //

/**
 * Points to the background music file
 */
Mix_Music*	bg_music = NULL;

/**
 * Points to the menu sound
 */
Mix_Chunk*	menu_sound = NULL;

/**
 * Points to the selection sound
 */
Mix_Chunk*	select_sound = NULL;

/**
 * Points to the crack low volume sound
 */
Mix_Chunk*	crack_low_sound = NULL;

/**
 * Points to the crack high volume sound
 */
Mix_Chunk*	crack_high_sound = NULL;

/**
 * Points to the paddle hit sound
 */
Mix_Chunk*	paddle_hit_sound = NULL;


// Global Game Functions //

/**
 * Dummy Initialise Function - Initialize Game components
 */
void Init();

/**
 * Dummy Shutdown function
 */
void CloseGame();

// Helper Functions //

/**
 * Function to load music media
 */
bool loadMusicMedia();

/**
 * Function to close music media resources
 */
void closeMusicMedia();

/**
 * Clear screen
 */
void ClearScreen();

/**
 * Enforce Frame Capping
 */
void enforceFPS(int frameStartTime);

/**
 * Save score from currently ended game
 */
void saveScore(int score, Uint32 timeElapsed);

/**
 * Main function
 */
int main(int argc, char** argv);

#endif // !RSPWN_BRKOUT_MAIN

