
#if 0
program='Calc7';
g++  -Wall -Werror --std=c++11  -o ${program}.exe ${program}.cpp;
exit 0;
#endif

#include    "CombinationGenerator.h"
#include    "PokerHandChecker.h"

#include    <iostream>

int main(int argc, char * argv[])
{
    initializeCacheTable();
    countHandPatterns<7>(std::cout, std::cerr, &g_tableCache);
    return ( 0 );
}
