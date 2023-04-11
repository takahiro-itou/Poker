# generator

##  イントロダクション

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

これを以下のように書き換えられるようにする。

```
Generator gen(52, 5);

gen.resetGenerator();
do {
    const Generator::Pattern & pattern = gen.getCurrent();
    doSomething(pattern);
} while ( gen.generateNext() );
```
