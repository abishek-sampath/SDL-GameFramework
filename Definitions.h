#include <iostream>

#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

// window
#define SCREEN_WIDTH    960
#define SCREEN_HEIGHT   720
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

// Areas, Maps and Tiles
#define AREA_1      "./areas/1.area"
#define MAP_WIDTH   40
#define MAP_HEIGHT  40
#define TILE_SIZE   16

#endif // DEFINITIONS_H_INCLUDED
