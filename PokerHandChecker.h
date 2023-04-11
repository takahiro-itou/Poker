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

#if !defined( POKER_HANDS_PROB_INCLUDED_COMBINATION_GENERATOR_H )
#    include    "generator/CombinationGenerator.h"
#endif

#if !defined( POKER_HANDS_PROB_SYS_INCLUDED_IOMANIP )
#    include    <iomanip>
#    define   POKER_HANDS_PROB_SYS_INCLUDED_IOMANIP
#endif

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

struct BestPokerHand
{
    PokerHand   candHand;       /**<  可能性のある全ての候補。  **/
    PokerHand   bestHand;       /**<  候補の中で最も高い役。    **/
};

struct ResultTable
{
    int counter[512];
};

constexpr   int     NUM_HAND_CARDS  = 5;
constexpr   int     NUM_SUITS       = 4;
constexpr   int     NUM_DISP_DIGIT  = 10;

enum CardNumber {
    ACE     = 0,
    TEN     = 9,
    JACK    = 10,
    QUEEN   = 11,
    KING    = 12,
    MAX_CARD_NUMBER,
};

constexpr   int     NUM_DECK_CARDS  = NUM_SUITS * MAX_CARD_NUMBER;

struct  CacheTable
{
    PokerHand   hands[NUM_DECK_CARDS][NUM_DECK_CARDS][NUM_DECK_CARDS]
                     [NUM_DECK_CARDS][NUM_DECK_CARDS];
};

CacheTable  g_tableCache;

//----------------------------------------------------------------
/**   ペアの判定をする。
**
**/

