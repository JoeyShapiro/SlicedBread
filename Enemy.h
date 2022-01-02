#ifndef ENEMY_H
#define ENEMY_H

#include "Being.h"
#include "Player.h"
#include <math.h>
#include <ncurses.h>
#include "common.h"

class Player;

class Enemy : public Being {
	public: Enemy();

	void act(Player& player, bool isCharacter[], int col);
};

#endif