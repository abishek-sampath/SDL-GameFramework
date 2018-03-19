#ifndef GTILE_H_INCLUDED
#define GTILE_H_INCLUDED

#include "Definitions.h"

enum
{
    TILE_TYPE_NONE = 0,
    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK
};

class GTile
{
public:
    int TileID;
    int TypeID;

public:
    GTile();
};

#endif // GTILE_H_INCLUDED
