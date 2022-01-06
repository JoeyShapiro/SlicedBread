#include "Interactable.h"

Interactable::Interactable() {
    skin = 'i';
}
Item item;

void Interactable::moveC() {
    mvwprintw(game, x, y, "%c", skin);
}