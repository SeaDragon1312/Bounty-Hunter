#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "common.h"
#include "BaseObject.h"
#include <fstream>

#define MAX_TILES 20        // số loại map nhiều nhất (thùng, đất, xu, ....)

class TileMat : public BaseObject   // TileMat kế thừa từ BaseObject
{
public:
    TileMat(){;}
    ~TileMat(){;}
};

class GameMap           // định nghĩa lớp GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}


    void LoadMap(char* name);                   // Load map từ file
    void LoadTIles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;};
    void SetMap(Map& map_data) {game_map = map_data;};
private:
    Map game_map;
    TileMat tile_mat[MAX_TILES];
};

#endif // GAME_MAP_H
