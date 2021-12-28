#include "Enemy.h"

//class Enemy : public Being {
	//public:
    Enemy::Enemy() {
		skin = 'e';
	}

	void Enemy::act(Player& player, bool isCharacter[], int col) { // 2d in c++ is weird, must be Player& to pass object and not create a tmp o?
		int possibleMoves[5][2] = {{x+1,y}, {x-1,y}, {x,y+1}, {x,y-1}, {x, y}}; // TODO should they be like king or can player do that
		int legalMoves[5][2] = {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1, -1}};
		// get all legal moves
		for (int i=0; i<5; i++) {
			int tmpx = possibleMoves[i][0];
			int tmpy = possibleMoves[i][1];
			if (!isCharacter[tmpx + tmpy * col]) {
				legalMoves[i][0] = tmpx;
				legalMoves[i][1] = tmpy;
			}
		}
		int bestH = 1000; // INFINITY doesnt work ?
		int bestM[2] = {x, y};

		for (int i=0; i<5; i++) {
			if (legalMoves[i][0] == -1)
				continue;
			int xPrime = legalMoves[i][0];
			int yPrime = legalMoves[i][1];
			int h = abs(xPrime - player.x) + abs(yPrime - player.y);
			
			if (h <= bestH) {
				bestH = h;
				bestM[0] = xPrime; // if x moves multiple times per act
				bestM[1] = yPrime;
			}
		}

		if (bestM[0] == player.x && bestM[1] == player.y) {
			player.damage(1);
		} else {
			x = bestM[0];
			y = bestM[1];
		}
	}
//};