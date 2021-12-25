#include "Player.h"

//class Player : public Being {
	//public: 
    Player::Player() {
		skin = '@';
	}

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
		moveC(); // maybe move
	}

//};