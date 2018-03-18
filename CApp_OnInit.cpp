#include "CApp.h"



bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Init failed\n");
        return false;
    }

    //create window
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                        SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("window creation failed\n");
        return false;
    }

    //create v-synced rendered
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
        printf("renderer init failed\n");
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Initialize resource manager
	resourceManager = ResourceManager::instance();

	// Initialize event handler
	eventHandler = new CEvent();


	//TEMP SDL RECT FRAMES
    std::vector<SDL_Rect> anim_1_frames;
	SDL_Rect frame1 = {0, 0, 75, 132};
	anim_1_frames.push_back(frame1);
	SDL_Rect frame2 = {75, 0, 75, 132};
	anim_1_frames.push_back(frame2);
	SDL_Rect frame3 = {150, 0, 75, 132};
	anim_1_frames.push_back(frame3);
	SDL_Rect frame4 = {225, 0, 75, 132};
	anim_1_frames.push_back(frame4);
	SDL_Rect frame5 = {300, 0, 75, 132};
	anim_1_frames.push_back(frame5);
	SDL_Rect frame6 = {375, 0, 75, 132};
	anim_1_frames.push_back(frame6);
	SDL_Rect frame7 = {450, 0, 75, 132};
	anim_1_frames.push_back(frame7);
	SDL_Rect frame8 = {525, 0, 75, 132};
	anim_1_frames.push_back(frame8);
	texRectsMap[1] = anim_1_frames;
    std::vector<SDL_Rect> anim_2_frames;
	frame1 = {0, 0, 64, 64};
	anim_2_frames.push_back(frame1);
	frame2 = {0, 64, 64, 64};
	anim_2_frames.push_back(frame2);
	frame3 = {0, 124, 64, 64};
	anim_2_frames.push_back(frame3);
	frame4 = {0, 192, 64, 64};
	anim_2_frames.push_back(frame4);
	frame5 = {0, 256, 64, 64};
	anim_2_frames.push_back(frame5);
	frame6 = {0, 320, 64, 64};
	anim_2_frames.push_back(frame6);
	frame7 = {0, 384, 64, 64};
	anim_2_frames.push_back(frame7);
	frame8 = {0, 448, 64, 64};
	anim_2_frames.push_back(frame8);
	texRectsMap[2] = anim_2_frames;

	// Initialize Entities
	Entity1 = new CEntity(renderer, resourceManager);
	Entity2 = new CEntity(renderer, resourceManager);
	if (Entity1->OnLoad(SPRITESHEET2,
                     ANIM_2_TEX_W, ANIM_2_TEX_H,
                     anim_1_frames.size()) == false) {
        printf("entity1 failed\n");
        return false;
	}
	if (Entity2->OnLoad(SPRITESHEET,
                     ANIM_1_TEX_W, ANIM_1_TEX_H,
                     anim_2_frames.size()) == false) {
	    printf("entity2 failed\n");
        return false;
	}
	Entity2->X = 200;
	CEntity::entityList.push_back(Entity1);
	CEntity::entityList.push_back(Entity2);




	return true;
}
