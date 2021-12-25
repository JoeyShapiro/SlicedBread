#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>

#include "Character.h"
#include "Being.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

char kin() {
	int c = getch();
	ungetch(c);
	return getch();
}

Player player;

int main() {
	player.setPos(5, 5);

	cbreak();
	initscr();			/* Start curses mode 		  */
	curs_set(0); // remove cursor
	player.moveC();
	refresh();			/* Print it on to the real screen */
	while (true) {
		char k = kin();
		clear();
		player.handleInput(k);
		refresh();
	}
	endwin();			/* End curses mode		  */

	return 0;
}