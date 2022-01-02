#ifndef CELL_H // what does this do
#define CELL_H

#include "Interactable.h"
#include "Enemy.h"


class Cell {
    public:
        char ground[14][38]; // separate types, they will need own place for stuff anyway
        Interactable i[24];
        Enemy enemies[24];
        
};

#endif