﻿/*!
@page QandA Ｑ＆Ａ
  よくありそうな質問
 <HR>
\n
 Ｑ.何故緩いライセンスではなくAGPL ver3なの？\n
\n
 Ａ.\n
 最大の理由は利用者同士がお互いにコードを共有した方が、開発者とユーザーの利益になるとの結論に至ったからです.\n
詳しくはSDXとは?を読んで下さい.\n
AGPLなのはWebGLに対応する可能性があるからです\n
<HR>
　Ｑ.旧バージョンはzlibだけどこれはどうなるの？\n
 \n
 Ａ.\n
 以前に公開していたバージョンのライセンスを変更する事は出来ないので、\n
旧バージョンはzlibライセンスで利用する事が出来ます。\n
 \n
<HR>
　Ｑ.ライセンスが英語なのでよくわからないです、違反したらどうなるの？\n
\n
 Ａ.\n
非公式ですが、こちらが参考になると思います\n
http://www.ipa.go.jp/osc/osslegal.html#GNUGPL1
\n
 このライブラリを作ったゲームを配布する場合プログラムのライセンスをAGPL ver3にする必要があります、\n
画像や音声、シナリオ、外部スクリプト等の外部ファイルのライセンスはAGPL ver3にする必要はありません。\n
\n
 コードについては\n
①誰でもダウンロード出来る形で公開する\n
②プログラムと一緒に配布する\n
③問い合わせ先を明記して要求があればコードを送る\n
のように何らかの手段で入手可能にする必要があります\n
\n
<HR>
 Ｑ.ライセンス違反したらどうなるの？\n
 \n
 ライセンス違反を発見した場合、まず是正を要求します。即訴訟とかは余程悪質でない限りしません。\n
ただ違反は好ましくありませんので、疑問があればフォーラムで質問して下さい。\n
\n
<HR>
Ｑ.何故Appstoreで配布出来ないの？\n
このような事情です。年齢制限等は緩和されましたが他はあまり変わっていません。\n
http://sourceforge.jp/magazine/08/04/17/0141213
\n
 いわゆる脱獄アプリとして配布する事は可能ですが、メーカー保障が切れる行為を推奨はしません。\n
<HR>
 Ｑ.関数の使い方はどうやって調べるの？\n
\n
 Ａ.\n
 リファレンスやサンプルコードを読んでください。\n
\n
 #include "Sample/Sample.h" でヘッダを読み込んで\n
 Sample～で始まる関数を呼び出すとサンプルコードを実行する事も出来ます。\n
<HR>
Ｑ.未実装機能とは？\n
\n
Ａ.\n
 クラスの詳細か関数の説明の後に\n
 [未実装]とある場合は未実装です\n
 今後実装しない可能性もありますが、出来たら実装したい機能です.\n
<HR>
Ｑ.図形描画機能が貧弱だし、動画も扱えなくて不便、ネットワークや3D機能はなんで実装しないの？\n
\n
Ａ.\n
原則として、コミッタがゲーム開発に必要としている機能を優先して開発する方針があります。\n
そうでないとレビューが困難になるからです。\n
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
仮引数やローカル変数だけの理由は、android-ndkの対応状況を考慮したのと、\n
利用者が増えたので英訳してSDL公式に取り込んで貰おうとかなった場合も、仮引数だけなら翻訳が楽だからです\n
<HR>
\n
Ｑ.何故管理がGithubとSorceForgeに分かれているんですか？\n
\n
Ａ.\n
Github専用のリポジトリ管理ソフトが使いやすいので、ソースはGithubで管理しています。\n
安定版をSorceForgeに置いているのは、Githubより検索にかかる可能性が高いのと、バイナリの配布が楽だからです。\n
<HR>
Ｑ.SDXの意味は？\n
\n
Ａ.\n
 SDの部分はSDL、DXの部分はDXLibから取っています。\n
元々はDXLibのラッパーとして開発していたのを途中で内部実装をSDLに変更したので、現在DXLibは使っていません。\n
しかしながら機能分割の粒度や関数の命名等でDXLibを参考にしているので、敬意を表明して名称に残しています\n
<HR>
Ｑ.何故DXLIB版のサポートを辞めたの？\n
\n
Ａ.\n
機能はDXLibの方がSDLより豊富ですが、プラットフォーム対応の差でSDLに注力した方が良いと判断したからです\n
<HR>
Ｑ.SDL2.0の参考サイトとかありますか？\n
\n
Ａ.\n
自分は実装後に見つけたのでしっかり読んでいませんが、\n
こちらや\n
http://lazyfoo.net/tutorials/SDL/index.php
\n
ドキュメント日本語訳のプロジェクトが参考になると思います\n
https://sourceforge.jp/projects/sdl2referencejp/
\n
<HR>
 Ｑ．分からない事があったら、どうすればよいですか？\n
\n
 Ａ．\n
 掲示板で「新しい話題を始める」をクリックして質問して下さい。\n
 <a href="http://sourceforge.jp/projects/dxframework/forums/31378/" target="_blank"><B>SDXFramework：ヘルプフォーラム</B></a>\n
 一応書き込んだら作者にメールが行くのでそれなりの早さで反応します。\n
 \n
 作者のtwitterや、メール、ブログ等で質問されると確認が手間なのと情報を一元管理して共有しにくいので、\n
出来るだけ、掲示板を利用して下さい。(twitterはbotなので、殆どチェックしません)\n
 <HR>
*/