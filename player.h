#ifndef __PLAYER__
#define	__PLAYER__

#include "CommonFunc.h"
#include "BaseObject.h"

#define PLAYER_SPEED 0.6

#define animationRate 4
#define animationLength 4

class Player : public BaseObject {
public:
	Player();
	~Player();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
		WALK_SPACE = 4,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);
	bool LoadImag(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[3]);
	void Set_clips();

	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);

	void BuyRod() { //decrease money
		money -= 1;
	}

	void SellFish() {
		money += 1; //increase money
	}



private:
	int money;

	float x_val_; //how many frame do player walk
	float y_val_;

	float x_pos_; //current position of player
	float y_pos_;

	int width_frame_; // size of player animation
	int height_frame_;

	SDL_Rect frame_clip_[4];
	Input input_type_;
	int frame_;	//one animation
	int status_; //left or right
	bool on_ground_;

	int map_x_;
	int map_y_;
};


#endif /*__PLAYER__*/