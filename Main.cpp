
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
    NO_CACHED       =  -1,
    HICARD          =   0,
    ONE_PAIR        =   1,
    TWO_PAIR        =   2,
    THREE_OF_A_KIND =   4,
    STRAIGHT        =   8,
    ROYAL_STRAIGHT  =  16,       //  役ではないが処理の都合で必要。  //
    FLUSH           =  32,
    FULL_HOUSE      =  64,
    FOUR_OF_A_KIND  = 128,
    ROYAL_FLUSH     = 256,
};

PokerHand  checkNumbers(const int &(buckets)[13])
{
}

PokerHand  checkHand(const int (& buf)[NUM_HAND_CARDS])
{
    //  バケットソートを行う。  //
    int buckets[13] = { 0 };
    int suits[4] = { 0, 0, 0, 0 };

    for ( int i = 0; i < NUM_HAND_CARDS; ++ i ) {
        const int   card = buf[i] - 1;
        ++ buckets[card % 13];
        ++ suits  [card / 13];
    }

    PokerHand   phPairs = checkNumbers(buckets);

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
