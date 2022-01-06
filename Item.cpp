#include "Item.h"

Item::Item() { // i think its going so fast time() doesnt chagne anything
    srand(time(0));
    name = "item " + std::to_string(rand()%10); //names[rand() % 10];
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

std::string names[10] = {"Helmet", "Boots", "Chestplate", "Gauntlets", "Shield", "Trousers", "Cape", "Hat", "Thing", "Other Thing"};