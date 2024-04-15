#ifndef __COMMON_FUNCTION__
#define __COMMON_FUNCTION__

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_rect.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_bullet[3];
static Mix_Chunk* g_sound_exp[2];

//Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 4; //fps

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 32
#define MAX_MAP_X 150
#define MAX_MAP_Y 50

#define LAND_TILE 1
#define SAND_TILE 2

struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	int space_;

};

struct Map {
	int start_x_; //position of minimap
	int start_y_;

	int max_x_;
	int max_y_;

	int gmap[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;

};

namespace SDLCommonFunc
{

	bool CheckCollisionMouse(int x, int y, const SDL_Rect& obj);                // kiểm tra vị trí của chuột có trong hình ảnh không
}
#endif /*__COMMON_FUNCTION__*/