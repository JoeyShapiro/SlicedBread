#ifndef BEING_H // what does this do
#define BEING_H

#include "Character.h"
#include <ncurses.h>

class Being : public Character {
	public:
		int health;

	void moveC();
};

#endif