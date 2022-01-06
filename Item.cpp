#include "Item.h"

Item::Item() {
    name = "test";
    itemDossier.health = rand() % 2;
    itemDossier.acc = rand() % 2;
    itemDossier.ap = rand() % 2;
    itemDossier.armor = rand() % 2;
    itemDossier.critC = rand() % 2;
    itemDossier.critM = (double) (rand() % 2);
    itemDossier.def = rand() % 2;
    itemDossier.defC = rand() % 2;
    itemDossier.phys = rand() % 2;
};

std::string name;
Dossier itemDossier;