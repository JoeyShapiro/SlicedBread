#ifndef PLAYER_H
#define PLAYER_H

#include "Being.h"

class Player : public Being {
	public: Player();
	int mapx;
	int mapy;

	void handleInput(char key);

	void damage(int dam);
};

#endif