#include "Interactable.h"

Item item;

void Interactable::moveC() {
    mvwprintw(game, x, y, "%c", skin);
}