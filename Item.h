#ifndef ITEM_H // what does this do
#define ITEM_H

#include "common.h"
#include <string>
#include "Dossier.h"

class Item {
    public:
    Item();
		std::string name;
    Dossier itemDossier;
};

#endif