inline  PokerHand
checkPairs(const int (& buckets)[MAX_CARD_NUMBER])
{
    int  pairs  = 0;
    int  tuple  = 0;
    int  fours  = 0;

    for ( int i = 0; i < MAX_CARD_NUMBER; ++ i ) {
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

    return ( HICARD );
}

//----------------------------------------------------------------
/**   ストレートの判定をする。
**
**/

inline  PokerHand
checkStraight(const int (& buckets)[MAX_CARD_NUMBER])
{
    //  A-K-Q-J-10のストレートを判定。  //
    if ( buckets[ACE] == 1 && buckets[TEN] == 1 && buckets[JACK] == 1
            && buckets[QUEEN] == 1 && buckets[KING] == 1 )
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
    for ( int i = pos + 1; i < pos + NUM_HAND_CARDS; ++ i ) {
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
checkHand(
        const int (& buf)[NUM_HAND_CARDS])
{
    //  バケットソートを行う。  //
    int buckets[MAX_CARD_NUMBER] = { 0 };
    int suits[NUM_SUITS] = { 0, 0, 0, 0 };

    for ( int i = 0; i < NUM_HAND_CARDS; ++ i ) {
        const int   card = buf[i] - 1;
        ++ buckets[card % MAX_CARD_NUMBER];
        ++ suits  [card / MAX_CARD_NUMBER];
    }

    //  ペア系の判定。  //
    PokerHand   phPairs = checkPairs(buckets);
    if ( phPairs != HICARD ) {
        //  ペアができている時はフラッシュの可能性はない。  //
        return ( phPairs );
    }

    //  ストレートの判定。  //
    phPairs = checkStraight(buckets);

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
/**   ポーカーハンドを判定する。
**
**/

inline  PokerHand
checkHandWithCache(
        const int (& buf)[NUM_HAND_CARDS],
        CacheTable * const  pCache)
{
    //  キャッシュにデータがあればそれを返す。  //
    PokerHand * pCacheEntry = nullptr;
    if ( pCache != nullptr ) {
        pCacheEntry = pCache->hands[buf[0]][buf[1]][buf[2]][buf[3]] + buf[4];
        const   PokerHand   cv  = (* pCacheEntry);
        if ( cv != NO_CACHED ) {
            return ( cv );
        }
    }

    //  役の判定を実行して結果を得る。  //
    const   PokerHand   ph  = checkHand(buf);

    //  結果をキャッシュしてから返す。  //
    if ( pCacheEntry != nullptr ) {
        (* pCacheEntry) = ph;
    }
    return ( ph );
}

//----------------------------------------------------------------
/**   指定されたカードの組から最も高いハンドを得る。
**
**/

template <int R>
inline  BestPokerHand
findMaxHand(
        const int (& cardBuf)[R],
        CacheTable * const  pCache)
{
    static_assert(
            NUM_HAND_CARDS <= R,
            "The number of cards is shortage.");
    typedef     CombinationGenerator<R, NUM_HAND_CARDS, 0>  Combination;
    typedef     typename  Combination::Pattern              CombPattern;

    BestPokerHand   phBest  = { HICARD, HICARD };
    int             work[NUM_HAND_CARDS];
    Combination     comb;

    comb.resetGenerator();
    do {
        const  CombPattern &pat = comb.getCurrent();
        for ( int i = 0; i < NUM_HAND_CARDS; ++ i ) {
            work[i] = cardBuf[pat[i]];
        }
        PokerHand   ph  = checkHandWithCache(work, pCache);
        if ( phBest.bestHand < ph ) {
            phBest.bestHand = ph;
        }
        phBest.candHand = static_cast<PokerHand>(phBest.candHand | ph);
    } while ( comb.generateNext() );

    return ( phBest );
}

//----------------------------------------------------------------
/**   キャッシュテーブルを初期化する。
**
**/

inline  void
initializeCacheTable()
{
    for ( int c0 = 0; c0 < NUM_DECK_CARDS; ++ c0 ) {
    for ( int c1 = 0; c1 < NUM_DECK_CARDS; ++ c1 ) {
    for ( int c2 = 0; c2 < NUM_DECK_CARDS; ++ c2 ) {
    for ( int c3 = 0; c3 < NUM_DECK_CARDS; ++ c3 ) {
    for ( int c4 = 0; c4 < NUM_DECK_CARDS; ++ c4 ) {
        g_tableCache.hands[c0][c1][c2][c3][c4] = NO_CACHED;
    }
    }
    }
    }
    }
}

//----------------------------------------------------------------
/**   集計結果テーブルの内容をストリームに出力する。
**
**/

inline  std::ostream  &
showCounts(const ResultTable &table, std::ostream &os)
{
    os  <<  std::right
        <<  "\nRoyal Flush     = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[ROYAL_FLUSH]
        <<  "\nStraight Flush  = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[STRAIGHT | FLUSH]
        <<  "\nFour Of A Kind  = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[FOUR_OF_A_KIND]
        <<  "\nFull House      = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[FULL_HOUSE]
        <<  "\nFlush           = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[FLUSH]
        <<  "\nStraight        = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[STRAIGHT]  + table.counter[ROYAL_STRAIGHT]
        <<  "\nThree Of A Kind = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[THREE_OF_A_KIND]
        <<  "\nTwo Pair        = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[TWO_PAIR]
        <<  "\nOne Pair        = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[ONE_PAIR]
        <<  "\nHi Card         = "  <<  std::setw(NUM_DISP_DIGIT)
        <<  table.counter[HICARD];

    return ( os );
}

//----------------------------------------------------------------
/**   集計結果テーブルの内容をストリームに出力する。
**
**/

inline  std::ostream  &
showDetail(const ResultTable &table, std::ostream &os)
{
    constexpr  int  TABLE_SIZE
            = sizeof(table.counter) / sizeof(table.counter[0]);

    for ( int i = TABLE_SIZE - 1; i >= 1; -- i ) {
        if ( table.counter[i] == 0 ) { continue; }

        os  <<  "0x"    <<  std::setfill('0')   <<  std::hex
            <<  std::setw(4)    <<  i   <<  "\t = "
            <<  std::setfill(' ')   <<  std::dec
            <<  std::setw(NUM_DISP_DIGIT)
            <<  table.counter[i]    <<  "\t";
        if ( i & ROYAL_FLUSH ) {
            os  <<  "RF,";
        }
        if ( i & FOUR_OF_A_KIND ) {
            os  <<  "4K,";
            }
        if ( i & FULL_HOUSE ) {
            os  <<  "FH,";
        }
        if ( i & FLUSH ) {
            os  <<  "FL,";
        }
        if ( i & ROYAL_STRAIGHT ) {
            os  <<  "RS,";
        }
        if ( i & STRAIGHT ) {
            os  <<  "ST,";
        }
        if ( i & THREE_OF_A_KIND ) {
            os  <<  "3K,";
        }
        if ( i & TWO_PAIR ) {
            os  <<  "2P,";
        }
        if ( i & ONE_PAIR ) {
            os  <<  "1P,";
        }
        os  <<  std::endl;
    }

    return ( os );
}

//----------------------------------------------------------------
/**   各ハンドのできる事象数をカウントする。
**
**/

template <int N>
inline  void
countHandPatterns(
        std::ostream & strOut,
        std::ostream & strErr,
        CacheTable   * tblCache = nullptr)
{
    typedef     CombinationGenerator<52, N>     CardPatternGenerator;
    typedef     typename
            CardPatternGenerator::Pattern       CardPatternBuffer;

    CardPatternGenerator    comb;
    ResultTable             results = { 0 };
    ResultTable             retCand = { 0 };

    int counter = 0;
    int numPats = 1;
    for ( int i = 1; i <= N; ++ i ) {
        numPats = numPats * (52 + 1 - i) / i;
    }

    comb.resetGenerator();
    do {
        ++ counter;
        const  CardPatternBuffer  & buf = comb.getCurrent();
        const  BestPokerHand        bph = findMaxHand(buf, tblCache);
        ++ results.counter[bph.bestHand];
        ++ retCand.counter[bph.candHand];
        if ( (counter & 65535) == 0 ) {
            strErr  <<  counter <<  " / "
                    <<  numPats
                    <<  " ("
                    <<  (counter * 100.0 / numPats)
                    <<  " %)\r";
        }
    } while ( comb.generateNext() );

    strErr  <<  counter <<  " / "
            <<  numPats
            <<  " ("
            <<  (counter * 100.0 / numPats)
            <<  " %)\nFinish."  <<  std::endl;
    showCounts(results, strOut) <<  std::endl;
    strOut  <<  "\nDetails\n";
    showDetail(retCand, strOut) <<  std::endl;

    return;
}

#endif
