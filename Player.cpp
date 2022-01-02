#include "Player.h"
#include <string>

//class Player : public Being {
	//public: 
    Player::Player() {
		skin = '@';
		health = 100;
		ap = 2;
		phys = 15;
		critC = 25;
		critM = 1.2;
		defC = 5;
		def = 10;
		acc = 75;
		armor = 15;
	}
	int mapx = 0; // here for now
	int mapy = 0; // maybe each character, or map has character array, map array, because then would check each characeter in total array, rather than array in each map


	void Player::handleInput(char key, bool isCharacter[]) { // maybe make being (k, p) // has to be here ??
		int arrx = x-1; // took a while to find, is char starts at 0, player starts at 1, maybe draw char, needs that place i think
		int arry = y-1; // used to convert x and y to isChar array
		if (key == 'w' && !isCharacter[arry+(arrx-1)*39]) {
			x--; // --x, y
		} else if (key == 's' && !isCharacter[arry+(arrx+1)*39]) {
			x++; // ++x, y
		} else if (key == 'a' && !isCharacter[(arry-1)+arrx*39]) {
			y--; // x, --y
		} else if (key == 'd' && !isCharacter[(arry+1)+arrx*39]) {
			y++; // x, ++y
		} else if (key == 'w' && isCharacter[arry+(arrx-1)*39]) {
			for (int i=0; i<24; i++) {
				if (x == enemies[i].x+1 && y == enemies[i].y) { // smarter i think, to not cause oob
					int dam = calcDamage();
					enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
			}
		} else if (key == 's' && !isCharacter[arry+(arrx+1)*39]) {
			for (int i=0; i<24; i++) { // func maybe with enemy pos
				if (x == enemies[i].x-1 && y == enemies[i].y) { // smarter i think, to not cause oob
					int dam = calcDamage();
					enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
			}
		} else if (key == 'a' && !isCharacter[(arry-1)+arrx*39]) {
			for (int i=0; i<24; i++) {
				if (x == enemies[i].x && y == enemies[i].y+1) { // smarter i think, to not cause oob
					int dam = calcDamage();
					enemies[i].damage(dam);
					std::string log = "@: attacked e for " + std::to_string(dam); // cant use format string :(
					enLog(logs, log);
				}
			}
		} else if (key == 'd' && !isCharacter[(arry+1)+arrx*39]) {
			for (int i=0; i<24; i++) {
				if (x == enemies[i].x+1 && y == enemies[i].y-1) { // smarter i think, to not cause oob
					int dam = calcDamage();
					enemies[i].damage(dam);
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
			x = row-10;
			mapx--;
			enLog(logs, "new cell up");
		} else if (x > row-10) {
			x = 1;
			mapx++;
			enLog(logs, "new cell down");
		} else if (y < 1) {
			y = col/2-2;
			mapy--;
			enLog(logs, "new cell left");
		} else if (y > col/2-2) {
			y = 1;
			mapy++;
			enLog(logs, "new cell right");
		}
		moveC(); // maybe move
	}
//};