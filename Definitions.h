#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "FontTexture.h"



// window
#define SCREEN_WIDTH    1440
#define SCREEN_HEIGHT   810
#define TITLE           "SDL Trials"

/**
 * Number of strings
 */
#define NUM_OF_STRINGS	16

/**
 * Label for the lives
 */
#define LIVES_LABEL		"LIVES : "

/**
 * Label for the score
 */
#define SCORE_LABEL		"SCORE : "

/**
 * Index for lives
 */
#define LIVES_INDEX		9

/**
 * Index for score
 */
#define SCORE_INDEX		10

/**
 * Index for exit
 */
#define EXIT_GAME_INDEX		11

/**
 * Load level index
 */
#define LOAD_LEVEL_INDEX	12

/**
 * Win message index
 */
#define WIN_MSG_INDEX		13

/**
 * Lose message index
 */
#define LOSE_MSG_INDEX		14

 /**
 * Revive message index
 */
#define REVIVE_MSG_INDEX	15

/**
 * The frame rate to which the game is capped to
 */
#define FRAME_RATE		60

/**
 * Total number of languages
 */
#define	NUM_OF_LANGS	3

/**
 * Index for English language
 */
#define LANG_TYPE_EN	1

/**
 * Index for French language
 */
#define LANG_TYPE_FR	2

/**
 * Index for Spanish language
 */
#define LANG_TYPE_ES	3

/**
 * The name of the English language file
 */
#define EN_FILE			"assets/en.lang"

/**
 * The name of the French language file
 */
#define FR_FILE			"assets/fr.lang"

/**
 * The name of the spanish language file
 */
#define ES_FILE			"assets/es.lang"

// MENU OPTIONS


/**
 * Tehe number of menu items
 */
#define NUM_OF_MENUS		4

/**
 * The index for new game option
 */
#define NEW_GAME_OPTION		1

/**
 * The index for level select option
 */
#define LEADERBOARD_GAME_OPTION	2

/**
 * The index for exit game option
 */
#define EXIT_GAME_OPTION	3

/**
 * The index for language select game option
 */
#define LANG_GAME_OPTION	4

/**
 * New Game X position
 */
#define NG_X	(SCREEN_WIDTH * 0.3)

/**
 * New Game Y position
 */
#define NG_Y	(SCREEN_HEIGHT * 0.4)

/**
 * Level select X position
 */
#define LB_X	(NG_X)

/**
 * Level select Y position
 */
#define LB_Y	(NG_Y + (SCREEN_HEIGHT * 0.1))

/**
 * Exit X position
 */
#define EX_X	(NG_X)

/**
 * Exit Y position
 */
#define EX_Y	(LB_Y + (SCREEN_HEIGHT * 0.1))

/**
 * Language X position
 */
#define LN_X	(NG_X)

/**
 * Language Y position
 */
#define LN_Y	(EX_Y + (SCREEN_HEIGHT * 0.1))

/**
 * English language X position
 */
#define EN_X	(LN_X + (SCREEN_WIDTH * 0.1))

/**
 * English language Y position
 */
#define EN_Y	(LN_Y + (SCREEN_HEIGHT * 0.1))

/**
 * French language X position
 */
#define FR_X	(EN_X + (SCREEN_WIDTH * 0.1))

/**
 * French language Y position
 */
#define FR_Y	(EN_Y)

/**
 * Spanish language X position
 */
#define ES_X	(FR_X + (SCREEN_WIDTH * 0.1))

/**
 * Spanish language Y position
 */
#define ES_Y	(EN_Y)

/**
 * Exit option X position
 */
#define EXIT_X		10

/**
 * Exit option Y position
 */
#define EXIT_Y		(SCREEN_HEIGHT * 0.6)

/**
 * Index for New Game
 */
#define NEW_GAME_INDEX		0

/**
 * Index for Level in Menu
 */
#define LEADERBOARD_INDEX	1

/**
 * Index for Exit in Menu
 */
#define EXIT_MENU_INDEX		2

/**
 * Index for Languages in Menu
 */
#define LANG_MENU_INDEX		3

/**
 * Index for English language
 */
#define LANG_EN_INDEX		4

/**
 * Index for French language
 */
#define LANG_FR_INDEX		5

/**
 * Index for Spanish language
 */
#define LANG_ES_INDEX		6

/**
 * Index for exit question
 */
#define EXIT_Q_INDEX		7

/**
 * The path to the background image
 */
#define MENU_BG_IMAGE		"./images/WolvenReign.png"

/**
 * Total number of levels
 */
#define NUM_OF_LEVELS		3

/**
 * Index for level labels
 */
#define LEVELS_LABEL_INDEX	8
/**
 * The path to the font for the game
 */
#define GAME_FONT_NAME	"assets/advanced_led_board-7.ttf"

