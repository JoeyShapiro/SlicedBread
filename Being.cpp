#include "Being.h"

//class Being : public Character {
	//public:
		int health;
		int ap;
		int phys;
		int critC;
		double critM;
		int defC;
		int def;
		int acc;
		int armor;

	void Being::moveC() {
		mvwprintw(game, x, y, "%c", skin);
	}

	void Being::checkPulse() {
		if (health <= 0) {
			setPos(-1, -1);
		}
	}

	int Being::calcDamage() {
		srand(time(0));
		double dam = phys;

		if (((rand() % 100) + 1) >= acc) // >= so less is more
			return 0;

		if (((rand() % 100) + 1) <= critC) // critC/100 is crit%, but recip(critC) should also give higher chance with higher number
			dam *= critM;

		return (int) dam;
	}

	void Being::damage(int dam) { // maybe move log here, or both, or combine here
		int taken = dam;

		if (((rand() % 100) + 1) <= defC)
			taken -= def; // maybe devide
		taken -= armor;
		if (taken <= 0)
			taken = 0;
		
		health -= taken;
	}
//};