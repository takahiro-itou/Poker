
#if 0
g++ -o Poker.exe Main.cpp;
exit 0;
#endif

#include    "CombinationGenerator.h"
#include    "PokerHandChecker.h"

#include    <iostream>

int main(int argc, char * argv[])
{
    countHandPatterns<5>(std::cout, std::cerr);
    return ( 0 );
}
