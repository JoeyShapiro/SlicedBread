#include "common.h"

WINDOW *game;
WINDOW *winLog;
WINDOW *stats;
WINDOW *menu;
std::queue<std::string> logs; // im lazy :P
int row;
int col;
bool map[MAP_S][MAP_S];


void enLog(std::queue<std::string>& logs, std::string s) {
	int logSize = 6; // TODO find better place, maybe make class...
	if (logs.size() >= logSize) {
		logs.pop();
		logs.push(s);
	} else { // maybe change order
		logs.push(s);
	}
}