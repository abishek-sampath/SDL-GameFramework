#include "ScoreBoard.h"


using namespace std;

/**
 * Constructor for ScoreBoard that initializes its member variables
 */
ScoreBoard::ScoreBoard(stack<State>	*gameStateStack,
	SDL_Renderer*	renderer,
	ResourceManager* resourceManager) {

	// Init Variables Pointers
	ScoreBoard::gameStateStack = gameStateStack;
	ScoreBoard::renderer = renderer;
	ScoreBoard::resourceManager = resourceManager;
}


/**
 * Empty destructor for ScoreBoard
 */
ScoreBoard::~ScoreBoard() {

}




/**
 * Function to handle input in ScoreBoard Screen
 */
void ScoreBoard::HandleScoreBoardInput() {

    // remove events during delay
	SDL_PumpEvents();
    SDL_FlushEvent(SDL_KEYDOWN | SDL_QUIT);
    while(SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT) {
            while (!gameStateStack->empty()) {
				gameStateStack->pop();
			}
			break;
        }

        if(e.type == SDL_KEYDOWN) {
            gameStateStack->pop();
            break;
        }
    }
}

/**
 * Render ScoreBoard text
 */
void ScoreBoard::SetScoreBoard() {
    SDL_RenderClear(renderer);
    std::stringstream timeText;
    // render title
    SDL_Color	whiteColor = { 0xff, 0xff, 0xff };
    FontTexture scoreboardTexture;
    resourceManager->loadFontTexture(scoreboardTexture, SCOREBOARD_TITLE, &whiteColor, FONT_SIZE_MID);
    scoreboardTexture.render(renderer, ((SCREEN_WIDTH / 2) - (scoreboardTexture.getWidth() / 2)), (SCREEN_HEIGHT * 0.1));

    // render heading
    FontTexture headerTexture;
    timeText.str("");
    timeText << "KILLS" << "\t\t\t" << "TIME";
    resourceManager->loadFontTexture(headerTexture, timeText.str(), &whiteColor, FONT_SIZE_SMALL);
    headerTexture.render(renderer, ((SCREEN_WIDTH / 2) - (headerTexture.getWidth() / 2)), (SCREEN_HEIGHT * 0.2));

    //open savegame file
    std::ifstream ifile(SAVE_FILE);
    if (ifile)
    {
        int a;
        Uint32 b;
        float i=30.0f;
        while (ifile >> a >> b)
        {
            timeText.str("");
            timeText << a << "    \t\t";
            //calculate time
            int secs    = (b / 1000) % 60;
            int mins    = (b / (1000 * 60)) % 60;
            int hours   = (b / (1000 * 60 * 60));

            if(hours < 10)
                timeText << "0" << hours << ":";
            else
                timeText << hours << ":";

            if(mins < 10)
                timeText << "0" << mins << ":";
            else
                timeText << mins << ":";

            if(secs < 10)
                timeText << "0" << secs;
            else
                timeText << secs;

            // render score
            FontTexture scoreTexture;
            resourceManager->loadFontTexture(headerTexture, timeText.str(), &whiteColor, FONT_SIZE_SMALL);
            headerTexture.render(renderer, ((SCREEN_WIDTH / 2) - (headerTexture.getWidth() / 2)), (SCREEN_HEIGHT * (i/100)));
            i += 10;
        }

        //close input stream
        ifile.close();
    }

    FontTexture endTexture;
    resourceManager->loadFontTexture(endTexture, SCOREBOARD_STATUS, &whiteColor, FONT_SIZE_SMALL, (SCREEN_WIDTH * 0.9));
    endTexture.render(renderer, (SCREEN_WIDTH * 0.05), (SCREEN_HEIGHT * 0.9));
}
