#include "Player.h"
#include <string>

//class Player : public Being {
	//public: 
    Player::Player() {
		skin = '@';
		health = 100;
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
		} else {
			// x, y
			 //cerr << key << endl;
		}
		for (int i=0; i<14; i++) {
			std::string test = "";
			for (int j=0; j<39; j++) {
				if (isCharacter[j+i*39])
					test += '1';
				else
					test += ' ';
			}
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