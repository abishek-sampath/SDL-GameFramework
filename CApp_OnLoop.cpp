#include "CApp.h"


void CApp::OnLoop()
{
    // exit if player not alive
    if(player1->dead) {
        running = false;
        return;
    }


    //get current time
    Uint32 timePassed = SDL_GetTicks() - beginTime;
    int secs    = timePassed / 1000;

    int mins    = secs / 60;
    int hours   = mins / 60;
    timeText.str("");
    if(hours > 0)
        timeText << hours << ":";
    if(mins > 0)
        timeText << (mins % 60) << ":";
    if(secs > 0)
        timeText << (secs % 60);


    // spawn health packs if health is low
    GenerateLifePack(secs);


    // spawn Enemies and Waves randomly
    GenerateEnemyEntity(secs);
    GenerateWaveOfEnemies(secs);


    // clear renderer for next loop
    SDL_RenderClear(renderer);

    for(unsigned int i=0; i < GEntity::EntityList.size(); i++) {
        if(!GEntity::EntityList[i])
            continue;
        if(GEntity::EntityList[i]->dead) {
            if(GEntity::EntityList[i]->name == ENEMY_NAME)
                score++;
            GEntity::EntityList[i]->OnCleanup();
            //delete(GEntity::EntityList[i]);
            GEntity::EntityList.erase(GEntity::EntityList.begin() + i);
        }
        GEntity::EntityList[i]->OnLoop();
    }

    // handle queued collision events
    for(unsigned int i=0; i < GEntityCollision::EntityCollisonList.size(); i++) {
        GEntity* entityA = GEntityCollision::EntityCollisonList[i].entityA;
        GEntity* entityB = GEntityCollision::EntityCollisonList[i].entityB;

        if(entityA == NULL || entityB == NULL)
            continue;

        if(entityA->OnCollision(entityB)) {
            entityB->OnCollision(entityA);
        }
    }
    GEntityCollision::EntityCollisonList.clear();

    GFPS::FPSControl.OnLoop();

    char buffer[255];
    sprintf(buffer, "%d", GFPS::FPSControl.GetFPS());
    SDL_SetWindowTitle(window, buffer);
}




void CApp::GenerateLifePack(int currTime)
{
    if(generateLives == true && (currTime % 20 == 0)) {
        numb_lives_to_gen++;
        generateLives = false;
    }
    if(currTime % 20 != 0) {
        generateLives = true;
    }
    if(player1->health == PLAYER_MAX_HEALTH) {
        return;
    }
    if(player1->health == 1 && numb_lives_to_gen > 0 && generateLives) {
        //int init_x = 0;
        //int final_x = GArea::AreaControl.GetAreaWidth() / numb_lives_to_gen;
        int temp = numb_lives_to_gen;
        for(int i = 1; i<= temp && i < 4; i++)
        {
            //int health_pos = init_x + rand() % (final_x * i - init_x + 1);
            int health_pos = rand() % (GArea::AreaControl.GetAreaWidth());

            LifeUpgradeEntity* life = (LifeUpgradeEntity*)lifeTemplate->clone();
            life->X = health_pos;
            life->Y = 10;
            life->flags = ENTITY_FLAG_GRAVITY;
            GEntity::EntityList.push_back(life);

            //init_x = final_x * i;
            numb_lives_to_gen--;
        }

        generateLives = false;
    }
}



