#include <iostream>

#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

// window
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   450
#define TITLE           "SDL Trials"


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
#define P1_MAX_SPEED_X        5
#define P1_MAX_SPEED_Y        10

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
#define TILE_SIZE   30

#endif // DEFINITIONS_H_INCLUDED
