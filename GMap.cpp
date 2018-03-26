#include "GMap.h"

GMap::GMap(SDL_Renderer* renderer, ResourceManager* resourceManager)
{
    texture = NULL;
    this->renderer = renderer;
    this->resourceManager = resourceManager;
}


bool GMap::OnLoad(const char* file)
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

    // load corresponding props
    std::string propFile(file);
    propFile.append(".props");
    std::vector<char> writable(propFile.begin(), propFile.end());
    writable.push_back('\0');
    if(loadAllProps(&writable[0]) == false) {
        return false;
    }

    return true;
}


void GMap::OnRender(int mapX, int mapY)
{
    if(texture == NULL) {
        std::cout << "1 Tile Texture Null";
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
                std::cout << "2 Tile NONE";
                continue;
            }

            int tx = mapX + (x * TILE_SIZE);
            int ty = mapY + (y * TILE_SIZE);

//            int tileSetX = (tileList[ID].TileID % tileSetWidth) * TILE_SIZE;
//            int tileSetY = (tileList[ID].TileID / tileSetWidth) * TILE_SIZE;

            // load current tile texture
            texture = getPropTexture(tileList[ID].TileID);
            if(texture == NULL) {
                std::cout << "Tile Texture Null";
                continue;
            }

            TextureUtils::OnDraw(texture, renderer,
                                 tx, ty,
                                 TILE_SIZE, TILE_SIZE,
                                 0, 0,
                                 TILE_SIZE, TILE_SIZE);

            ID++;
        }
    }
}



GTile* GMap::GetTile(int X, int Y)
{
    int ID = 0;
    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));

    if(ID < 0 || ID >= tileList.size()) {
        return NULL;
    }

    return &tileList[ID];
}



/**
 * This function loads the image resources from a props file.
 *
*/
bool GMap::loadAllProps(char* propFile)
{
    FILE* fileHandler = fopen(propFile, "r");
    if(fileHandler == NULL)
    {
        return false;
    }

    while(true)
    {
        int key = -1;
        char value[255]="";
        if(fscanf(fileHandler, "%d=%s", &key, value) == EOF)
        {
            break;
        }
        std::string propName(value);
        propsResourceMap.insert(std::pair<int, std::string>(key, propName));
        resourceManager->loadImg(propName, renderer);
        fscanf(fileHandler, "\n");
    }
    fclose(fileHandler);

    return true;
}



/**
 * This function loads the image resources from a props file.
 * And applies the provided rgb color keying
 */
bool GMap::loadAllProps(char* propFile, int r, int g, int b)
{
    FILE* fileHandler = fopen(propFile, "r");
    if(fileHandler == NULL)
    {
        return false;
    }

    while(true)
    {
        int key = -1;
        char value[255];
        if(fscanf(fileHandler, "%d=%s", &key, value) == EOF)
        {
            break;
        }
        std::string propName(value);
        propsResourceMap.insert(std::pair<int, std::string>(key, propName));
        resourceManager->loadImg(propName, renderer, r, g, b);
        fscanf(fileHandler, "\n");

    }
    fclose(fileHandler);

    return true;
}



/**
 * This function loads the texture for the corresponding prop value.
 */
SDL_Texture* GMap::getPropTexture(int prop)
{
    std::map<int, std::string>::iterator it = propsResourceMap.find(prop);
    // if already in the map
    if (it != propsResourceMap.end())
    {
        // SDL_Log("Loaded from resource manager.");
        return resourceManager->loadImg(it->second, renderer);
    }

    return NULL;
}

