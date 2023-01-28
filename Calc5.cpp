
#if 0
program='Calc5';
g++  -Wall -Werror --std=c++11  -o ${program}.exe ${program}.cpp;
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
