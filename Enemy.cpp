#include "Enemy.h"
#include "common.h" // maybe have it return string instead
#include "string"

//class Enemy : public Being {
	//public:
    Enemy::Enemy() {
		skin = 'e';
		dossier.health = 10;
		dossier.ap = 1;
		dossier.phys = 15;
		dossier.critC = 10;
		dossier.critM = 1.5;
		dossier.defC = 5;
		dossier.def = 5;
		dossier.acc = 75;
		dossier.armor = 10;
	}

	void Enemy::act(Player& player, bool isCharacter[], int col) { // 2d in c++ is weird, must be Player& to pass object and not create a tmp o?
		int possibleMoves[5][2] = {{x+1,y}, {x-1,y}, {x,y+1}, {x,y-1}, {x, y}}; // TODO should they be like king or can player do that
		int legalMoves[5][2] = {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1, -1}};
		// get all legal moves
		for (int i=0; i<5; i++) {
			int tmpx = possibleMoves[i][0];
			int tmpy = possibleMoves[i][1];
			if (!isCharacter[(tmpy-1) + (tmpx-1) * 39]) {
				legalMoves[i][0] = tmpx;
				legalMoves[i][1] = tmpy;
			}
		}
		double bestH = 1000; // INFINITY doesnt work ?
		int bestM[2] = {x, y};

		for (int i=0; i<5; i++) {
			if (legalMoves[i][0] == -1)
				continue;
			int xPrime = legalMoves[i][0];
			int yPrime = legalMoves[i][1];
			//int h = abs(xPrime - player.x) + abs(yPrime - player.y); // manhattan
			double h = sqrt(((xPrime - player.x)*(xPrime - player.x)) + ((yPrime - player.y)*(yPrime - player.y))); // euclidean (EFFICIENCY)
			
			if (h <= bestH) {
				bestH = h;
				bestM[0] = xPrime; // if x moves multiple times per act
				bestM[1] = yPrime;
			}
		}

		// abs(bestM[0] - player.x) + abs(bestM[1] - player.y) == 0 // still doesnt work, just "juggles" instead
		if (bestM[0] == player.x && bestM[1] == player.y) {
			int dam = calcDamage();
			player.damage(dam);
			std::string log = "e: attacked @ for " + std::to_string(dam); // cant use format string :(
			enLog(logs, log);
		} else {
			x = bestM[0];
			y = bestM[1];
		}
	}
//};