#include "game_map.h"


void GameMap::LoadTiles(SDL_Renderer* screen) {
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILES; i++) {
		sprintf_s(file_img, "map/%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) {
			continue;
		}
		tile_mat[i].LoadImg(file_img, screen);
		fclose(fp);
	}

}

void GameMap::LoadMap(char* name) {
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		std::cout << "read map file fail";
		return;
	}

	game_map_.start_y_ = 0;
	game_map_.start_x_ = 0;

	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;

	for (int j = 0; j < MAX_MAP_Y; j++) {
		for (int i = 0; i < MAX_MAP_X; i++) {
			fscanf_s(fp, "%d", &game_map_.gmap[j][i]);

			int val = game_map_.gmap[j][i];

			if (val >= 0) {
				game_map_.max_y_ = j;
				game_map_.max_x_ = i;
			}
		}
	}


	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE; //position in tile
	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;

	game_map_.file_name_ = name;
	fclose(fp);
}

void GameMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	x1 = (game_map_.start_x_ % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_y_ / TILE_SIZE;

	y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) {

		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map_.gmap[map_y][map_x];
			if (val > 0) {
				tile_mat[val].SetRect(j, i);
				tile_mat[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}