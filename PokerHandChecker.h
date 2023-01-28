//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Poker Hands Probability.  ---                  **
**                                                                      **
**          Copyright (C), 2023,      Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**
**
**      @file       PokerHandChecker.h
**/

#if !defined( POKER_HANDS_PROB_INCLUDED_POKER_HAND_CHECKER_H )
#    define   POKER_HANDS_PROB_INCLUDED_POKER_HAND_CHECKER_H

#if !defined( POKER_HANDS_PROB_SYS_INCLUDED_OSTREAM )
#    include    <ostream>
#    define   POKER_HANDS_PROB_SYS_INCLUDED_OSTREAM
#endif

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

constexpr   int     NUM_HAND_CARDS  = 5;

//----------------------------------------------------------------
/**   ペア系とストレートの判定をする。
**
**/

inline  PokerHand
checkNumbers(const int (& buckets)[13])
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

//----------------------------------------------------------------
/**   ポーカーハンドを判定する。
**
**/

inline  PokerHand
checkHand(const int (& buf)[NUM_HAND_CARDS])
{
    //  バケットソートを行う。  //
    int buckets[13] = { 0 };
    int suits[4] = { 0, 0, 0, 0 };

    for ( int i = 0; i < NUM_HAND_CARDS; ++ i ) {
        const int   card = buf[i] - 1;
        ++ buckets[card % 13];
        ++ suits  [card / 13];
    }

    //  ペア及びストレートの判定。  //
    PokerHand   phPairs = checkNumbers(buckets);
    if ( (phPairs != STRAIGHT) && (phPairs != ROYAL_STRAIGHT)
            && (phPairs != HICARD) )
    {
        //  ペアができている時はフラッシュの可能性はない。  //
        return ( phPairs );
    }

    if ( suits[0] == 5 || suits[1] == 5 || suits[2] == 5 || suits[3] == 5 )
    {
        if ( phPairs & ROYAL_STRAIGHT ) {
            return ( ROYAL_FLUSH );
        }
        return ( static_cast<PokerHand>(phPairs | FLUSH) );
    }

    return ( phPairs );
}

//----------------------------------------------------------------
/**   集計結果テーブルの内容をストリームに出力する。
**
**/

inline  std::ostream  &
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

#endif
