#include "CApp.h"
#include <ctime>

//local file methods
//bool loadFrameDimensions(std::string animFile, std::string &imgFile, std::vector<SDL_Rect> &frameSet,
//                         ResourceManager* resourceManager, SDL_Renderer* renderer);

bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Init failed\n");
        return false;
    }

    //create window
    window = SDL_CreateWindow(TITLE,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("window creation failed\n");
        return false;
    }

    //create v-synced rendered
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("renderer init failed\n");
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Initialize resource manager
    resourceManager = ResourceManager::instance(renderer);

    // Initialize Area with renderer and resource manager
    GArea::AreaControl.renderer = renderer;
    GArea::AreaControl.resourceManager = resourceManager;
    if(GArea::AreaControl.OnLoad(AREA_2) == false) {
        return false;
    }

    // Initialize players
    player1 = new PlayerEntity(renderer, resourceManager);
    player2 = new PlayerEntity(renderer, resourceManager);
    if(player1->OnLoad(SPRITESHEET,
                       64, 64,
                       ANIM_1_TEX_W, ANIM_1_TEX_H,
                       ANIM_1_FRAMES) == false) {
                        return false;
                       }
    player1->name = PLAYER_NAME;
    player1->X = 100;
    GEntity::EntityList.push_back(player1);
    GCamera::CameraControl.targetMode = TARGET_MODE_CENTER;
    GCamera::CameraControl.SetTarget(&player1->X, &player1->Y);


    // BULLETS
    // Initialize Bullet Images
    //resourceManager->loadImg(BULLET_FIRE_IMG, renderer);
    //resourceManager->loadImg(BULLET_IMG, renderer);
    bulletTemplate = new BulletEntity(renderer, resourceManager);
    if(bulletTemplate->OnLoad(40, 40) == false)
    {
        bulletTemplate->OnCleanup();
        return false;
    }


    // ENEMY
    enemyTemplate = new EnemyEntity(renderer, resourceManager);
    if(enemyTemplate->OnLoad(ENEMY_ANIM_FILE, 75, 75) == false) {
        return false;
    }
    enemyTemplate->flags = ENTITY_FLAG_GRAVITY;


    // LIFE UPGRADE
    lifeTemplate = new LifeUpgradeEntity(renderer, resourceManager);
    if(lifeTemplate->OnLoad(LIFE_ANIM_FILE, 16, 16) == false) {
        return false;
    }
    lifeTemplate->flags = ENTITY_FLAG_GRAVITY;


    // initialize for randomness
    std::srand(std::time(NULL));


    return true;
}


//bool loadFrameDimensions(std::string animFile, std::string &imgFile, std::vector<SDL_Rect> &frameSet,
//                         ResourceManager* resourceManager, SDL_Renderer* renderer)
//{
//    const char* file = animFile.c_str();
//    FILE* fileHandler = fopen(file, "r");
//    if(fileHandler == NULL) {
//        return false;
//    }
//
//    char tempName[255]="";
//    fscanf(fileHandler, "%s\n", tempName);
//    imgFile.assign(tempName);
//    if(resourceManager->loadImg(imgFile, renderer) == NULL) {
//        fclose(fileHandler);
//        return false;
//    }
//    int frameSetSize = 0;
//    fscanf(fileHandler, "%d\n", &frameSetSize);
//    for(int i=0; i<frameSetSize; i++) {
//        SDL_Rect rect;
//        fscanf(fileHandler, "%d %d %d %d", &rect.x, &rect.y, &rect.w, &rect.h);
//        frameSet.push_back(rect);
//        fscanf(fileHandler, "\n");
//    }
//    fclose(fileHandler);
//
//    return true;
//}
