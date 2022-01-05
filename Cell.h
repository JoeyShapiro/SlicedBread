#ifndef CELL_H // what does this do
#define CELL_H

#include "Interactable.h"
#include "Enemy.h"

class Cell {
    public:
        char ground[GAME_H][GAME_W]; // separate types, they will need own place for stuff anyway
        Interactable i[24];
        Enemy enemies[24]; // to fix "note: forward dec" and "unknown type" use "*", recursive dec is wierd
        
};

#endif