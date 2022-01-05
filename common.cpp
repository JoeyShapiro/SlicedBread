#include "common.h"

WINDOW *game;
WINDOW *winLog;
WINDOW *stats;
WINDOW *menu;
std::queue<std::string> logs; // im lazy :P
int row;
int col;
bool map[MAP_S][MAP_S];
int logC = 0;
// seconds starts = duration_cast<seconds>(
//     	system_clock::now().time_since_epoch()
// ); // maybe use just simple counter, but this is more fun
// timer is cool, but i did it, its not great and kinda big for log, also not useful for speed and legibility


void enLog(std::queue<std::string>& logs, std::string s) {
	int logSize = 6; // TODO find better place, maybe make class...
	// seconds ss = duration_cast<seconds>(
    // 	system_clock::now().time_since_epoch()
	// ); // maybe use just simple counter, but this is more fun
	std::string ts = std::to_string(++logC) + " : " + s; // time + string // this is clever, i like ++c
	if (logs.size() >= logSize) {
		logs.pop();
		logs.push(ts);
	} else { // maybe change order
		logs.push(ts);
	}
}