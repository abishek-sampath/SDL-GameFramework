#include "GArea.h"

GArea GArea::AreaControl;

GArea::GArea()
{
    areaSize = 0;
}


bool GArea::OnLoad(const char* file)
{
    mapList.clear();

    FILE* fileHandler = fopen(file, "r");
    if(fileHandler == NULL) {
        return false;
    }

    char tileSetFile[255];
    fscanf(fileHandler, "%s\n", tileSetFile);
    if((texture = resourceManager->loadImg(tileSetFile, renderer)) == NULL) {
        fclose(fileHandler);
        return false;
    }

    fscanf(fileHandler, "%d\n", &areaSize);
    for(int x = 0; x < areaSize; x++) {
        for(int y = 0; y < areaSize; y++) {
            char mapFile[255];
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

    int firstIDX = -cameraX / mapWidth;
    int firstIDY = ((-cameraY / mapHeight) * areaSize);
    int firstID = firstIDX + firstIDY;

    for(int i = 0; i < 9; i++) {
        int ID = firstID + ((i / 3) * areaSize) + (i % 3);

        if(ID < 0 || ID >= mapList.size())
            continue;

        int x = ((ID % areaSize) *  mapWidth) + cameraX;
        int y = ((ID / areaSize) * mapHeight) + cameraY;
        mapList[ID].OnRender(x, y);
    }
}


void GArea::OnCleanup()
{
    mapList.clear();
}
