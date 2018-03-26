#include "Menu.h"

using namespace std;

/**
 * Constructor - Initialize Menu components
 */
Menu::Menu(stack<State>	*gameStateStack,
	StringData		*stringData,
	SDL_Renderer*	renderer,
	SDL_Color		*blueColor,
	SDL_Color		*yellowColor,
	SDL_Color		*greenColor,
	SDL_Color		*whiteColor,
	Mix_Music*	bg_music,
	Mix_Chunk*	menu_sound,
	Mix_Chunk*	select_sound) {

	// Init Variables Pointers
	Menu::gameStateStack = gameStateStack;
	Menu::stringData = stringData;
	Menu::renderer = renderer;
	Menu::blueColor = blueColor;
	Menu::yellowColor = yellowColor;
	Menu::greenColor = greenColor;
	Menu::whiteColor = whiteColor;
	Menu::bg_music = bg_music;
	Menu::menu_sound = menu_sound;
	Menu::select_sound = select_sound;


	// set background texture
    SDL_Surface* img = IMG_Load(MENU_BG_IMAGE);
    if (img == NULL)
    {
        SDL_Log("Failed to allocate surface");
    }
    menuBackgroundtexture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

	// load language and menu options
	menuOptionChanged = true;
	langOptionChanged = true;
	currentMenuOption = NEW_GAME_OPTION;
	currentLangOption = LANG_TYPE_EN;
	if (!loadMenuLanguage(LANG_TYPE_EN)) {
		printf("Error loading Menu Language and rendering!\n");
	}
}

/**
 * Destroyer - Free all Menu components
 */
Menu::~Menu() {
	// Free background texture
	SDL_DestroyTexture(menuBackgroundtexture);
	menuBackgroundtexture = NULL;
	//// free menu option textures
	//for (int i = 0; i < 7; i++) {
	//	stringData->stringTextures[i].freeFontTexture();
	//}
}

/**
 * Load language pack, English, French or Spanish
 */
bool Menu::loadMenuLanguage(int lang_type) {
	stringData->selectedLang = lang_type;
	string fileName;
	switch (lang_type)
	{
	case LANG_TYPE_FR:
		fileName = FR_FILE;
		break;
	case LANG_TYPE_ES:
		fileName = ES_FILE;
		break;
	default:
		fileName = EN_FILE;
		break;
	}

	ifstream in(fileName);
	if (!in) {
		printf("Cannot Open file %s.\n", fileName.c_str());
		return false;
	}

	char str[255];
	int textIndex = 0;

	while (in) {
		in.getline(str, 255);  // delim defaults to '\n'
		stringData->stringTexts[textIndex] = str;
		// load texture
		FontTexture texture;
		stringData->stringTextures[textIndex++] = texture;
		if (textIndex == NUM_OF_STRINGS)
			break;
	}

	// close file stream
	in.close();
	//load textures for menu options
	loadMenuTextures();

	return true;
}

/**
 * Function to load Menu option textures
 */
void Menu::loadMenuTextures() {
	// Main Menu textures
	loadFontTexture(stringData->stringTextures[NEW_GAME_INDEX], stringData->stringTexts[NEW_GAME_INDEX], whiteColor,FONT_SIZE_BIG);
	loadFontTexture(stringData->stringTextures[LEADERBOARD_INDEX], stringData->stringTexts[LEADERBOARD_INDEX], whiteColor, FONT_SIZE_BIG);
	loadFontTexture(stringData->stringTextures[EXIT_MENU_INDEX], stringData->stringTexts[EXIT_MENU_INDEX], whiteColor, FONT_SIZE_BIG);
	loadFontTexture(stringData->stringTextures[LANG_MENU_INDEX], stringData->stringTexts[LANG_MENU_INDEX], whiteColor, FONT_SIZE_BIG);
	loadFontTexture(stringData->stringTextures[LANG_EN_INDEX], stringData->stringTexts[LANG_EN_INDEX], whiteColor, FONT_SIZE_MID);
	loadFontTexture(stringData->stringTextures[LANG_FR_INDEX], stringData->stringTexts[LANG_FR_INDEX], whiteColor, FONT_SIZE_MID);
	loadFontTexture(stringData->stringTextures[LANG_ES_INDEX], stringData->stringTexts[LANG_ES_INDEX], whiteColor, FONT_SIZE_MID);
	// Quit Texture
	loadFontTexture(stringData->stringTextures[EXIT_Q_INDEX], stringData->stringTexts[EXIT_Q_INDEX], whiteColor, FONT_SIZE_BIG);

	// if no new language selected, highlight previous language
	if (langOptionChanged) {
		short newLang = stringData->selectedLang + NUM_OF_MENUS - 1;
		//menuoptions.menuTextures[newLang].setColor(255, 255, 255);
		loadFontTexture(stringData->stringTextures[newLang], stringData->stringTexts[newLang], greenColor, FONT_SIZE_MID);
		langOptionChanged = false;
	}
}


/**
 * Function to handle input in Menu Screen
 */
