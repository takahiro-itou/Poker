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
**      An Implementation of CombinationGenerator class.
**
**      @file       CombinationGenerator.inl
**/

#if !defined( POKER_HANDS_PROB_INCLUDED_COMBINATION_GENERATOR_INL )
#    define   POKER_HANDS_PROB_INCLUDED_COMBINATION_GENERATOR_INL

#if !defined( POKER_HANDS_PROB_INCLUDED_COMBINATION_GENERATOR_H )
#    include    "CombinationGenerator.h"
#endif

//========================================================================
//
//    CombinationGenerator  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

template <int N, int R, int FIRST>
CombinationGenerator<N, R, FIRST>::CombinationGenerator()
    : m_buf()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

template <int N, int R, int FIRST>
CombinationGenerator<N, R, FIRST>::~CombinationGenerator()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    内部状態をリセットして最初のパターンに戻す。
//

template <int N, int R, int FIRST>
inline  void
CombinationGenerator<N, R, FIRST>::resetGenerator()
{
    for ( int i = 0; i < R; ++ i ) {
        this->m_buf[i]  = FIRST + i;
    }
}

//----------------------------------------------------------------
//    内部状態を更新して次のパターンを生成する。
//

template <int N, int R, int FIRST>
inline  bool
CombinationGenerator<N, R, FIRST>::generateNext()
{
    int pos;
    for ( pos = R; pos >= 1; -- pos ) {
        const  int  endVal  = (FIRST + N) - (R - pos);
        if ( (++ this->m_buf[pos - 1]) < endVal ) {
            break;
        }
    }

    if ( pos == 0 ) {
        return ( false );
    }

    for ( int i = pos; i < R; ++ i ) {
        this->m_buf[i]  = this->m_buf[i - 1] + 1;
    }

    return ( true );
}

//----------------------------------------------------------------
//    現在のパターンをコピーする。
//

template <int N, int R, int FIRST>
template <int K>
inline  void
CombinationGenerator<N, R, FIRST>::getCurrent(int (& buf)[K])
{
    static_assert(R <= K, "The size of buffer is too small.");
    for ( int i = 0; i < R; ++ i ) {
        buf[i]  = this->m_buf[i];
    }
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

#endif
