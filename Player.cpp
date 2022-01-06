#include "Player.h"
#include <string>
#include "uncommon.h" // this fixes "unknown type enemy, in Cell.h", it caused loop, put here it wont, only needs for work, not def

//class Player : public Being {
	//public: 
    Player::Player() {
		skin = '@';
		dossier.health = 100;
		dossier.ap = 2;
		dossier.phys = 15;
		dossier.critC = 25;
		dossier.critM = 1.2;
		dossier.defC = 5;
		dossier.def = 10;
		dossier.acc = 75;
		dossier.armor = 15;
	}
	int mapx = 0; // here for now
	int mapy = 0; // maybe each character, or map has character array, map array, because then would check each characeter in total array, rather than array in each map
	int itemCnt = 0;
	Item items[10];
	Dossier dossierMod;

	void Player::handleInput(char key, bool isCharacter[]) { // maybe make being (k, p) // has to be here ??
		int arrx = x-1; // took a while to find, is char starts at 0, player starts at 1, maybe draw char, needs that place i think
		int arry = y-1; // used to convert x and y to isChar array
		if (key == 'w' && !isCharacter[arry+(arrx-1)*GAME_W]) {
			x--; // --x, y
		} else if (key == 's' && !isCharacter[arry+(arrx+1)*GAME_W]) {
			x++; // ++x, y
		} else if (key == 'a' && !isCharacter[(arry-1)+arrx*GAME_W]) {
			y--; // x, --y
		} else if (key == 'd' && !isCharacter[(arry+1)+arrx*GAME_W]) {
			y++; // x, ++y
		} else if (key == 'w' && isCharacter[arry+(arrx-1)*GAME_W]) {
			for (int i=0; i<24; i++) {
				if (x == cells[mapx][mapy].enemies[i].x+1 && y == cells[mapx][mapy].enemies[i].y) { // smarter i think, to not cause oob
					int dam = calcDamage();
					cells[mapx][mapy].enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
			}
		} else if (key == 's' && isCharacter[arry+(arrx+1)*GAME_W]) {
			for (int i=0; i<24; i++) { // func maybe with enemy pos
				if (x == cells[mapx][mapy].enemies[i].x-1 && y == cells[mapx][mapy].enemies[i].y) { // smarter i think, to not cause oob
					int dam = calcDamage();
					cells[mapx][mapy].enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
			}
		} else if (key == 'a' && isCharacter[(arry-1)+arrx*GAME_W]) {
			for (int i=0; i<24; i++) {
				if (x == cells[mapx][mapy].enemies[i].x && y == cells[mapx][mapy].enemies[i].y+1) { // smarter i think, to not cause oob
					int dam = calcDamage();
					cells[mapx][mapy].enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
			}
		} else if (key == 'd' && isCharacter[(arry+1)+arrx*GAME_W]) {
			for (int i=0; i<24; i++) {
				if (x == cells[mapx][mapy].enemies[i].x+1 && y == cells[mapx][mapy].enemies[i].y-1) { // smarter i think, to not cause oob
					int dam = calcDamage();
					cells[mapx][mapy].enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
			}
		} else {
			// x, y
			 //cerr << key << endl;
		}
		// check if player should move to new cell
		if (x < 1) { // move moveC to main, then change map to it
			x = GAME_H;
			mapx--;
			enLog(logs, "new cell up");
		} else if (x > GAME_H) {
			x = 1;
			mapx++;
			enLog(logs, "new cell down");
		} else if (y < 1) {
			y = GAME_W;
			mapy--;
			enLog(logs, "new cell left");
		} else if (y > GAME_W-1) { // GAME_W should work, but doesnt
			y = 1;
			mapy++;
			enLog(logs, "new cell right");
		}
		moveC(); // maybe move
	}

	void Player::calcStats() {
		dossierMod.zero(); // zero out
		dossierMod += dossier;
		for (int i=0; i<itemCnt; i++) {
			dossierMod += items[i].itemDossier;
		}
	}

	void Player::addItem(Item item) {
		if (itemCnt < 10)
			items[itemCnt++] = item;// add to counter after
		else
			enLog(logs, "inventory full");
	}

	void Player::removeItem(int loc) { // could return but maybe later
		for (int i=loc; i<itemCnt-loc; i++) { // kinda smart
			items[i] = items[i+1];
		} // print upto itemCnt
	}
//};