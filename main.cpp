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
#include "uncommon.h"
#include "Cell.h"

using namespace std;

char kin() {
	int c = getch();
	ungetch(c);
	return getch();
}

Player player;

void reDrawStats() { // maybe in Player
	mvwprintw(stats, 0, 1, "Player Stats");
	mvwprintw(stats, 1, 1, "Health: %d", player.dossier.health);
	mvwprintw(stats, 2, 1, "AP:     %d", player.dossier.ap);
	mvwprintw(stats, 3, 1, "Phys:   %d", player.dossier.phys);
	mvwprintw(stats, 4, 1, "Acc:    %d", player.dossier.acc);
	mvwprintw(stats, 5, 1, "Armor:  %d", player.dossier.armor);
	mvwprintw(stats, 6, 1, "Crit C: %d", player.dossier.critC);
	mvwprintw(stats, 7, 1, "Crit M: %.2f", player.dossier.critM);
	mvwprintw(stats, 8, 1, "Def:    %d", player.dossier.def);
	mvwprintw(stats, 9, 1, "Def C:  %d", player.dossier.defC);
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

void mapCells() {
	for (int i=0; i<MAP_S; i++) {
		for (int j=0; j<MAP_S; j++) {
			bool up = false; // dont need i think, but keeps it clean
			bool down = false;
			bool left = false;
			bool right = false;
			if (i > 0)
				up = map[i-1][j];
			if (i < MAP_S+1)
				down = map[i+1][j];
			if (j > 0)
				left = map[i][j-1];
			if (j < MAP_S+1)
				right = map[i][j+1];
			if (!map[i][j]) // if cell is empty
				continue;
			// TODO how do i deal with oob
			if (map[i][j] && up && left && right && down) // + //  must be reverse order (least likely first (slime trap))
				memcpy(cells[i][j].ground, UDLR, sizeof(cells[i][j].ground));
			else if (map[i][j] && up && left && right) // -'-
				memcpy(cells[i][j].ground, HORIZONTALUP, sizeof(cells[i][j].ground));
			else if (map[i][j] && up && left && down) // -|
				memcpy(cells[i][j].ground, VERTICALLEFT, sizeof(cells[i][j].ground));
			else if (map[i][j] && up && right && down) // |-
				memcpy(cells[i][j].ground, VERTICALRIGHT, sizeof(cells[i][j].ground));
			else if (map[i][j] && down && left && right) // T
				memcpy(cells[i][j].ground, HORIZONTALDOWN, sizeof(cells[i][j].ground));
			else if (map[i][j] && down && left) // -,
				memcpy(cells[i][j].ground, LEFTDOWN, sizeof(cells[i][j].ground));
			else if (map[i][j] && up && left) // -'
				memcpy(cells[i][j].ground, LEFTUP, sizeof(cells[i][j].ground));
			else if (map[i][j] && down && right) // L(upside down)
				memcpy(cells[i][j].ground, DOWNRIGHT, sizeof(cells[i][j].ground));
			else if (map[i][j] && up && right) // L
				memcpy(cells[i][j].ground, UPRIGHT, sizeof(cells[i][j].ground));
			else if (map[i][j] && down && up) // |
				memcpy(cells[i][j].ground, VERTICAL, sizeof(cells[i][j].ground));
			else if (map[i][j] && left && right) // _
				memcpy(cells[i][j].ground, HORIZONTAL, sizeof(cells[i][j].ground));
			else if (map[i][j] && down) // , // maybe make Cells class for "Cells."
				memcpy(cells[i][j].ground, DOWN, sizeof(cells[i][j].ground)); // use size of ground, this will mean it CANT overcopy, i think
			else if (map[i][j] && left) // -(left) // TODO maybe be fancy and do later
				memcpy(cells[i][j].ground, LEFT, sizeof(cells[i][j].ground));
			else if (map[i][j] && right) // -(right)
				memcpy(cells[i][j].ground, RIGHT, sizeof(cells[i][j].ground));
			else if (map[i][j] && up) // '
				memcpy(cells[i][j].ground, UP, sizeof(cells[i][j].ground));
			else
				memcpy(cells[i][j].ground, TEST, sizeof(cells[i][j].ground)); // failsafe, kinda ut not really
			cells[i][j].addCol(); // things spawned in walls, nvr gave coll, got lucky most didnt
		}
	}
	enLog(logs, "cells mapped");
}

void spawnStuff() {
	srand(time(NULL));
	for (int i=0; i<MAP_S; i++) {
		for (int j=0; j<MAP_S; j++) {
			if (!map[i][j])
				continue;
			cells[i][j].spawns();
		}
	}
}

void loadCell(bool isCharacter[]) {
	//bool curCell = map[player.mapx][player.mapy];
	for (int i=0; i<GAME_H; i++) {
		for (int j=0; j<GAME_W; j++) {
			if (cells[player.mapx][player.mapy].ground[i][j] == ' ')
				continue;
			mvwprintw(game, i+1, j+1, "%c", cells[player.mapx][player.mapy].ground[i][j]);
			isCharacter[j+i*GAME_W] = true; // i did col, but its not that large
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

		mvwprintw(menu, 7, 1, "Items");
		for (int i=0; i<player.itemCnt; i++) {
			mvwprintw(menu, 8+i, 1, "%s", player.items[i].name.c_str());
		}
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
	bool isCharacter[row*col]; // make sure right order
	genMap();
	mapCells();
	player.calcStats();
	// TODO organize
	for (int i=0; i<MAP_S; i++) {
		for (int j=0; j<MAP_S; j++) {
			for (int k = 0; k < 24; k++) { // find better way
				cells[i][j].enemies[k].x = -1;
				cells[i][j].enemies[k].y = -1;
				cells[i][j].inters[k].x = -1; // smert
				cells[i][j].inters[k].y = -1;
			}
		}
	}
	spawnStuff();

	// prelim
	//cells[player.mapx][player.mapy].enemies[0].setPos(3,3); // you can do this!?
	for (int i = 0; i < 24; i++) {
		if (cells[player.mapx][player.mapy].enemies[i].x != -1)
			cells[player.mapx][player.mapy].enemies[i].moveC();
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
		// ^ maybe with handle input, so there is no room between, isChar and where can move
		wclear(game);
		wclear(winLog);
		wclear(stats);
		wclear(menu);
		box(game, '*', '*');
		mvwprintw(game, 0, col/(4)-7, "world - (%d, %d)", player.mapx, player.mapy);
		box(winLog, '*', '*');
		box(stats, '*', '*');
		box(menu, '*', '*');
		player.handleInput(k, isCharacter); // find how to make them all the same (be in for loop and check if player)
		// ^ should ACTUALLy be here, makes sense, and gets most updated,, alines with what player "sees"
		for (int i = 0; i < row*col; i++) // this was after loadCell(), zeroing it out
			isCharacter[i] = false;
		player.checkPulse();
		if (player.x == -1) { // GAMEOVER
			enLog(logs, "system: GAMEOVER");
			continue; // how should i do this
		}
		loadCell(isCharacter); // has to be first so player can see it
		//isCharacter[player.x+player.y*col] = true; // 5 + 5 * col = 1D loce x go oob, removing made e stop traveling
		// but why did it change value, wait for ask, i bet it changed all to true which means 255, then -643...
		for (int i = 0; i < 24; i++) { // for (Enemy e : cells[player.mapx][player.mapy].enemies) // does not work, causes overflow
			cells[player.mapx][player.mapy].enemies[i].checkPulse();
			if (cells[player.mapx][player.mapy].enemies[i].x != -1) {
				cells[player.mapx][player.mapy].enemies[i].act(player, isCharacter, col);
				cells[player.mapx][player.mapy].enemies[i].moveC(); // this would move/update but isChar would be delayed, now update then update isChar
				isCharacter[(cells[player.mapx][player.mapy].enemies[i].y-1)+(cells[player.mapx][player.mapy].enemies[i].x-1)*GAME_W] = true; // YAY this caused error, x+y*col, made x go oob, removing made e stop traveling
			}
			if (cells[player.mapx][player.mapy].inters[i].x != -1) { // smert :P
				cells[player.mapx][player.mapy].inters[i].moveC();
				isCharacter[(cells[player.mapx][player.mapy].inters[i].y-1)+(cells[player.mapx][player.mapy].inters[i].x-1)*GAME_W] = true;
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