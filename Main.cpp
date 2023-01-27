
#if 0
g++ -o Poker.exe Main.cpp;
exit 0;
#endif

#include    "CombinationGenerator.h"

#include    <iostream>
#include    <ostream>

constexpr   int     MAX_BUF = 16;
constexpr   int     NUM_HAND_CARDS  = 5;

typedef     CombinationGenerator<52, 5>     CardPatternGenerator;
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

struct ResultTable
{
    int counter[512];
};

PokerHand  checkNumbers(const int (& buckets)[13])
{
    int  pairs  = 0;
    int  tuple  = 0;
    int  fours  = 0;

    for ( int i = 0; i < 13; ++ i ) {
        switch ( buckets[i] ) {
        case  2:
            ++ pairs;
            break;
        case  3:
            ++ tuple;
            break;
        case  4:
            ++  fours;
            break;
        }
    }

    if ( fours ) {
        return ( FOUR_OF_A_KIND );
    }
    if ( tuple == 1 && pairs == 1 ) {
        return ( FULL_HOUSE );
    }
    if ( tuple ) {
        return ( THREE_OF_A_KIND );
    }
    if ( pairs == 2 ) {
        return ( TWO_PAIR );
    }
    if ( pairs == 1 ) {
        return ( ONE_PAIR );
    }

    //  A-K-Q-J-10のストレートを判定。  //
    if ( buckets[0] == 1 && buckets[9] == 1 && buckets[10] == 1
            && buckets[11] == 1 && buckets[12] == 1 )
    {
        return ( ROYAL_STRAIGHT );
    }
    //  上記以外のストレートを判定。    //
    int pos = 0;
    for ( int i = 0; i < 9; ++ i ) {
        if ( buckets[i] ) {
            pos = i;
            break;
        }
    }
    for ( int i = pos + 1; i <= pos + 4; ++ i ) {
        if ( buckets[i] == 0 ) {
            return ( HICARD );
        }
    }
    return ( STRAIGHT );
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

    return ( phPairs );
}

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
