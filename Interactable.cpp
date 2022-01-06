#include "Interactable.h"

Interactable::Interactable() {
    skin = 'i';
}
Item item;

void Interactable::moveC() {
    mvwprintw(game, x, y, "%c", skin);
}

Item Interactable::interact() { // do here yeah
    return item;
}

void Interactable::remove(bool rm) {
    setPos(-1, -1);
}