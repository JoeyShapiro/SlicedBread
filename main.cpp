#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>

#include "Character.h"
#include "Being.h"
#include "Player.h"
#include "Enemy.h"
#include "common.h"

using namespace std;

char kin() {
	int c = getch();
	ungetch(c);
	return getch();
}


Player player;

void reDrawStats() { // maybe in Player
	mvwprintw(stats, 0, 0, "Player Stats");
	mvwprintw(stats, 1, 0, "Health: %d", player.health);
}

int main() {
	int row, col;

	// start ncurses
	cbreak();
	initscr();			/* Start curses mode 		  */
	curs_set(0); // remove cursor
	getmaxyx(stdscr, row, col);

	// place windows
	game = newwin(row-8, col/2, 0, 0);
	winLog = newwin(row/4, col, row-8, 0);
	stats = newwin(row-8, col, 0, col/2);

	Character characters[row*col]; // could draw with matrix (x, y) but value is easy
	Enemy enemies[row*col]; // TODO find how to make to one ^
	bool isCharacter[row*col]; // make sure right order
	// TODO organize
	for (int i = 0; i < row*col; i++) { // find better way
		enemies[i].x = -1;
		enemies[i].y = -1;
	}

	// prelim
	enemies[0].setPos(1,1);
	for (int i = 0; i < row*col; i++) {
		if (enemies[i].x != -1)
			enemies[i].moveC();
	}

	player.setPos(5, 5);

	player.moveC();
	wrefresh(game);			/* Print it on to the real screen */
	wrefresh(winLog);
	wrefresh(stats);
	while (true) {
		char k = kin();
		wclear(game);
		wclear(winLog);
		wclear(stats);
		player.handleInput(k); // find how to make them all the same (be in for loop and check if player)
		for (int i = 0; i < row*col; i++)
			isCharacter[i] = false;
		//isCharacter[player.x+player.y*col] = true; // 5 + 5 * col = 1D loc
		for (int i=0; i<row*col; i++)
			isCharacter[enemies[i].x+enemies[i].y*col] = true;
		for (int i = 0; i < row*col; i++) { // for (Enemy e : enemies) // does not work, causes overflow
			if (enemies[i].x != -1) {
				enemies[i].act(player, isCharacter, col);
				enemies[i].moveC();
			}
		}
		reDrawStats(); // should be here... i think
		wrefresh(game);
		wrefresh(winLog);
		wrefresh(stats);
	}
	endwin();			/* End curses mode		  */

	return 0;
}