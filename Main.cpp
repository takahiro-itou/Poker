
#if 0
g++ -o Poker.exe Main.cpp;
exit 0;
#endif

#include    "CombinationGenerator.h"
#include    "PokerHandChecker.h"

#include    <iostream>

constexpr   int     MAX_BUF = 16;

typedef     CombinationGenerator<52, 5>     CardPatternGenerator;
typedef     CardPatternGenerator::Pattern   CardPatternBuffer;



std::ostream  &
showCards(const int buf[], const int R, std::ostream & os)
{
    for ( int i = 0; i < R; ++ i ) {
        os  <<  buf[i]  <<  ",";
    }
    return ( os );
}


int main(int argc, char * argv[])
{
    countHandPatterns<5>(std::cout, std::cerr);
    return ( 0 );
    return ( 0 );
}
