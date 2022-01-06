#ifndef INTERACTABLE_H // what does this do
#define INTERACTABLE_H

#include "Character.h"
#include <ncurses.h>
#include "common.h"
#include "Item.h"

class Interactable : public Character {
    public:
        Interactable();
        Item item;

    void moveC();
};

#endif