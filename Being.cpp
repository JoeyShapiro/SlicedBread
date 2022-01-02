#include "Being.h"

//class Being : public Character {
	//public:
		Dossier dossier;

	void Being::moveC() {
		mvwprintw(game, x, y, "%c", skin);
	}

	void Being::checkPulse() {
		if (dossier.health <= 0) {
			setPos(-1, -1);
		}
	}

	int Being::calcDamage() {
		srand(time(0));
		double dam = dossier.phys;

		if (((rand() % 100) + 1) >= dossier.acc) // >= so less is more
			return 0;

		if (((rand() % 100) + 1) <= dossier.critC) // critC/100 is crit%, but recip(critC) should also give higher chance with higher number
			dam *= dossier.critM;

		return (int) dam;
	}

	void Being::damage(int dam) { // maybe move log here, or both, or combine here
		int taken = dam;

		if (((rand() % 100) + 1) <= dossier.defC)
			taken -= dossier.def; // maybe devide
		taken -= dossier.armor;
		if (taken <= 0)
			taken = 0;
		
		dossier.health -= taken;
	}
//};