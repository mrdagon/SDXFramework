﻿/*!
@page QandA Ｑ＆Ａ
  よくある質問
  準備中
 <HR>
\n
 Ｑ.関数の使い方はどうやって調べるの？\n
\n
 Ａ.\n
 リファレンスやサンプルコードを読んでください。\n
\n
 #include "Sample/Sample.h" でヘッダを読み込んで\n
 Sample～で始まる関数を呼び出すとサンプルコードを実行する事も出来ます。\n
<HR>
\n
Ｑ.SDL版とDXLIB版はどう違うの？\n
\n
Ａ.\n
DXLIB版の特徴\n
Windowsのみで動作\n
実装済みの機能はDXLIB版の方が豊富\n
SDL版ではZマスク、画像フィルター処理、リソースの別スレッドでの読み込み、動画等の機能が非実装\n
文字の描画の仕様が違うのでSDLより早いが、読み込みは遅く、メモリを多く使う\n
\n
3D機能を追加する場合、DXLIB版はDXライブラリのラッパーをする事になるので比較的楽ですが\n
SDL版はOpenGLとSDLを理解する必要があり、3Dモデルファイルのフォーマットやモーションや当たり判定等は色々面倒です\n
\n
SDL版の特徴\n
Win、Mac、Linux、Android、iOSで動作\n
フルスクリーンの切り替え速度はDXLIBより良く、アプリケーションの起動が早い\n
Joypad絡みで不具合がある？\n
ライセンス表記が不要\n
\n
大体こんな感じです、実行速度の違い等は調べていませんが、どちらかがすごく早かったり遅かったりという事はないようです\n
<HR>
Ｑ.未実装機能とは？\n
\n
Ａ.\n
    クラスの詳細か関数の説明の後に\n
    [未実装]とある場合は未実装です\n
    [DXLIB]とある場合、DXLIB専用です\n
    [SDL]とある場合はSDL専用です
\n
<HR>
Ｑ.SDL版の図形描画機能が貧弱だし、動画も扱えなくて不便、ネットワークや3D機能はなんで実装しないの？\n
\n
Ａ.\n
    大原則として、ライブラリ開発者自身がゲーム開発に必要な機能を優先して開発する方針があります。\n
    SDLの複数ウィンドウとか、動画とか、ネットワークとか、図形描画諸々は必要としている開発者がいないため実装されません。\n
    特定の色を透過色に指定する機能も透過pngを使ったほうが確実なので、実装していません。\n
<HR>
\n
Ｑ.なんで引数だけ日本語でクラス名とかは英語なの、ルー語？\n
\n
Ａ.\n
普段日本語で思考しているので、日本語の方がライブラリが使いやすく開発が楽だからです。\n
というかわざわざ全部の識別子を英語にする理由がありません。\n
\n
仮引数だけの理由は、android-ndkの対応状況を考慮したのと、\n
万一利用者が増えたから英訳しようとか思った場合も、仮引数だけならそこまで手間ではないからです\n
<HR>
\n
Ｑ.何故管理がGithubとSorceForgeに分かれているんですか？\n
\n
Ａ.\n
Github専用のリポジトリ管理ソフトが使いやすいので、ソースはGithubで管理しています。\n
安定版をSorceForgeに置いているのは、Githubより検索にかかる可能性が高いのと、規約上13歳以下でも問題ないのと\n
バイナリの配布が楽なのと、UIが日本語だからです。\n
<HR>
\n
 Ｑ．分からない事があったら、どうすればよいですか？\n
\n
 Ａ．\n
 掲示板で「新しい話題を始める」をクリックして質問して下さい。\n
 <a href="http://sourceforge.jp/projects/dxframework/forums/31378/" target="_blank"><B>SDXフレームワーク：ヘルプフォーラム</B></a>\n
 一応書き込んだら作者にメールが行くのでそれなりの早さで反応します。\n
 \n
 作者のtwitterや、メールアドレス、ブログ等で質問されると確認が手間なのと情報を一元管理して共有しにくいので、\n
出来るだけ、掲示板を利用して下さい。(twitterはbotなので、殆どチェックしません)\n
 <HR>
*/