#include "fish.h"
#include "CommonFunc.h"

// test int RandLuck (0-25 26-48 49-50)

// add all fishes of a type into a vector
void Fish::Fish_Dictionary(std::string typedata) {
	Fish gFish;
	std::ifstream fp;
	fp.open(typedata);

	if (!fp) {
		std::cout << "Cannot open fish file" << std::endl;
	}

	int total;
	fp >> total;

	while (fp >> gFish.id) {
		fp >> std::quoted(gFish.name);
		fp >> std::quoted(gFish.path);
		fp >> gFish.price;

		fish_dict.push_back(gFish);
	}
	fp.close();
}

// return fish from a type dictionary
Fish Fish::whichFish(std::string generaldata) {
	Fish_Dictionary(generaldata);

	int id = rand() % fish_dict.size();

	return fish_dict[id];
}


Fish Fish::RandFish(int luck) {
	Fish gFish;
	if (luck >= 0 && luck < 26) {
		gFish = whichFish("Data//trashdata.txt");
	}
	else if (luck >= 26 && luck < 49) {
		gFish = whichFish("Data//normaldata.txt");
	}
	else if (luck >= 49 && luck <= 50) {
		gFish = whichFish("Data//legendarydata.txt");
	}

	return gFish;
}

void Fish::DrawFish(Player *player, SDL_Renderer* screen) {
	SDL_Rect temp_rect = player->GetRect();
	this->SetRect(temp_rect.x, temp_rect.y - 32);

	LoadImg(this->path, screen);

}
