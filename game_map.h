#ifndef __MAP__
#define __MAP__

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20 //number of types of tile can be used

class TileMat : public BaseObject {

public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap {

public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadTiles(SDL_Renderer* screen); //load img to list of tiles
	void LoadMap(char* name);
	void DrawMap(SDL_Renderer* screen);
	Map GetMap() const {
		return game_map_;
	}
	void SetMap(const Map& map_data) { game_map_ = map_data; }

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES]; //list of tiles
};

#endif /*__MAP__*/