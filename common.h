#ifndef COMMON_H // what does this do
#define COMMON_H

#include <ncurses.h>
#include <string>
#include <queue>

extern WINDOW *game;
extern WINDOW *winLog;
extern WINDOW *stats;
extern WINDOW *menu;
extern std::queue<std::string> logs;

void enLog(std::queue<std::string>& logs, std::string s);

#endif