﻿/*!
@page QandA Ｑ＆Ａ
よくありそうな質問
<HR>
\n
Ｑ.何故緩いライセンスではなくAGPLver3なの？\n
\n
Ａ.\n
　最大の理由は利用者同士がお互いにコードを共有した方が、開発者とユーザーの利益になると思うからです.\n
詳しくはSDXとは?を読んで下さい.\n
　AGPLなのはWebGLに対応したくなった時に困りそうだからです.\n
<HR>
Ｑ.どういう人向け？\n
\n
Ａ.\n
　デスクトップ環境中心の2Dゲームを作っており、Androidでも動くとなお良く、日本語ドキュメントがあるライブラリが必要で、AGPLでも構わない人向けです。\n
SDLをC++と組み合わせて使おうと思ったけど面倒そうに思えた人にはお勧め出来ます。\n
\n
　利用者が増えれば簡単にコードを入手可能になるメリットが生まれるのですが、現状では利用者数は伸びておらず、改変したいゲームが当ライブラリを利用している場合もそんなに無いと思います。\n
あとは3D機能、広告機能、SNS機能、動画機能、物理演算等が欲しい場合は他の開発環境使った方が楽な事があると思います。\n
\n
<HR>
Ｑ.ライセンスが英語なのでよくわからないです\n
\n
Ａ.\n
　非公式ですが、こちらが参考になると思います\n
http://www.ipa.go.jp/osc/osslegal.html#GNUGPL1
\n
ライセンスについてはこちら。\n
@ref LicenseInfo\n
このライブラリを使ったソフトウェアを配布する場合ソースコードを入手可能にしライセンスをAGPLver3にする必要があります、\n
画像や音声、シナリオ、スクリプト等の外部ファイルのライセンスはAGPLver3にする必要はありません。\n
\n
入手可能であれば良いので\n
①誰でもダウンロード出来る形でGithub等で公開する\n
②プログラムと一緒に配布する\n
③問い合わせ先を明記して要求があればコードを送る\n
のように手段は問いません\n
\n
　あと著作権表記を忘れずに行って下さい。\n
\n
<HR>
Ｑ.不注意や勘違い、あるいは故意にライセンス違反したらどうなるの？\n
\n
Ａ.\n
　ライセンス違反を発見した場合、是正を要求すると思いますが、訴訟とかは余程の事が無いとあり得ません。\n
ただ何にせよライセンス違反は好ましくありませんので、疑問があればフォーラムで質問するなりして下さい。\n
\n
<HR>
Ｑ.SDXのコードを読んでアルゴリズムや設計を勉強した後、一から似たようなコードを描いた場合AGPLで公開する必要はありますか？\n
SDXの実装を参考にしてSDL2.0を使ったソフトを作り非GPL配るとかはOK？\n
\n
Ａ.\n
　アルゴリズムや設計、デザインパターン等は著作権で保護されないので、GPLのコードを読んでプログラミングを勉強したからといってGPLで公開する必要はありません。\n
コードを読んで記憶を頼りにほぼ同じソフトを作るとか、コードを横に並べて変数名やら細部を微妙に変えたコードに書き直すとかする場合はGPLにする必要があると思います。\n
実装の参考にするとかの場合、どれだけ参考にするかで変わってくると思うので何とも言えません。\n
\n
<HR>
Ｑ.破壊的変更って何？\n
\n
Ａ.\n
　ライブラリ利用者が新しいVerに上げた時、今までのコードにエラーが出たり挙動が変わったりする修正の事です。\n
バグの修正や未実装機能の実装によって、正常な動作になる場合は破壊的変更とは書いていません。\n
　SDXでは必要があったり、使いやすさが向上する場合破壊的変更を行った過去があるので、Verを上げたら大量のエラーが出る事がありました。\n
現状大体の問題は解消したのですが、今後も無いとは限りません。\n
修正内容については更新履歴を確認して下さい。\n
\n
　Verを上げた時に利用者のコードを修正する必要があるのは好ましくないのですが、破壊的変更を行わず使いにくいままにするより、修正を行ったほうが良い事もあるので、ご了承下さい。\n
\n
<HR>
Ｑ.Appstoreで配布出来ない？\n
このような事情があり配布は困難です。\n
年齢制限等は緩和されましたが他はあまり変わっていません。\n
http://sourceforge.jp/magazine/08/04/17/0141213
\n
　いわゆる脱獄アプリとして配布する事は可能ですが、メーカー保障が切れるそうなので推奨はしていません。\n
Appstore等で配布したい場合、別のライブラリを使う事をお勧めします。\n
Appstore以外でも秘密保持契約が必要だったり、DRMを付けないといけないプラットフォームでは基本的に配信出来ません。\n
\n
<HR>
Ｑ.SDXFrameworkのソースも一緒に配布する必要はありますか？\n
\n
Ａ.\n
　SDXFrameworkのバージョンと入手方法を明示していれば、ライブラリの部分は配布しなくてもかまいません。\n
ライブラリに何らかの修正を加えた場合は、少なくとも変更した箇所のコードを配布する必要があります。\n
\n
　一応サーバーからデータが消えるとかそういう事もあるので、一緒に配った方が確実ではあります。\n
\n
<HR>
Ｑ.関数の使い方はどうやって調べるの？\n
\n
Ａ.\n
　リファレンスやサンプルコードを読んでください。\n
\n
"Sample/Sample.h"をincludeして、Sample～で始まる関数を呼び出すとサンプルコードを実行する事が出来ます。\n
サンプルコードで使用している画像ファイルはdataフォルダ内の物を使って下さい。\n
<HR>
Ｑ.未実装機能とは？\n
\n
Ａ.\n
　クラスの詳細か関数の説明の後に[未実装]とある場合は未実装です、今後実装しない可能性もありますが、出来たら実装したい機能です.\n
@reftodo"未実装関数とクラス一覧"\n
<HR>
Ｑ.図形描画機能が貧弱だし、動画も扱えなくて不便、ネットワークや3D機能はなんで実装しないの？\n
\n
Ａ.\n
　基本的にライブラリ開発者がゲーム開発に必要としている機能を優先する方針で開発しています。\n
必要としていない機能は、レビューが困難ですし、実装するモチベーションも上がりません。\n
動画とか、ネットワークとか、画像処理は必要としている開発者がいないため今の所、実装される予定がありません。\n
必要になれば追加される可能性はあります。\n
<HR>
\n
Ｑ.なんで引数だけ日本語でクラス名とかは英語なの、ルー語？\n
\n
Ａ.\n
　普段日本語で思考しているので、日本語の方がライブラリが使いやすく開発が楽だからです。\n
というかわざわざ全部の識別子を英語にする理由がありません。\n
\n
　仮引数やローカル変数だけの理由は、android-ndkの対応状況を考慮したのと、\n
なんかの拍子に利用者が増えたので英訳しようとかなった場合も、仮引数だけなら翻訳が楽だからです\n
<HR>
\n
Ｑ.何故管理がGithubとOSDNに分かれているんですか？\n
\n
Ａ.\n
　Githubの方が使いやすいので、ソースはGithubで管理しています。\n
安定版をOSDNに置いているのは、Githubよりアクセス数が増えるのとバイナリの配布が楽だからです。\n
<HR>
Ｑ.SDXの意味は？\n
\n
Ａ.\n
　SDの部分はSDL、DXの部分はDXLibから取っています。最初はDXFrameworkという名称でした。\n
DXLibのラッパーとして開発していたのを途中で内部実装をSDLに変更したので、現在DXLibは使っていません。\n
しかしながら機能分割の粒度や関数の命名等でDXLibを参考にしているので、敬意を表して名称に残しています。\n
<HR>
Ｑ.何故DXLIB版の開発を辞めたの？\n
\n
Ａ.\n
機能はDXLibの方がSDLより豊富ですが、プラットフォーム対応の関係でSDLに専念する事にしました。\n
<HR>
Ｑ.SDL2.0の参考サイトとかありますか？\n
\n
Ａ.\n
こちらや\n
http://lazyfoo.net/tutorials/SDL/index.php
\n
ドキュメント日本語訳のプロジェクトが参考になると思います\n
https://sourceforge.jp/projects/sdl2referencejp/
\n
<HR>
Ｑ.初期のバージョンはzlibだけどこれはどうなるの？\n
\n
Ａ.\n
　ややこしいので、公式に旧verの配布はしていませんが、以前に公開していたverのライセンスはそのままです。\n
なので旧バージョンはzlibライセンスで利用する事が出来ますし、再配布も可能で、開発を引き継ぐのも特に問題はありません。\n
\n
<HR>
Ｑ.ttfを全部bmpフォントに置き換えたのでSDL2_ttfが必要なくなったのですが？\n
\n
Ａ.\n
ソースコードに『#define OMIT_SDL2_TTF』を定義するとttf関連の機能が無効になります。\n
そうするとttf関連のdllやframework等を削除出来ます。\n
Android向けの場合、各種Android.mkファイルで設定を変更して下さい。\n
\n
<HR>
Ｑ．分からない事があったら、どうすればよいですか？\n
\n
Ａ．\n
　掲示板で「新しい話題を始める」から質問して下さい。\n
<ahref="http://sourceforge.jp/projects/dxframework/forums/31378/"target="_blank"><B>SDXFramework：ヘルプフォーラム</B></a>\n
書き込んだら作者にメールが行くのでそれなりの早さで返信します。\n
\n
　作者のtwitterや、メール、ブログ等で質問されると確認が手間なのと、他の利用者と共有しにくいので、\n
公式フォーラムの利用を推奨しています。(twitterはbotなので、殆どチェックしません)\n
*/