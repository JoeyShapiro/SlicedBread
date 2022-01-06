#include "Player.h"
#include <string>
#include "uncommon.h" // this fixes "unknown type enemy, in Cell.h", it caused loop, put here it wont, only needs for work, not def

//class Player : public Being {
	//public: 
    Player::Player() {
		skin = '@';
		dossierBase.health = 100;
		dossierBase.ap = 2;
		dossierBase.phys = 15;
		dossierBase.critC = 25;
		dossierBase.critM = 1.2;
		dossierBase.defC = 5;
		dossierBase.def = 10;
		dossierBase.acc = 75;
		dossierBase.armor = 10;
	}
	int mapx = 0; // here for now
	int mapy = 0; // maybe each character, or map has character array, map array, because then would check each characeter in total array, rather than array in each map
	int itemCnt = 0;
	Item items[10];
	Dossier dossierBase; // doing it this way is better, now Being. stuff should work

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
				if (x == cells[mapx][mapy].inters[i].x+1 && y == cells[mapx][mapy].inters[i].y) { // smarter i think, to not cause oob
					Item item = cells[mapx][mapy].inters[i].interact();
					bool rm = addItem(item);
					cells[mapx][mapy].inters[i].remove(rm);
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
				if (x == cells[mapx][mapy].inters[i].x-1 && y == cells[mapx][mapy].inters[i].y) {
					Item item = cells[mapx][mapy].inters[i].interact();
					bool rm = addItem(item);
					cells[mapx][mapy].inters[i].remove(rm);
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
				if (x == cells[mapx][mapy].inters[i].x && y == cells[mapx][mapy].inters[i].y+1) {
					Item item = cells[mapx][mapy].inters[i].interact();
					bool rm = addItem(item);
					cells[mapx][mapy].inters[i].remove(rm);
				}
			}
		} else if (key == 'd' && isCharacter[(arry+1)+arrx*GAME_W]) {
			for (int i=0; i<24; i++) {
				if (x == cells[mapx][mapy].enemies[i].x && y == cells[mapx][mapy].enemies[i].y-1) { // smarter i think, to not cause oob
					int dam = calcDamage();
					cells[mapx][mapy].enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
				if (x == cells[mapx][mapy].inters[i].x && y == cells[mapx][mapy].inters[i].y-1) {
					Item item = cells[mapx][mapy].inters[i].interact();
					bool rm = addItem(item);
					cells[mapx][mapy].inters[i].remove(rm);
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
		dossier.zero(); // zero out
		dossier += dossierBase;
		for (int i=0; i<itemCnt; i++) {
			dossier += items[i].itemDossier;
		}
	}

	bool Player::addItem(Item item) { // is it proper to return true or false
		if (itemCnt < 10) {
			items[itemCnt++] = item;// add to counter after
			calcStats();
			return true;
		} else {
			enLog(logs, "inventory full");
			return false;
		}
	}

	void Player::removeItem(int loc) { // could return but maybe later
		for (int i=loc; i<itemCnt-loc; i++) { // kinda smart
			items[i] = items[i+1];
		} // print upto itemCnt
		calcStats();
	}
//};