#include <iostream>

int main() {
    int rx = 0;
    int ry = 0;
    bool isCharacters[14*38];

    for (int i=0; i<14*38; i++)
        if (rand() % 2 == 1)
            isCharacters[i] = true;

    srand(time(NULL));
    for (int i=0; i<24; i++) {
        if (rand() % i == 0) {
            do {
                rx = rand() % 14;
                ry = rand() % 38;
            } while (isCharacters[rx+ry*38]);
            isCharacters[rx+ry*38] = true;
            std::cout << i << ":" << rx << ", " << ry << std::endl;
        }
        if (rand() % i == 0) {
            do {
                rx = rand() % 14;
                ry = rand() % 38;
            } while (isCharacters[rx+ry*38]);
            isCharacters[rx+ry*38] = true;
            std::cout << i << ":" << rx << ", " << ry << std::endl;
        }
    }


    return 0;
}