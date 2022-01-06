#ifndef PLAYER_H
#define PLAYER_H

#include "Being.h"
#include "Item.h"

class Player : public Being {
	public: Player();
	int mapx;
	int mapy;
	Item items[10];
	Dossier dossierBase;
	int itemCnt;

	void handleInput(char key, bool isCharacter[]);

	void calcStats();

	bool addItem(Item item);

	void removeItem(int loc);
};

#endif