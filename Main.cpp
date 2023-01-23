
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
    CombinationGenerator<52, 7> comb;

    int counter = 0;
    int buf[MAX_BUF];

    int total = 133784560;
    comb.resetGenerator();
    do {
        ++ counter;
        comb.getCurrent(buf);

#if 0
        std::cout   <<  counter
                    <<  "\t";
        showCards(buf, 2, std::cout)    <<  std::endl;
#endif
        if ( (counter & 65535) == 0 ) {
            std::cerr   <<  counter <<  " / "
                        <<  total
                        <<  " ("
                        <<  (counter * 100.0 / total)
                        <<  " %)\r";
        }
    } while ( comb.generateNext() );

    std::cerr   <<  counter
                <<  "\nFinish."   <<  std::endl;

    return ( 0 );
}
