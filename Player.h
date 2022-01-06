#ifndef PLAYER_H
#define PLAYER_H

#include "Being.h"
#include "Item.h"

class Player : public Being {
	public: Player();
	int mapx;
	int mapy;
	Item items[10];
	Dossier dossierMod;
	int itemCnt;

	void handleInput(char key, bool isCharacter[]);

	void calcStats();

	void addItem(Item item);

	void removeItem(int i);
};

#endif