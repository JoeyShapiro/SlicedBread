#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <queue>

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
	mvwprintw(stats, 0, 1, "Player Stats");
	mvwprintw(stats, 1, 1, "Health: %d", player.health);
}

void printQueue(queue<string> logs) { // abuses the rule used for enemy calling player
	queue<string> tmpLogs = logs; // maybe make own, that can print and delete as needed
	int i = 0;
	while (!tmpLogs.empty()) {
		i++;
		mvwprintw(winLog, i, 1, "%s", tmpLogs.front().c_str());
		tmpLogs.pop();
	}
}

void enLog(queue<string>& logs, string s) {
	int logSize = 6; // TODO find better place, maybe make class...
	if (logs.size() >= logSize) {
		logs.pop();
		logs.push(s);
	} else { // maybe change order
		logs.push(s);
	}
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
	winLog = newwin(row/3, col, row-8, 0);
	stats = newwin(row-8, col/2, 0, col/2);
	box(game, '*', '*');
	box(winLog, '*', '*');
	box(stats, '*', '*');

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
		enLog(logs, "hi");
		wclear(game);
		wclear(winLog);
		wclear(stats);
		box(game, '*', '*');
		box(winLog, '*', '*');
		box(stats, '*', '*');
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
		printQueue(logs);
		wrefresh(game);
		wrefresh(winLog);
		wrefresh(stats);
	}
	endwin();			/* End curses mode		  */

	return 0;
}