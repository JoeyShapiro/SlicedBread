#include "Dossier.h"

int health;
int ap;
int phys;
int critC;
double critM;
int defC;
int def;
int acc;
int armor;

void Dossier::zero() {
    health = 0;
    ap = 0;
    phys = 0;
    critC = 0;
    critM = 0.0;
    defC = 0;
    def = 0;
    acc = 0;
    armor = 0;
}

Dossier &operator+=(Dossier &A, Dossier& B) {
    A.health += B.health; // maybe use tmp
    A.ap += B.ap;
    A.phys += B.phys;
    A.critC += B.critC;
    A.critM += B.critM;
    A.defC += B.defC;
    A.def += B.def;
    A.acc += B.acc;
    A.armor += B.armor;

    return A;
}