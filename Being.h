#ifndef BEING_H // what does this do
#define BEING_H

#include "Character.h"
#include <ncurses.h>
#include "common.h"

class Being : public Character {
	public:
		int health;
		int ap;
		int phys;
		int critC;
		double critM;
		int defC;
		int def;
		int acc;
		int armor;

	void moveC();

	void checkPulse();

	int calcDamage();

	void damage(int dam);
};

#endif