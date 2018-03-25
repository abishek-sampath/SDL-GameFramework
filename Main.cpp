// Calling the main method

#include "main.h"

using namespace std;

/**
 * Frame counter
 */
long counter = 1;

/**
 * Main function
 */
int main(int argc, char* argv) {
	// Initialise game components
	Init();

	// Stack based game loop
	while (!gameStateStack->empty()) {
		int frameStartTime = SDL_GetTicks();
		gameStateStack->top().StatePointer();
		enforceFPS(frameStartTime);
	}

	// Shutdown game
	CloseGame();

	return 0;
}

/**
 * Dummy Initialise Function - Initialize Game components
 */
void Init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}
	//create window
	window = SDL_CreateWindow(TITLE,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	//create vsynced rendered
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	// Initialize font library
	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	// Initialize SDL Sound mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not be intialized! Error : %s\n", Mix_GetError());
	}
	// load media
	if (!loadMusicMedia()) {
		printf("Media could not be loaded! \n");
	}

	// allocate new memory
	if (gameStateStack == NULL)
		gameStateStack = new stack<State>;
	if (stringData == NULL)
		stringData = new StringData();

	// Push exit state to stack
	State currentState;
	currentState.StatePointer = ExitState;
	gameStateStack->push(currentState);

	// Push menu state to stack
	currentState.StatePointer = MenuState;
	gameStateStack->push(currentState);
	exitObj = new Exit(gameStateStack,
		stringData,
		renderer,
		menu_sound,
		select_sound);
	menuObj = new Menu(gameStateStack,
		stringData,
		renderer,
		&blueColor,
		&yellowColor,
		&greenColor,
		&whiteColor,
		bg_music,
		menu_sound,
		select_sound);
}

/**
 * Dummy Shutdown function
 */
void CloseGame() {
	// free resources allocated with new
	delete(gameStateStack);
	delete(stringData);
	delete(menuObj);
	delete(exitObj);

	// close music resources
	closeMusicMedia();

	// Free SDL window
	SDL_DestroyWindow(window);
	window = NULL;

	//exit subsystem
	Mix_Quit();
	// Close font library
	TTF_Quit();
	// quit SDL
	SDL_Quit();
}



/**
 * Menu Demo
 */
void MenuState() {
	// start music
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	// handle key input
	menuObj->HandleMenuInput();
	// clear screen
	ClearScreen();
	//set text to be rendered
	menuObj->SetMenu();
	//update Screen
	SDL_RenderPresent(renderer);
}

/**
 * Game State function
 */
void GameState() {
	// Make sure nothing from the last frame is still drawn. //
	ClearScreen();
	// update and render the game components
	// update Screen
	SDL_RenderPresent(renderer);
}

/**
 * ExitState pushes exit screen to stack and next render the text
 * with whether or not to exit the game will be shown
 */
void ExitState() {
	// pause music
	if (Mix_PlayingMusic() == 1)
		Mix_PauseMusic();
	// handle y/n
	exitObj->HandleExitInput();
	// Make sure nothing from the last frame is still drawn. //
	ClearScreen();
	//render exit options
	exitObj->SetExit();
	// Update screen
	SDL_RenderPresent(renderer);
}


/**
 * Clear screen
 */
void ClearScreen() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
}

/**
 * Enforce Frame Capping
 */
void enforceFPS(int frameStartTime) {
	// Frame Capping
	//If we want to cap the frame rate
	int frameTime = SDL_GetTicks() - frameStartTime;
	if (frameTime < (1000 / FRAME_RATE))
	{
		//Sleep the remaining frame time
		SDL_Delay((1000 / FRAME_RATE) - frameTime);
	}
}

/**
 * Function to load music media
 */
bool loadMusicMedia() {
	// TODO : Add code to load music media here
	return false;
}

/**
 * Function to close music media resources
 */
void closeMusicMedia() {
	// TODO : clear all loaded music media
}

/**
 * Funciton to Load Font textures
 */
bool loadFontTexture(FontTexture &texture, std::string &text, SDL_Color *color, int fontSize)
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
		if (!texture.loadFromRenderedText(renderer, text, *color, font))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	TTF_CloseFont(font);

	return success;
}
