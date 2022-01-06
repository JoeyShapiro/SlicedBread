#ifndef DOSSIER_H // what does this do
#define DOSSIER_H

#include "common.h"
#include <string>

class Dossier {
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

	void zero();

	friend Dossier &operator+=(Dossier &A, Dossier& B);
};

#endif