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
#include "Cells.h"

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

void genMap() {
	srand(time(NULL)); // "random" number
	map[0][0] = true;
	for (int i=0; i<MAP_S; i++) {
		for (int j=0; j<MAP_S; j++) {
			if(map[i+1][j] or map[i-1][j] or map[i][j+1] or map[i][j-1]) {
				if (rand() % i == 0) // i lowers the chances each time, i b smrt
					map[i][j] = true; // somehow, because of srand(), is now random
			}
		}
	}
	enLog(logs, "map generated");
}

void loadCell(bool isCharacter[]) {
	//bool curCell = map[player.mapx][player.mapy];
	for (int i=0; i<14; i++) {
		for (int j=0; j<39; j++) {
			if (LEFT[i][j] == ' ')
				continue;
			mvwprintw(game, i+1, j+1, "%c", LEFT[i][j]);
			isCharacter[j+i*39] = true; // i did col, but its not that large
		}
	}
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

void reDrawMenu() { // TODO maybe change wchich is shown or recreate each time
	string chosen = "map";
	mvwprintw(menu, 0, 2, "menu - %s", chosen.c_str());
	if (chosen == "map") {
		for (int i=0; i<MAP_S; i++) {
			for (int j=0; j<MAP_S; j++) {
				if (map[i][j] and i == player.mapx and j == player.mapy) {
					mvwprintw(menu, i+1, j+1, "@");
				} else if (map[i][j]) {
					mvwprintw(menu, i+1, j+1, "?");
				}
			}
		}
		mvwprintw(menu, 1, MAP_S+2, "Legend");
		mvwprintw(menu, 2, MAP_S+2, "@ Player");
		mvwprintw(menu, 3, MAP_S+2, "? Unknown");
		mvwprintw(menu, 4, MAP_S+2, "e Enemy");
		mvwprintw(menu, 5, MAP_S+2, "D Chest");
		mvwprintw(menu, 6, MAP_S+2, "E Elite");
	}
}

int main() {

	// start ncurses
	cbreak();
	initscr();			/* Start curses mode 		  */
	curs_set(0); // remove cursor
	getmaxyx(stdscr, row, col);

	// place windows TODO KISS
	game = newwin(row-8, col/2, 0, 0);
	winLog = newwin(row/3, col, row-8, 0);
	stats = newwin(row-8, col/5, 0, col/2);
	menu = newwin(row-8, col/3.3, 0, col/1.42); // what is this decimal nonsense
	box(game, '*', '*');
	mvwprintw(game, 0, col/4, "world - world"); // prints somewhere but also moves cursor
	box(winLog, '*', '*');
	box(stats, '*', '*');
	box(menu, '*', '*');

	Character characters[row*col]; // could draw with matrix (x, y) but value is easy
	Enemy enemies[row*col]; // TODO find how to make to one ^
	bool isCharacter[row*col]; // make sure right order
	genMap();
	// TODO organize
	for (int i = 0; i < row*col; i++) { // find better way
		enemies[i].x = -1;
		enemies[i].y = -1;
	}

	// prelim
	enemies[0].setPos(3,3);
	for (int i = 0; i < row*col; i++) {
		if (enemies[i].x != -1)
			enemies[i].moveC();
	}

	player.setPos(5, 5);

	player.moveC();
	enLog(logs, "https://github.com/JoeyShapiro/SlicedBread");
	wrefresh(game);			/* Print it on to the real screen */
	wrefresh(winLog);
	wrefresh(stats);
	wrefresh(menu);
	while (true) {
		char k = kin(); // "up" is 3 characters, because its "]]^" or something, on console, i mite b smarte
		wclear(game);
		wclear(winLog);
		wclear(stats);
		wclear(menu);
		box(game, '*', '*');
		mvwprintw(game, 0, col/(4)-7, "world - (%d, %d)", player.mapx, player.mapy);
		box(winLog, '*', '*');
		box(stats, '*', '*');
		box(menu, '*', '*');
		for (int i = 0; i < row*col; i++) // this was after loadCell(), zeroing it out
			isCharacter[i] = false;
		loadCell(isCharacter); // has to be first so player can see it
		//isCharacter[player.x+player.y*col] = true; // 5 + 5 * col = 1D loc
		for (int i=0; i<row*col; i++) {
			isCharacter[enemies[i].y+enemies[i].x*col] = true; // YAY this caused error, x+y*col, made x go oob, removing made e stop traveling
		} // but why did it change value, wait for ask, i bet it changed all to true which means 255, then -643...
		player.handleInput(k, isCharacter); // find how to make them all the same (be in for loop and check if player)
		// ^ should be here, makes sense, and gets most updated
		for (int i = 0; i < row*col; i++) { // for (Enemy e : enemies) // does not work, causes overflow
			if (enemies[i].x != -1) {
				enemies[i].act(player, isCharacter, col);
				enemies[i].moveC();
			}
		}
		reDrawStats(); // should be here... i think
		reDrawMenu();
		printQueue(logs);
		wrefresh(game);
		wrefresh(winLog);
		wrefresh(stats);
		wrefresh(menu);
	}
	endwin();			/* End curses mode		  */

	return 0;
}