void CApp::GenerateWaveOfEnemies(int currTime)
{
    int widthOfScreen = GArea::AreaControl.GetAreaWidth();
    int maxDistFromPlayer = widthOfScreen / 4;
    int playerPositionX = player1->X;

    if ((currTime % enemyWaveDelay == 0) && (enemyGenerated == false))
    {
        int newEnemyPosX = rand() % (playerPositionX + maxDistFromPlayer) + (playerPositionX - maxDistFromPlayer);
        if (playerPositionX - maxDistFromPlayer < 0)
        {
            newEnemyPosX = rand() % maxDistFromPlayer;
        }
        if (playerPositionX + maxDistFromPlayer > widthOfScreen)
        {
            newEnemyPosX = rand() % (widthOfScreen - (playerPositionX - maxDistFromPlayer)) + (playerPositionX - maxDistFromPlayer);
        }

        //int newEnemyPosY = rand() % heightOfScreen;

        // CALL FUNCTION TO GENERATE ENEMY HERE
        EnemyEntity* enemy = (EnemyEntity*)enemyTemplate->clone();
        if(newEnemyPosX < 0)
            newEnemyPosX = 100;
        if(newEnemyPosX > GArea::AreaControl.GetAreaWidth())
            newEnemyPosX = GArea::AreaControl.GetAreaWidth() - 100;
        enemy->X = newEnemyPosX;
        enemy->Y = 10;
        enemy->flags = ENTITY_FLAG_GRAVITY;
        GEntity::EntityList.push_back(enemy);

        if (++createdEnemiesPerWaveSoFar == enemiesPerWave)
        {
            enemyGenerated = true;
            timeGenerated = currTime;
            createdEnemiesPerWaveSoFar = 0;
            enemiesPerWave++;
        }
    }
    if ((currTime == timeGenerated + 1) && (enemyGenerated == true))
        enemyGenerated = false;
}



void CApp::GenerateEnemyEntity(int currTime)
{
    int widthOfScreen = GArea::AreaControl.GetAreaWidth();
    int maxDistFromPlayer = widthOfScreen / 4;
    int playerPositionX = player1->X;

    if ((currTime % enemyTimeDelay == 0) && (enemyGenerated == false))
    {
        int newEnemyPosX = rand() % (playerPositionX + maxDistFromPlayer) + (playerPositionX - maxDistFromPlayer);
        if (playerPositionX - maxDistFromPlayer < 0)
        {
            newEnemyPosX = rand() % maxDistFromPlayer;
        }
        if (playerPositionX + maxDistFromPlayer > widthOfScreen)
        {
            newEnemyPosX = rand() % (widthOfScreen - (playerPositionX - maxDistFromPlayer)) + (playerPositionX - maxDistFromPlayer);
        }

        //int newEnemyPosY = rand() % heightOfScreen;

        // CALL FUNCTION TO GENERATE ENEMY HERE
        EnemyEntity* enemy = (EnemyEntity*)enemyTemplate->clone();
        if(newEnemyPosX < 0)
            newEnemyPosX = 100;
        if(newEnemyPosX > GArea::AreaControl.GetAreaWidth())
            newEnemyPosX = GArea::AreaControl.GetAreaWidth() - 100;
        enemy->X = newEnemyPosX;
        enemy->Y = 10;
        enemy->flags = ENTITY_FLAG_GRAVITY;
        GEntity::EntityList.push_back(enemy);

        enemyGenerated = true;
        timeGenerated = currTime;
    }
    if ((currTime == timeGenerated + 1) && (enemyGenerated == true))
        enemyGenerated = false;
}



//void CApp::OnLoop()
//{
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_RenderClear(renderer);
//
//    texture = resourceManager->loadImg("images/capguy-walk.png", renderer);
//    SDL_Rect windowRect = {0,0,140,200};
//    SDL_Rect textureRect;
//    textureRect.x = 0;
//    textureRect.y = 0;
//    SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
//    textureRect.w /= 8;
//
//    //Total number of frames of the animation
//        int totalFrames = 8;
//
//        //Amount of delay in milliseconds for each frame
//        int delayPerFrame = 50;
//
//        //SDL_GetTicks() method gives us the time in milliseconds
//
//        //'frame' will give us the index of frame we want to render
//        //For example, if 'frame' is 2, it will give us the third frame
//       int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
//
//    //The index of frame is multiplied by the width of the frame
//        //This will give us the appropriate
//        //frame dimensions from the sprite sheet
//        textureRect.x = frame * textureRect.w;
//
//
//
//    SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);
//}