void Menu::HandleMenuInput() {
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
			if ((ksym.sym == SDLK_ESCAPE) || (ksym.sym == SDLK_q)) {
				gameStateStack->pop();
				return;
			}
			if (ksym.sym == SDLK_DOWN) {
				if (currentMenuOption < NUM_OF_MENUS) {
					ResetMenuTexture(currentMenuOption, whiteColor);
					// play sound
					Mix_PlayChannel(-1, menu_sound, 0);
					++currentMenuOption;
				}
				menuOptionChanged = true;
				return;
			}
			if (ksym.sym == SDLK_UP) {
				if (currentMenuOption > 1) {
					if (currentMenuOption == NUM_OF_MENUS) {
						ResetLangTexture(currentLangOption, whiteColor);
						ResetLangTexture(stringData->selectedLang, greenColor);
						currentLangOption = stringData->selectedLang;
						langOptionChanged = false;
					}
					ResetMenuTexture(currentMenuOption, whiteColor);
					// play sound
					Mix_PlayChannel(-1, menu_sound, 0);
					--currentMenuOption;
				}
				menuOptionChanged = true;
				return;
			}
			if (ksym.sym == SDLK_LEFT) {
				if ((currentMenuOption == LANG_GAME_OPTION) &&
					(currentLangOption > 1)) {
					ResetLangTexture(currentLangOption, whiteColor);
					// play sound
					Mix_PlayChannel(-1, menu_sound, 0);
					--currentLangOption;
					langOptionChanged = true;
				}
				return;
			}
			if (ksym.sym == SDLK_RIGHT) {
				if ((currentMenuOption == LANG_GAME_OPTION) &&
					(currentLangOption < NUM_OF_LANGS)) {
					ResetLangTexture(currentLangOption, whiteColor);
					// play sound
					Mix_PlayChannel(-1, menu_sound, 0);
					++currentLangOption;
					langOptionChanged = true;
				}
				return;
			}
			if (ksym.sym == SDLK_RETURN) {
				if (currentMenuOption == NEW_GAME_OPTION) {
					// play sound
					Mix_PlayChannel(-1, select_sound, 0);
					// Enable text input
					SDL_StartTextInput();
					// Add New Game State to stack
					State currentState;
					currentState.StatePointer = GameState;
					gameStateStack->push(currentState);
					return;
				}
				if (currentMenuOption == LEADERBOARD_GAME_OPTION) {
					// play sound
					Mix_PlayChannel(-1, select_sound, 0);
					State currentState;
					currentState.StatePointer = ScoreBoardState;
					gameStateStack->push(currentState);
					return;
				}
				if (currentMenuOption == EXIT_GAME_OPTION) {
					// play sound
					Mix_PlayChannel(-1, select_sound, 0);
					gameStateStack->pop();
					return;
				}
				if (currentMenuOption == LANG_GAME_OPTION) {
					langOptionChanged = true;
					// play sound
					Mix_PlayChannel(-1, select_sound, 0);
					loadMenuLanguage(currentLangOption);
					return;
				}
				return;
			}
		}
	}
}


/**
 * Render Menu text
 */
void Menu::SetMenu() {
	// update selection
	if (menuOptionChanged) {
		ResetMenuTexture(currentMenuOption, blueColor);
		menuOptionChanged = false;
	}
	if (langOptionChanged) {
		ResetLangTexture(currentLangOption, yellowColor);
		langOptionChanged = false;
	}

	// TODO : render background image

	// render all labels
	SetMenuBackground();
	stringData->stringTextures[NEW_GAME_INDEX].render(renderer, NG_X, NG_Y);
	stringData->stringTextures[LEADERBOARD_INDEX].render(renderer, LB_X, LB_Y);
	stringData->stringTextures[EXIT_MENU_INDEX].render(renderer, EX_X, EX_Y);
	stringData->stringTextures[LANG_MENU_INDEX].render(renderer, LN_X, LN_Y);
	stringData->stringTextures[LANG_EN_INDEX].render(renderer, EN_X, EN_Y);
	stringData->stringTextures[LANG_FR_INDEX].render(renderer, FR_X, FR_Y);
	stringData->stringTextures[LANG_ES_INDEX].render(renderer, ES_X, ES_Y);
}

/**
 * Render menu background
 */
void Menu::SetMenuBackground() {
    SDL_Rect rect;
    rect.w = SCREEN_WIDTH * 0.8;
    rect.h = SCREEN_HEIGHT * 0.3;
    rect.x = (SCREEN_WIDTH / 2) - (rect.w / 2);
    rect.y = 20;
	SDL_RenderCopy(renderer, menuBackgroundtexture,NULL, &rect);
}

/**
 * Reset previous menu texture
 */
void Menu::ResetMenuTexture(short menuOption, SDL_Color *color) {
	loadFontTexture(stringData->stringTextures[menuOption - 1], stringData->stringTexts[menuOption - 1], color, FONT_SIZE_BIG);
}

/**
 * Reset previous language texture
 */
void Menu::ResetLangTexture(short langOption, SDL_Color *color) {
	loadFontTexture(stringData->stringTextures[langOption + NUM_OF_MENUS - 1], stringData->stringTexts[langOption + NUM_OF_MENUS - 1], color, FONT_SIZE_MID);
}
