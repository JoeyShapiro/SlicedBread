#ifndef PLAYER_H
#define PLAYER_H

#include "Being.h"
#include "uncommon.h"
#include "Item.h"

class Player : public Being {
	public: Player();
	int mapx;
	int mapy;
	Item items[10];

	void handleInput(char key, bool isCharacter[]);
};

#endif