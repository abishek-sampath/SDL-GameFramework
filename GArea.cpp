#include "GArea.h"
#include <string>

GArea GArea::AreaControl;

GArea::GArea()
{
    areaSizeX = 0;
    areaSizeY = 0;
}


bool GArea::OnLoad(const char* file)
{
    mapList.clear();

    FILE* fileHandler = fopen(file, "r");
    if(fileHandler == NULL) {
        return false;
    }

    char tileSetFile[255]="";
    fscanf(fileHandler, "%s\n", tileSetFile);
    if((texture = resourceManager->loadImg(tileSetFile, renderer)) == NULL) {
        fclose(fileHandler);
        return false;
    }

    fscanf(fileHandler, "%d ", &areaSizeX);
    fscanf(fileHandler, "%d \n", &areaSizeY);
    for(int x = 0; x < areaSizeX; x++) {
        for(int y = 0; y < areaSizeY; y++) {
            char mapFile[255] = "";
            fscanf(fileHandler, "%s ", mapFile);
            GMap tempMap(renderer, resourceManager);
            if(tempMap.OnLoad(mapFile) == false) {
                fclose(fileHandler);
                return false;
            }
            tempMap.texture = texture;
            mapList.push_back(tempMap);
        }
        fscanf(fileHandler, "\n");
    }
    fclose(fileHandler);

    return true;
}


void GArea::OnRender(int cameraX, int cameraY)
{
    // in pixels
    int mapWidth = MAP_WIDTH * TILE_SIZE;
    int mapHeight = MAP_HEIGHT * TILE_SIZE;

    // everything below doubtful
//    int horizontalMaps = ((-cameraX + SCREEN_WIDTH) / mapWidth) - (-cameraX / mapWidth)  + 1;
//    int verticalMaps = ((-cameraY + SCREEN_WIDTH) / mapHeight) - (-cameraY / mapHeight) + 1;
//    int mapsToLoad = horizontalMaps * verticalMaps;

    //int firstIDX = -cameraX / mapWidth;
    //int firstIDY = ((-cameraY / mapHeight) * areaSizeY);
    //int firstID = firstIDX + firstIDY;
    for(int i = 0; i < (areaSizeX * areaSizeY); i++) {
        //int ID = firstID + ((i / 2) * areaSizeX) + (i % 2);
        int ID = i;

        if(ID < 0 || ID >= mapList.size())
            continue;

        int x = ((ID % areaSizeY) *  mapWidth) + cameraX;
        int y = ((ID % areaSizeX) * mapHeight) + cameraY;
        mapList[ID].OnRender(x, y);
    }
}


void GArea::OnCleanup()
{
    mapList.clear();
}


GMap* GArea::GetMap(int X, int Y)
{
    int mapWidth    = MAP_WIDTH * TILE_SIZE;
    int mapHeight   = MAP_HEIGHT * TILE_SIZE;

    int ID = X / mapWidth;
    ID = ID + ((Y / mapHeight) * areaSizeX);

    if(ID < 0 || ID >= mapList.size()) {
        return NULL;
    }

    return &mapList[ID];
}



GTile* GArea::GetTile(int X, int Y)
{
    int mapWidth    = MAP_WIDTH * TILE_SIZE;
    int mapHeight   = MAP_HEIGHT * TILE_SIZE;

    // check right and bottom out of bounds
    if(X > (mapWidth * areaSizeY) || Y > (mapHeight * areaSizeX))
        return NULL;

    GMap* gmap = GetMap(X, Y);
    if(gmap == NULL)
        return NULL;

    X = X % mapWidth;
    Y = Y % mapHeight;

    return gmap->GetTile(X, Y);
}
