# ”実行にはDirectXのインストールが必要です”

### プロジェクトのファイル構成の関係でコードをファイルにまとめることが出来ませんでした。申し訳ありません。

## 操作<br>
移動：WASD<br>
ジャンプ、回避：Space<br>
ダッシュ：Shiftを押しながら移動<br>
攻撃：左クリック<br>
武器切り替え：E<br>
リロード：R<br>


## 工夫した点<br>
操作していて面白い、と思えるようにプレイヤーの動きにこだわりました。<br>
敵を攻撃していて楽しい、と感じるようにヒットストップやエフェクトなどにこだわりました。<br>
同じ３Dモデル、テクスチャを何度も呼び出しているので、この２つを一括管理するクラスを作成しました。<br>
このクラスでは、勉強を兼ねて３Dモデルをstd::listで、テクスチャをstd::mapで管理しています。ファイル名をキーとして３Dモデル、テクスチャにアクセスした際に現在の配列内に同じ物があるか探索し、見つかった場合はそのポインタを、見つからなかった場合は新しくロードし、配列に格納したのちポインタを返す仕組みになっています。<br>
プレイヤーと敵はステートマシンで制御しています。<br>
敵の動きはプレイヤーに向かって直進するだけでは敵同士が同じ動きになってしまうので、移動方向、移動時間にランダム性を与え同じ敵でも異なる方向に移動し重なり合うのを防ぎました。<br>
地面はシェーダーを使い、３つのテクスチャとRGB値によってテクスチャをブレンドし、道を引けるようにしました。<br>
その他に、水たまりもシェーダーを使い、波の法線テクスチャを同一方向に動かすことで水の表現をしました。<br>
ゲームとして面白く遊べるようサウンドやエフェクトを各場面で出すことで手触り感が良くなるよう工夫しました。<br>
プレイヤーのジャンプ、回避時に鳴るサウンドは２種類の音源をランダムで鳴らすことで連続でアクションした際に違和感を軽減しています。

