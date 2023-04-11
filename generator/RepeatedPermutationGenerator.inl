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
**      An Implementation of RepeatedPermutationGenerator class.
**
**      @file       RepeatedPermutationGenerator.inl
**/

#if !defined( POKER_HANDS_PROB_INCLUDED_REPEATED_PERMUTATION_GENERATOR_INL )
#    define   POKER_HANDS_PROB_INCLUDED_REPEATED_PERMUTATION_GENERATOR_INL

#if !defined( POKER_HANDS_PROB_INCLUDED_REPEATED_PERMUTATION_GENERATOR_H )
#    include    "RepeatedPermutationGenerator.h"
#endif

//========================================================================
//
//    RepeatedPermutationGenerator  class.
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
RepeatedPermutationGenerator<N, R, FIRST>::RepeatedPermutationGenerator()
    : m_buf()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

template <int N, int R, int FIRST>
RepeatedPermutationGenerator<N, R, FIRST>::~RepeatedPermutationGenerator()
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
RepeatedPermutationGenerator<N, R, FIRST>::resetGenerator()
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
RepeatedPermutationGenerator<N, R, FIRST>::generateNext()
{
    return ( false );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在のパターンをコピーする。
//

template <int N, int R, int FIRST>
template <int K>
inline  void
RepeatedPermutationGenerator<N, R, FIRST>::getCurrent(int (& buf)[K])  const
{
    static_assert(R <= K, "The size of buffer is too small.");
    for ( int i = 0; i < R; ++ i ) {
        buf[i]  = this->m_buf[i];
    }
}

//----------------------------------------------------------------
//    現在のパターンを取得する。
//

template <int N, int R, int FIRST>
inline  const
typename  RepeatedPermutationGenerator<N, R, FIRST>::Pattern  &
RepeatedPermutationGenerator<N, R, FIRST>::getCurrent()  const
{
    return ( this->m_buf );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

#endif
