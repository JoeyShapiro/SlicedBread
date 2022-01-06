// do i need 2 files, maybe, cleann it up and use own names

#include "Cell.h"

char ground[GAME_H][GAME_W]; // separate types, they will need own place for stuff anyway
Interactable inters[24];
Enemy enemies[24]; // why cant i have duplicates, even in different classes
bool isCharacters[GAME_W*GAME_H]; // find how to use this, sadly for now just for spawns

void Cell::addCol() {
    for (int i=0; i<GAME_H; i++) {
		for (int j=0; j<GAME_W; j++) {
			if (ground[i][j] == ' ')
				continue;
			isCharacters[j+i*GAME_W] = true; // i did col, but its not that large
		}
	}
}

void Cell::spawns() {
    int rx = 0;
    int ry = 0;

    for (int i=0; i<24; i++) {
        srand(time(NULL));
        // find place to set enemy
        if (rand() % (i*i) == 0) {
            do {
                rx = rand() % GAME_H; // GAME_H-2 fixes wrong bus error
                ry = rand() % GAME_W;
            } while (isCharacters[ry+rx*GAME_W]); // (or reversed)rx+ry*w = "bus error", x,y might be reversed, oh well "as long as its consistant"
            enemies[i].setPos(rx, ry); // ^ im confused on the order or what happened, but it works
            isCharacters[ry+rx*GAME_W] = true;
        }
        // find place to set item
        if (rand() % i == 0) {
            do {
                rx = rand() % GAME_H; // GAME_H-3 fixes wrong bus error
                ry = rand() % GAME_W;
            } while (isCharacters[ry+rx*GAME_W]);
            inters[i].setPos(rx, ry);
            isCharacters[ry+rx*GAME_W] = true;
        }
    }
}