/**
 * The size fo big font
 */
#define FONT_SIZE_BIG	50

/**
 * The size of medium font
 */
#define FONT_SIZE_MID	35

/**
 * The size of small font
 */
#define FONT_SIZE_SMALL	25


/**
 * MUSIC DEFINITIONS
 */

/**
 * Path to the background music file
 */
#define BG_MUSIC_FILE		"assets/within.mp3"

/**
 * Path to the menu change sound
 */
#define MENU_CHANGE_SOUND	"assets/boing.wav"

/**
 * Path to the menu select sound
 */
#define MENU_SELECT_SOUND	"assets/scratch.wav"

/**
 * Path to the brick crack low volume sound
 */
#define BRICK_CRACK_LOW		"assets/Bite.wav"

/**
 * Path to the brick crack high volume sound
 */
#define BRICK_CRACK_HIGH	"assets/Smashing.wav"

/**
 * Path to the paddle ball hitting sound
 */
#define PADDLE_BALL_HIT		"assets/Racquet.wav"



/**
 * The structure which holds the fucntion pointer
 */
struct State
{
	void(*StatePointer) ();
};


/**
 * This structure holds the text strings and the
 * texture for each string
 */
struct StringData
{
	string stringTexts[NUM_OF_STRINGS];
	FontTexture stringTextures[NUM_OF_STRINGS];
	short selectedLang;
};

// Functions for Game States //

/**
 * This function holds the menu state
 */
void MenuState();

/**
 * This function holds the scoreboard state
 */
void ScoreBoardState();

/**
 * This function holds the exit state
 */
void ExitState();

/**
 * This function holds the game state
 */
void GameState();

/**
 * Loads media - implemented in main.cpp
 */
bool loadFontTexture(FontTexture &texture, std::string &text, SDL_Color *color, int fontSize = FONT_SIZE_BIG);




// images
#define SPRITESHEET     "images/tilesets/yoshi.png"
#define ANIM_1_TEX_W    64
#define ANIM_1_TEX_H    64
#define ANIM_1_FRAMES   8
const bool IS_ANIM_1_VERT = true;
#define SPRITESHEET2    "images/capguy-walk.png"
#define ANIM_2_TEX_W    75
#define ANIM_2_TEX_H    132
#define ANIM_2_FRAMES   8
const bool IS_ANIM_2_VERT = false;

//ingame player
#define PLAYER_NAME         "PLAYER1"
#define NORMAL_ANIM_STR     "normal_anim"
#define NORMAL_ANIM_FILE    "./other/animations/player.anim"
#define JUMP_ANIM_STR       "jump_anim"
#define JUMP_ANIM_FILE      "./other/animations/jump.player.anim"
#define P1_MAX_SPEED_X        10
#define P1_MAX_SPEED_Y        15
#define PLAYER_HEALTH_IMG   "./images/heart.png"
#define PLAYER_MAX_HEALTH   4

// bullet
#define BULLET_NAME         "BULLET"
#define BULLET_FIRE_IMG     "./images/bullet_fire.png"
#define BULLET_IMG          "./images/bullet.png"
#define BULLET_MAXSPEED     20
#define BULLET_EXPLODE_SPEED     5
#define BULLET_EXPLODE_ANIM_FILE    "./other/animations/bullet_explode.anim"

// enemy
#define ENEMY_NAME          "ENEMY"
#define ENEMY_ANIM_FILE     "./other/animations/enemy.anim"
#define ENEMY_MAXSPEEDX      5
#define ENEMY_MAXSPEEDY      20

// life upgrade
#define LIFE_NAME           "LIFE"
#define LIFE_ANIM_FILE      "./other/animations/life_upgrade.anim"

// Areas, Maps and Tiles
#define AREA_1      "./areas/1.area"
#define AREA_2      "./areas/testing_mario.area"
#define MAP_WIDTH   30
#define MAP_HEIGHT  15
#define TILE_SIZE   54


// game start instruction
#define GAME_INST_TITLE "LOADING . . ."
#define GAME_INST       "Use ARROW KEYS to move and jump. press LSHIFT while moving to get a speed move or jump. press X to fire bullets"
#define START_GAME_INST "press ENTER to begin game!"
#define GAME_END_1      "Hero! you have made "
#define GAME_END_2      " kills in a time of "
#define GAME_END_3      " in the Werewolf Reign. You will be remembered for your brave attempt!"
#define GAME_END      "press any key to exit ..."

// save files and scoreboard
#define SAVE_FILE           "./savegame"
#define SAVE_FILE_TEMP      "./temp.savegame"
#define SCOREBOARD_TITLE    "Recent Scores :"
#define SCOREBOARD_STATUS   "press any key to go back ..."

#endif // DEFINITIONS_H_INCLUDED
