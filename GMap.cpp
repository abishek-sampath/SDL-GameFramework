#include "GMap.h"

GMap::GMap(SDL_Renderer* renderer, ResourceManager* resourceManager)
{
    texture = NULL;
    this->renderer = renderer;
    this->resourceManager = resourceManager;
}


bool GMap::OnLoad(char* file)
{
    tileList.clear();

    FILE* fileHandler = fopen(file, "r");
    if(fileHandler == NULL) {
        return false;
    }

    for(int y=0; y<MAP_HEIGHT; y++) {
        for(int x=0; x<MAP_WIDTH; x++) {
            GTile tile;
            fscanf(fileHandler, "%d:%d ", &tile.TileID, &tile.TypeID);
            tileList.push_back(tile);
        }
        fscanf(fileHandler, "\n");
    }
    fclose(fileHandler);

    return true;
}


void GMap::OnRender(int mapX, int mapY)
{
    if(texture == NULL) {
        return;
    }
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    int tileSetWidth    = w / TILE_SIZE;
    //int tileSetHeight   = h / TILE_SIZE;

    int ID = 0;
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            if(tileList[ID].TypeID == TILE_TYPE_NONE) {
                ID++;
                continue;
            }

            int tx = mapX + (x * TILE_SIZE);
            int ty = mapY + (y * TILE_SIZE);

            int tileSetX = (tileList[ID].TileID % tileSetWidth) * TILE_SIZE;
            int tileSetY = (tileList[ID].TileID / tileSetWidth) * TILE_SIZE;

            TextureUtils::OnDraw(texture, renderer,
                                 tx, ty,
                                 tileSetX, tileSetY,
                                 TILE_SIZE, TILE_SIZE);

            ID++;
        }
    }
}
