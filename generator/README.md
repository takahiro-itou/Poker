# Pattern Generator

##  Abstract.

このプログラムでは 52 枚のカードの中から 5～7 枚を選ぶ組み合わせを
全て列挙し、その各パターンに対して何らかの判定処理を行う。
このディレクトリにあるモジュールは、
組み合わせの全パターンを列挙するアルゴリズムを実装する。

##  Introduction.

もっとも単純だが良くない実装としては、
以下のプログラムの様に多重ループで実装する方法がある
（オリジナルは VB6 だが C 言語で書き直した）。

https://gitlab.com/takahiro-itou-vb6backup/Poker/-/blob/master/Tables.bas#L200

```
for (c0 = 0; c0 <= 47; ++ c0) {
  for (c1 = c0 + 1; c1 <= 48; ++ c1) {
    for (c2 = c1 + 1; c2 <= 49; ++ c2) {
       for (c3 = c2 + 1; c3 <= 50; ++ c3) {
         for (c4 = c3 + 1; c4 <= 51; ++ c4) {
            doSomething(c0, c1, c2, c3, c4);
         }
      }
    }
  }
}
```

このコードは 52 枚中 5 枚選ぶロジックだが、
これでは 52 枚中 6 枚とか 6 枚に変更しようとすると、
コードの大幅な変更を余儀なくされる。
これを以下のように書き換えられるようにする。

```
Generator gen(52, 5);

gen.resetGenerator();
do {
    const Generator::Pattern & pattern = gen.getCurrent();
    doSomething(pattern);
} while ( gen.generateNext() );
```
