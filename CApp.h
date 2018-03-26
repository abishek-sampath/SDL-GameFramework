#ifndef CAPP_H_INCLUDED
#define CAPP_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <random>
#include <stdio.h>
#include <string>
#include <sstream>

#include "GEvent.h"
#include "GAnimation.h"
#include "GEntity.h"
#include "GArea.h"
#include "GCamera.h"

#include "PlayerEntity.h"
#include "BulletEntity.h"
#include "EnemyEntity.h"
#include "LifeUpgradeEntity.h"

#include "ResourceManager.h"
#include "TextureUtils.h"
#include "Definitions.h"

// for random number generation
//using param_type = typename std::uniform_int_distribution<int>::param_type;

class CApp : public GEvent {
private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    PlayerEntity* player1 = NULL;
    PlayerEntity* player2 = NULL;

    BulletEntity* bulletTemplate = NULL;
    EnemyEntity* enemyTemplate = NULL;
    LifeUpgradeEntity* lifeTemplate = NULL;
    TTF_Font* font = NULL;
    SDL_Color	whiteColor = { 0xff, 0xff, 0xff };


private:
    ResourceManager* resourceManager;
    std::unordered_map<int, std::vector<SDL_Rect>> texRectsMap;

// for random number generation
private:
    //std::mt19937 eng {std::random_device{}()};
    //std::uniform_int_distribution<int> dist;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

private:
    std::stringstream timeText;
    bool generateLives;
    int numb_lives_to_gen;
    Uint32 beginTime;
    int score;

public:
    CApp();
    CApp(SDL_Renderer* renderer, ResourceManager* resourceManager);
    int OnExecute();

public:
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnCleanup();

public:
    void OnExit();
    void OnKeyDown(SDL_Keycode &sym, Uint16 &mod);
    void OnKeyUp(SDL_Keycode &sym, Uint16 &mod);

public:
    void GenerateLifePack(int currTime);

public:
    int GetFinalScore();
    Uint32 GetFinalTime();

// enemy spawning
private:
    int enemyTimeDelay = 10;
    int enemyWaveDelay = 180;
    // defined in init()
    int maxDistFromPlayer = 0;
    bool enemyGenerated = false;
    int timeGenerated;
    int enemiesPerWave = 8;
    int createdEnemiesPerWaveSoFar = 0;
// enemy spawning
public:
    void GenerateEnemyEntity(int currTime);
    void GenerateWaveOfEnemies(int currTime);

};

#endif // CAPP_H_INCLUDED
