#include "player.h"

Player::Player() {
	frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;

	x_pos_ = 0;
	y_pos_ = 0;

	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	input_type_.space_ = 0;

	map_x_ = 0;
	map_y_ = 0;

	money = 0;
}
Player::~Player() {

}

bool Player::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true) {
		width_frame_ = rect_.w / 4; //4 frame of animations
		height_frame_ = rect_.h;
	}

	return ret;
}
bool Player::LoadImag(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImag(path, screen);

	if (ret == true) {
		width_frame_ = rect_.w; //4 frame of animations
		height_frame_ = rect_.h;
	}

	return ret;
}

void Player::Set_clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2 * width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;
	}
}

void Player::Show(SDL_Renderer* des) {
	if (status_ == WALK_LEFT) { LoadImg("img//player_left.png", des); }
	else if (status_ == WALK_RIGHT) { LoadImg("img//player_right.png", des); }
	else if (status_ == WALK_UP) { LoadImg("img//player_up.png", des); }
	else if (status_ == WALK_DOWN) { LoadImg("img//player_down.png", des); }
	else if (status_ == WALK_SPACE) { LoadImag("img//player_fishing.png", des); }


	//set speed?
	frame_ = (SDL_GetTicks() * animationRate / 500) % animationLength;

	if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.up_ == 1 || input_type_.down_ == 1) {
		frame_++;
	}
	else {
		frame_ = 0;
	}
	if (frame_ >= 4) {
		frame_ = 0;
	}

	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void Player::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[3]) {
	//Mix_PlayChannel(-1, bullet_sound[0], 0);
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
		case SDLK_d: {
			status_ = WALK_RIGHT;
			input_type_.space_ = 0;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
				   break;

		case SDLK_a: {
			status_ = WALK_LEFT;
			input_type_.space_ = 0;
			input_type_.right_ = 0;
			input_type_.left_ = 1;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
				   break;

		case SDLK_w: {
			status_ = WALK_UP;
			input_type_.space_ = 0;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_ = 1;
			input_type_.down_ = 0;
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
				   break;

		case SDLK_s: {
			status_ = WALK_DOWN;
			input_type_.space_ = 0;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 1;
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
				   break;
		case SDLK_SPACE: {
			status_ = WALK_SPACE;
			input_type_.space_ = 1;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}
					   break;

		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_d: {
			input_type_.right_ = 0;
		}
				   break;

		case SDLK_a: {
			input_type_.left_ = 0;

		}
				   break;

		case SDLK_w: {
			input_type_.up_ = 0;
		}
				   break;

		case SDLK_s: {
			input_type_.down_ = 0;
		}
				   break;
		case SDLK_SPACE: {
			input_type_.space_ = 0;
		}
					   break;
		default:
			break;
		}
	}
}

void Player::DoPlayer(Map& map_data) {
	x_val_ = 0;
	y_val_ = 0;

	if (input_type_.left_ == 1) {
		x_val_ -= PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1) {
		x_val_ += PLAYER_SPEED;
	}
	else if (input_type_.up_ == 1) {
		y_val_ -= PLAYER_SPEED;
	}
	else if (input_type_.down_ == 1) {
		y_val_ += PLAYER_SPEED;
	}
	CheckToMap(map_data);
	CenterEntityOnMap(map_data);
}

void Player::CheckToMap(Map& map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//check horizontal
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (x_val_ > 0) { //player is moving right

			int val1 = map_data.gmap[y1][x2];
			int val2 = map_data.gmap[y2][x2];

			if ((val1 != LAND_TILE && val1 != SAND_TILE) ||
				(val2 != LAND_TILE && val2 != SAND_TILE)) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= (width_frame_ + 1);
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) {

			int val1 = map_data.gmap[y1][x1];
			int val2 = map_data.gmap[y2][x1];

			if ((val1 != LAND_TILE && val1 != SAND_TILE) ||
				(val2 != LAND_TILE && val2 != SAND_TILE)) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}


	//check vertical
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (y_val_ > 0) {

			int val1 = map_data.gmap[y2][x1];
			int val2 = map_data.gmap[y2][x2];

			if ((val1 != LAND_TILE && val1 != SAND_TILE) ||
				(val2 != LAND_TILE && val2 != SAND_TILE)) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
			}
		}
		else if (y_val_ < 0) {

			int val1 = map_data.gmap[y1][x1];
			int val2 = map_data.gmap[y1][x2];

			if ((val1 != LAND_TILE && val1 != SAND_TILE) ||
				(val2 != LAND_TILE && val2 != SAND_TILE)) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ >= map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	/*if (y_pos_ < 0) {
		y_pos_ = 0;
	}
	else if (y_pos_ + height_frame_ >= map_data.max_y_) {
		y_pos_ = map_data.max_y_ - height_frame_ - 1;
	}*/
}

void Player::CenterEntityOnMap(Map& map_data) {
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);

	if (map_data.start_x_ < 0) {
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) {
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);

	if (map_data.start_y_ < 0) {
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_) {
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}