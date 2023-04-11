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
**      An Interface of RepeatedPermutationGenerator class.
**
**      @file       RepeatedPermutationGenerator.h
**/

#if !defined( POKER_HANDS_PROB_INCLUDED_REPEATED_PERMUTATION_GENERATOR_H )
#    define   POKER_HANDS_PROB_INCLUDED_REPEATED_PERMUTATION_GENERATOR_H

//  クラスの前方宣言。  //

//========================================================================
//
//    RepeatedPermutationGenerator  class.
//
/**
**    順列を生成するクラス。
**/

template <int N, int R, int FIRST=1>
class  RepeatedPermutationGenerator
{
//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     int     Pattern[R];

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    RepeatedPermutationGenerator();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~RepeatedPermutationGenerator();

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
public:

    //----------------------------------------------------------------
    /**   内部状態をリセットして最初のパターンに戻す。
    **
    **  @return     void.
    **/
    void
    resetGenerator();

    //----------------------------------------------------------------
    /**   内部状態を更新して次のパターンを生成する。
    **
    **  @retval     true    次のパターンが存在する。
    **  @retval     false   現在のパターンが最後。
    **/
    bool
    generateNext();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在のパターンをコピーする。
    **
    **  @param[out] buf     結果を格納する変数。
    **/
    template <int K>
    void
    getCurrent(int  (& buf)[K])  const;

    //----------------------------------------------------------------
    /**   現在のパターンを取得する。
    **
    **/
    const   Pattern  &
    getCurrent()  const;

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   現在のパターン。  **/
    int     m_buf[R];

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   RepeatedPermutationGeneratorTest;
};

//  Implementation.
#include    "RepeatedPermutationGenerator.inl"

#endif
