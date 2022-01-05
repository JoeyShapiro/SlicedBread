#ifndef COMMON_H // what does this do
#define COMMON_H

#include <ncurses.h>
#include <string>
#include <queue>
#include <chrono>

#define MAP_S 5
#define GAME_W 38
#define GAME_H 14

extern WINDOW *game;
extern WINDOW *winLog;
extern WINDOW *stats;
extern WINDOW *menu;
extern std::queue<std::string> logs;
extern int row;
extern int col;
extern bool map[MAP_S][MAP_S];
extern int logC;
//using namespace std::chrono;
//extern seconds starts;

void enLog(std::queue<std::string>& logs, std::string s);

#endif