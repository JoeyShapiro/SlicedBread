#ifndef CHARACTER_H
#define CHARACTER_H

#include <ncurses.h>

class Character {
	public:
		int x, y;
		char skin;
		Character();

	void setPos(int newx, int newy);
};

#endif