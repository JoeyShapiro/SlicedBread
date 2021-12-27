#include "Enemy.h"

//class Enemy : public Being {
	//public:
    Enemy::Enemy() {
		skin = 'e';
	}

	void Enemy::act(Player player, bool isCharacter[], int col) { // 2d in c++ is weird
		int possibleMoves[4][2] = {{x+1,y}, {x-1,y}, {x,y+1}, {x,y-1}}; // TODO should they be like king or can player do that
		int legalMoves[4][2] = {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}};
		for (int i=0; i<4; i++) {
			int tmpx = possibleMoves[i][0];
			int tmpy = possibleMoves[i][1];
			mvwprintw(winLog, i,0, "%d", isCharacter[tmpx+tmpy*col]);
			if (!isCharacter[tmpx + tmpy * col]) {
				legalMoves[i][0] = tmpx;
				legalMoves[i][1] = tmpy;
			}
		}
		int bestMove[2] = {x, y};
		int bestH = 1000; // INFINITY doesnt work ?

		for (int i=0; i<4; i++) {
			if (legalMoves[i][0] == -1)
				continue;
			int xPrime = legalMoves[i][0];
			int yPrime = legalMoves[i][1];
			int h = abs(xPrime - player.x) + abs(yPrime - player.y);
			
			if (h <= bestH) {
				bestH = h;
				x = xPrime;
				y = yPrime;
			}
		}
	}
//};