#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "player.h"
#include "SDL_mixer.h"


Mix_Chunk* bullet_sound[3];

BaseObject g_background;
BaseObject play_bottom;
BaseObject play_bottom_pressed;
BaseObject exit_button;
BaseObject exit_button_pressed;
BaseObject menu_background;
bool is_quit = false;


bool InitData() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);

	if (ret < 0) {
		std::cout << "SDL init fail\n";
		return false;
	}
	else {
		std::cout << "SDL init success\n";
		g_window = SDL_CreateWindow("Game",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (g_window == NULL) {
			std::cout << "window init fail\n";
			success = false;
		}
		else {
			std::cout << "window init success\n";
			g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_screen == NULL) {
				std::cout << "renderer init fail\n";
				success = false;
			}
			else {
				std::cout << "renderer init success\n";
				SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) && imgFlags)) {
					success = false;
				}
			}
		}
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return false;
	}

	g_sound_bullet[0] = Mix_LoadWAV("nhacnen.wav");
	g_sound_bullet[1] = Mix_LoadWAV("vutcancau.wav");
	g_sound_bullet[2] = Mix_LoadWAV("dichuyen.wav");

	return success;
}

bool LoadBackground() {
	bool ret = g_background.LoadImg("map//background.png", g_screen);
	if (ret == false) {
		std::cout << "load bg fail\n";
		return false;
	}
	std::cout << "load bg success\n";
	return true;
}

void close() {
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();

}

#undef main

int menu()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		std::cout << Mix_GetError() << std::endl;
	}
	Mix_Music* opening = NULL;
	opening = Mix_LoadMUS("audio/AweAmbience.wav");
	Mix_PlayMusic(opening, -1);

	Mix_Chunk* click = Mix_LoadWAV("audio/click.wav");



	bool ret = play_bottom.LoadImg("map/play.png", g_screen);
	play_bottom.SetRect(SCREEN_WIDTH * 0.5 - 520, SCREEN_HEIGHT * 0.1);

	ret = play_bottom_pressed.LoadImg("map/play_pressed.png", g_screen);
	play_bottom_pressed.SetRect(SCREEN_WIDTH * 0.5 - 520, SCREEN_HEIGHT * 0.1);

	ret = exit_button.LoadImg("map/exit.png", g_screen);
	exit_button.SetRect(SCREEN_WIDTH * 0.5 - 520, SCREEN_HEIGHT * 0.3);

	ret = exit_button_pressed.LoadImg("map/exit_pressed.png", g_screen);
	exit_button_pressed.SetRect(SCREEN_WIDTH * 0.5 - 520, SCREEN_HEIGHT * 0.3);

	ret = menu_background.LoadImg("map/cauca.png", g_screen);

	bool quit = false;
	while (!quit)
	{
		int xm, ym;
		SDL_GetMouseState(&xm, &ym);
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (SDLCommonFunc::CheckCollisionMouse(xm, ym, play_bottom.GetRect()))
			{
				if (g_event.type == SDL_MOUSEBUTTONDOWN) {
					Mix_PlayChannel(-1, click, 0);
					quit = true;
				}
			}
			if (SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect()))
			{
				if (g_event.type == SDL_MOUSEBUTTONDOWN) {
					Mix_PlayChannel(-1, click, 0);
					quit = true;
					is_quit = true;
				}
			}
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		menu_background.Render(g_screen, NULL);

		play_bottom.Render(g_screen);
		exit_button.Render(g_screen);
		if (SDLCommonFunc::CheckCollisionMouse(xm, ym, play_bottom.GetRect())) {
			play_bottom_pressed.Render(g_screen);
		}
		if (SDLCommonFunc::CheckCollisionMouse(xm, ym, exit_button.GetRect())) {
			exit_button_pressed.Render(g_screen);
		}

		SDL_RenderPresent(g_screen);
	}
	Mix_FreeMusic(opening);
	//time_in_menu = SDL_GetTicks();              // lấy thời gian ở trong menu vì SDL_GetTick() bấm giờ khi chương trình bắt đầu chạy
	menu_background.Free();
	play_bottom.Free();
	play_bottom_pressed.Free();
	return 0;
}
int main(int argc, char argv[]) {
	if (InitData() == false)
		return -1;

	if (LoadBackground() == false)
		return -1;

	GameMap game_map;
	game_map.LoadMap((char*)"map/map.dat");
	game_map.LoadTiles(g_screen);

	Player p_player;
	p_player.LoadImg("img//player_right.png", g_screen);
	p_player.Set_clips();



	while (!is_quit) {

		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
			}

			p_player.HandleInputAction(g_event, g_screen, g_sound_bullet);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL);
		game_map.DrawMap(g_screen);

		Map map_data = game_map.GetMap();

		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		game_map.SetMap(map_data);


		SDL_RenderPresent(g_screen);
	}

	close();
	return 0;
}