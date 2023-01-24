
#if 0
g++ -o Poker.exe Main.cpp;
exit 0;
#endif

#include    "CombinationGenerator.h"

#include    <iostream>
#include    <ostream>

constexpr   int     MAX_BUF = 16;
constexpr   int     NUM_HAND_CARDS  = 5;

typedef     CombinationGenerator<52, 7>     CardPatternGenerator;
typedef     CardPatternGenerator::Pattern   CardPatternBuffer;

enum PokerHand
{
    HICARD          = 0,
    ONE_PAIR        = 1,
    TWO_PAIR        = 2,
    THREE_OF_A_KIND = 4,
    STRAIGHT        = 8,
    FLUSH           = 16,
    FULL_HOUSE      = 32,
    FOUR_OF_A_KIND  = 64,
    ROYAL_FLUSH     = 128,
};

PokerHand  checkHand(const int (& buf)[NUM_HAND_CARDS])
{
    PokerHand   ph;

    return ( ph );
}

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
