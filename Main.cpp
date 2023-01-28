
#if 0
g++ -o Poker.exe Main.cpp;
exit 0;
#endif

#include    "CombinationGenerator.h"
#include    "PokerHandChecker.h"

#include    <iostream>
#include    <ostream>

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

std::ostream  &
showCounts(const ResultTable &table, std::ostream &os)
{
    os  <<  "\nRoyal Flush     = "  <<  table.counter[ROYAL_FLUSH]
        <<  "\nStraight Flush  = "  <<  table.counter[STRAIGHT | FLUSH]
        <<  "\nFour Of A Kind  = "  <<  table.counter[FOUR_OF_A_KIND]
        <<  "\nFull House      = "  <<  table.counter[FULL_HOUSE]
        <<  "\nFlush           = "  <<  table.counter[FLUSH]
        <<  "\nStraight        = "
        <<  table.counter[STRAIGHT]  + table.counter[ROYAL_STRAIGHT]
        <<  "\nThree Of A Kind = "  <<  table.counter[THREE_OF_A_KIND]
        <<  "\nTwo Pair        = "  <<  table.counter[TWO_PAIR]
        <<  "\nOne Pair        = "  <<  table.counter[ONE_PAIR]
        <<  "\nHi Card         = "  <<  table.counter[HICARD];
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
