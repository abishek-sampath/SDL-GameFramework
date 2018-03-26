#include "Exit.h"

using namespace std;

/**
 * Constructor for Exit that initializes its member variables
 */
Exit::Exit(stack<State>	*gameStateStack,
	StringData		*stringData,
	SDL_Renderer*	renderer,
	Mix_Chunk*	menu_sound,
	Mix_Chunk*	select_sound) {

	// Init Variables Pointers
	Exit::gameStateStack = gameStateStack;
	Exit::stringData = stringData;
	Exit::renderer = renderer;
	Exit::menu_sound = menu_sound;
	Exit::select_sound = select_sound;
}

/**
 * Empty destructor for Exit
 */
Exit::~Exit() {

}

/**
 * Function to handle input in Menu Screen
 */
void Exit::HandleExitInput() {
	if (SDL_PollEvent(&event)) {
		// Closing the window
		if (event.type == SDL_QUIT) {
			while (!gameStateStack->empty()) {
				gameStateStack->pop();
			}
			return;
		}
		// Keyboard Event
		if (event.type == SDL_KEYDOWN) {
			SDL_Keysym ksym = event.key.keysym;
			if (ksym.sym == SDLK_ESCAPE) {
				State state;
				state.StatePointer = MenuState;
				gameStateStack->push(state);
				return;
			}
			if ((ksym.sym == SDLK_y) || (ksym.sym == SDLK_q)) {
				// play sound
				Mix_PlayChannel(-1, select_sound, 0);
				gameStateStack->pop();
				return;
			}
			if (ksym.sym == SDLK_n) {
				// play sound
				Mix_PlayChannel(-1, select_sound, 0);
				State state;
				state.StatePointer = MenuState;
				gameStateStack->push(state);
				return;
			}
		}
	}
}

/**
 * Render exit text
 */
void Exit::SetExit() {
	// render all labels
	stringData->stringTextures[EXIT_Q_INDEX].render(renderer,
		(SCREEN_WIDTH - stringData->stringTextures[EXIT_Q_INDEX].getWidth()) / 2, EXIT_Y);
}
