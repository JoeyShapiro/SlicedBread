#ifndef PLAYER_H
#define PLAYER_H

#include "Being.h"

class Player : public Being {
	public: Player();

	void handleInput(char key);

};

#endif