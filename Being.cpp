#include "Being.h"

//class Being : public Character {
	//public:
		int health;

	void Being::moveC() {
		mvwprintw(game, x, y, "%c", skin);
	}
//};