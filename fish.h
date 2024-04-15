#ifndef FISH_H_
#define FISH_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "player.h"

class Fish : public BaseObject {
public:
	Fish() { ; }
	~Fish() { ; }

	std::string GetPath() { return path;  }

	void Fish_Dictionary(std::string typedata);

	Fish RandFish(int luck);
	Fish whichFish(std::string generaldata);

	void DrawFish(Player* player, SDL_Renderer* screen);

protected:
	int id;
	std::string name;
	std::string path;
	int price;

	std::vector<Fish> fish_dict;

	float x_pos;
	float y_pos;
};


#endif