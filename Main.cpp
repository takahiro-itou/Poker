
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
    CardPatternGenerator    comb;
    ResultTable             results = { 0 };

    int counter = 0;
    int total = 133784560;
    comb.resetGenerator();
    do {
        ++ counter;
        const  CardPatternBuffer  & buf = comb.getCurrent();

#if 0
        std::cout   <<  counter
                    <<  "\t";
        showCards(buf, 2, std::cout)    <<  std::endl;
#endif
        const   PokerHand   ph  = checkHand(buf);
        ++  results.counter[ph];
        if ( (counter & 65535) == 0 ) {
            std::cerr   <<  counter <<  " / "
                        <<  total
                        <<  " ("
                        <<  (counter * 100.0 / total)
                        <<  " %)\r";
        }
    } while ( comb.generateNext() );

    std::cerr   <<  counter
                <<  "\nFinish."     <<  std::endl;
    showCounts(results, std::cout)  <<  std::endl;

    return ( 0 );
}
