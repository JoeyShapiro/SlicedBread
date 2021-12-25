#include "Character.h"

//class Character { // keeping this helps me :P, but how does the header work
	//public:
		int x, y;
		char skin;
		Character::Character() {
			skin = '?';
		}

	void Character::setPos(int newx, int newy) {
		x = newx;
		y = newy;
	}
//};