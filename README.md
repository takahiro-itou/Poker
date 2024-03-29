# Poker 確率計算

- ポーカーハンドの成立する確率を計算する

##  用語

###   テキサス・ホールデム

- ポーカーのルールの一種
- 各プレーヤーに配られる二枚のカードと、
場に配られる全プレーヤーに共通のカード（コミュニティ・カードと言う、最大五枚）
の中から五枚を選び役（ポーカーハンド）を作り競う。

####   フロップ

- 各プレーヤーに二枚のカードを配る
- 場に三枚のカードを表向きに配る
    - これを、コミュニティ・カードといい、全プレーヤーで共有。
- この状態を「フロップ」と呼ぶ。
- この時点で、手札と場札の五枚でハンドができる場合を計算する。

####  ターン

- フロップの後、ディーラーはさらに１枚のコミュニティ・カードを場に公開する。
- この状態を「ターン」と呼ぶ。
- 手札と場札の六枚から五枚を選びハンドを作る。
- 選び方によって異なるハンドができる場合は高い方を選択する。

####  リバー

- ターンのあと、ディーラーは最後のコミュニティ・カードを場に公開する。
- この状態を「リバー」と呼ぶ。
- 手札と場札の七枚から五枚を選びハンドを作る。
- 選び方によって異なるハンドができる場合は最も高いハンドを採用する。

####  ショーダウン

- プレーヤーの手札二枚と場にでたコミュニティカードの中から、
最も強い五枚の組み合わせを用いて、ハンドの強さを競う。
- 手札二枚は、両方使っても、片方だけ使っても、全く使わなくても構わないとする。

##  アルゴリズム

###   カードの組み合わせの処理

- カード 52 枚には 0～51 の連番を振っておく。
- カードを配る処理は 0～51 の中から r 個の数字を選ぶ組み合わせとして扱う。
    - この処理は generator/ ディレクトリのモジュールが担当する。

###   最高ハンドの判定

- 仮の最高ハンド max_hand を最も弱いハンドに設定する。
- 配られた r 枚の中から 5 枚を選ぶ組み合わせすべて (この処理は generator/ が再び使える) に対して、
    - その 5 枚でできるハンド h を考える。
    - そのハンドが　max_hand より強ければ max_hand を h で上書きする。

最後の処理を簡単にするため、プログラム中では原則、
強いほうのハンドに、より大きな値をとるように定数（列挙型定数）の値を宣言する。

##  ポーカーハンド一覧

|    ポーカーハンド    |      定数名      | 定数値 |                            説明                            |
|:---------------------|:-----------------|-------:|:-----------------------------------------------------------|
| ロイヤルフラッシュ   | ROYAL_FLUSH      |    256 | A-K-Q-J-10 のストレートフラッシュ                          |
| ストレートフラッシュ | STRAIGHT + FLUSH |     40 | ストレートかつ、同一スート                                 |
| フォーオブアカインド | FOUR_OF_A_KIND   |    128 | 同じ数字のカードを 4 枚。フォーカードとも。                |
| フルハウス           | FULL_HOUSE       |     64 | 同じ数字の 2 枚組と 3 枚組。                               |
| フラッシュ           | FLUSH            |     32 | 同一のスートのカード 5 枚で構成。                          |
| 役ではない           | ROYAL_STRAIGHT   |     16 | 役ではないが処理の都合で必要。A-10 のストレート            |
| ストレート           | STRAIGHT         |      8 | 数字が連続した 5 枚のカード。 2-A-K を含むものは認めない。 |
| スリーオブアカインド | THREE_OF_A_KIND  |      4 | 同じ数字のカード 3 枚組 (とバラ 2 枚)                      |
| ツーペア             | TWO_PAIR         |      2 | 同じ数字のペアが二組 (と残り 1 枚)。                       |
| ワンペア             | ONE_PAIR         |      1 | 同じ数字のペアが一組 (とバラ 3 枚)。                       |
| ハイカード           | HICARD           |      0 | どのハンドも成立しない時。個々のカードを強い順に比較。     |

備考：
ストレートフラッシュの値が低いが、配られるカードが 7 枚以下であれば、
ストレートが成立している時、(ほかのカードとの）組み合わせを変えることで作れる可能性のあるペア系のハンドは、
ワンペア、ツーペア、スリーオブアカインドのみである。

実際 7 枚 5 枚のカードの数字を abcde とすると、これらは相異なる。
残り 2 枚の数字が
- a a -> aaa b c でスリーオブアカインド
- a b -> aa bb c でツーペア
- a x -> aa b c d でワンペア

である。もし、
フルハウスができるためには、このどれかと一致する数字が 1 枚と、別のどれかと一致する数字が 2 枚必要。
フォーオブアカインドができるためには、このどれかと一致する数字があと 3 枚必要。
従って 7 枚中使わなかった残り 2 枚とどのように組み合わせても、この二つハンドは成立しない。

よって、ストレートフラッシュの 40 を、フルハウスやフォーオブアカインドで上書きされる心配はない。
