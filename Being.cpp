#include "Being.h"

//class Being : public Character {
	//public:
		int health;

	void Being::moveC() {
		mvwprintw(game, x, y, "%c", skin);
	}

	void Being::checkPulse() {
		if (health <= 0) {
			setPos(-1, -1);
		}
	}
//};