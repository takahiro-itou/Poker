
#if 0
g++ -o Poker.exe Main.cpp;
exit 0;
#endif

#include    "CombinationGenerator.h"

#include    <iostream>
#include    <ostream>

constexpr   int     MAX_BUF = 16;

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
    CombinationGenerator<6, 2>  comb;

    int counter = 0;
    int buf[MAX_BUF];

    comb.resetGenerator();
    do {
        ++ counter;
        comb.getCurrent(buf);

        std::cout   <<  counter
                    <<  "\t";
        showCards(buf, 2, std::cout)    <<  std::endl;
        if ( counter >= 32 ) {
            break;
        }
    } while ( comb.generateNext() );

    return ( 0 );
}
