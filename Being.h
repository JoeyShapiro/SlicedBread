#ifndef BEING_H // what does this do
#define BEING_H

#include "Character.h"
#include <ncurses.h>
#include "common.h"
#include "Dossier.h"

class Being : public Character {
	public:
		Dossier dossier;

	void moveC();

	void checkPulse();

	int calcDamage();

	void damage(int dam);
};

#endif