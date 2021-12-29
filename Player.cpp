#include "Player.h"

//class Player : public Being {
	//public: 
    Player::Player() {
		skin = '@';
		health = 100;
	}
	int mapx = 0; // here for now
	int mapy = 0; // maybe each character, or map has character array, map array, because then would check each characeter in total array, rather than array in each map


	void Player::handleInput(char key) { // maybe make being (k, p) // has to be here ??
		if (key == 'w') {
			x--; // --x, y
		} else if (key == 's') {
			x++; // ++x, y
		} else if (key == 'a') {
			y--; // x, --y
		} else if (key == 'd') {
			y++; // x, ++y
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

	void Player::damage(int dam) {
		health -= dam;
	}

//};