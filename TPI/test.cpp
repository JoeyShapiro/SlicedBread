#include <iostream>
#include <vector>
#include <string>
#include <queue>



int main() {
    std::cout << "hello\n";
    srand(time(0));
    double dam = 10;

    if (rand() % 100 <= 75) // smart smart (((rand() % (acc/100)) + 1) != acc), even smarter, knew way, i smert
        std::cout << "miss\n";

    // "== 50" is 1/50, "<= 50" 50/100
    if (rand() % 100 <= 50) // critC/100 is crit%, but recip(critC) should also give higher chance with higher number
        dam *= 1.5;

    std::cout << rand() % 1 << std::endl;
    std::cout << rand() % 1 << std::endl;
    std::cout << rand() % 1 << std::endl;
    std::cout << rand() % 1 << std::endl;
    std::cout << rand() % 1 << std::endl;
    std::cout << dam << std::endl;

    return 0;
}