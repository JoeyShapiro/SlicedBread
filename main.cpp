#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>

using namespace std;

char kin() {
	int c = getch();
	ungetch(c);
	return getch();
}

class Character {
	public:
		int x, y;
		char skin;

	void moveC() {
		mvprintw(x, y, "%c", skin);
	}
};

int main() {	
	Character player;
	player.x = 5;
	player.y = 5;
	player.skin = '@';

	cbreak();
	initscr();			/* Start curses mode 		  */
	curs_set(0);
	player.moveC();
	refresh();			/* Print it on to the real screen */
	while (true) {
		char k = kin();
		clear();
		if (k == 'w') {
			player.x--;
			player.moveC(); // --x, y
		} else if (k == 's') {
			player.x++;
			player.moveC(); // ++x, y
		} else if (k == 'a') {
			player.y--;
			player.moveC(); // x, --y
		} else if (k == 'd') {
			player.y++;
			player.moveC(); // x, ++y
		} else {
			player.moveC(); // x, y
		}
		refresh();
	}
	endwin();			/* End curses mode		  */

	return 0;
}