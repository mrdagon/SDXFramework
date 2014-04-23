﻿/*!
@page WhatSDX SDXとは？
  SDXフレームワークはC++でゲーム制作するための、クラスライブラリです。\n
以下のような特徴があります。\n
<HR>
<B>特徴</B>\n
<B>1.マルチプラットフォーム</B>\n
  内部でSDLを使っているので、大体のプラットフォームで動きます。\n
  また、デバッグやら環境毎の最適化のため、SDXはマルチメディア部分のライブラリを切り替えれるように設計しています。\n
例えば、Windows環境ではDXライブラリが使えるので機能が多くなっています。\n

  このため現在利用しているライブラリの開発が止まったり、大規模アップデートで互換性が消えたり、\n
新たに高速な描画ライブラリが出て乗り換えたい場合等も、ライブラリの修正範囲を抑える事が出来ます\n
<HR>
<B>2.マルチメディア以外の機能</B>\n
  SDLやDXライブラリ、XNA等、DirectXやOpenGLのラッパーライブラリはマルチメディア機能とOS固有の処理を肩代わりする機能を持っています。\n
これだけでも低レベルなライブラリを使うのに比べて大分楽は出来ますが、ゲームアーキテクチャの基本設計は自力で構築する必要があるので、なんだかんだ大変です。\n
  cocos2d-X等のライブラリやUnity等のツールはそういった機能が提供されているように、SDXでも基本的な構造を提供しています。\n
SDXとそれらの違いは\n
  マルチメディア部分とアーキテクチャ部分を分離しているため、設計が気に入らないならマルチメディアだけでも使え、\n
アーキテクチャの基本設計を極力薄くしているので、ゲームジャンル毎にライブラリを切り替え可能な設計にしている事。\n
\n
  プログラミング初心者向けに作ると使う人は増えるかもしれないが、設計が変になりそうなので、初心者を意識せずに作っている事。\n
\n
  引数に日本語を使って、リファレンスを見る回数を減らせるようにしている事。\n
\n
  開発環境と統合された便利なレイアウトエディタが存在しない事等があります。\n
\n
  ゲームでは同じジャンルでも設計が大きく変わる事もあるので、そのまま使えない事も多いと思われますが、\n
その場合も改造しやすいサンプルソースみたいな感じで使う事が出来ます。\n
<HR>
<B>3.オープンソース</B>\n
  このライブラリは自分がゲーム開発を楽にするために開発を始めました。\n
実装作業は公開しようがしまいが必要ですが、ライブラリを公開するとドキュメントの整備やサポートを行う必要が出ます。\n
利用者が増えればバグ報告が来たり、色々メリットがあると思いますが、公開すると手間が増えるのはあまり好ましくありません。\n
  そのため、ソースコードを公開して開発者や利用者を広く集める事で\n
「ドキュメント整備やサポートの手間 ＜ 利用者によるバグ報告や他コミッタの実装による手間の削減、レビュー等個人開発では行えないメリットを受ける」となる事を目指しています。\n
\n
  そういった事情があるので、ライブラリ開発者が現在必要としていない機能は実装は後回しになっていたり、\n
引数名などを工夫してドキュメントを書く手間を削減したり、初心者しか使わない機能は排除したりしています。\n
  例えば、現状3Dの機能は実装されていませんが、3Dの機能が必要な人がライブラリ開発に加われば機能が増えるかもしれませんし、\n
マイナージャンルのフレームワークも開発者が加われば追加されるかもしれません。\n
MacやLinux環境でのサポートが早まるかもしれませんし、英語のドキュメントが追加されるかもしれません\n
  上手く開発者が集まれば、個人開発に比べて安定した上で高機能なライブラリになる可能性がありますが\n
一人も集まらなければ、2D専用のライブラリとしてゆっくり開発していくと思います。\n
\n
開発に興味がある人はSorceForgeの掲示板で気軽にお問い合わせ下さい。
<HR>
<B>対応開発環境</B>\n
  Windows7以降 + VisualStudio2013\n
\n
  MacOSX最新版 + Xcode最新版\n
\n
  解説を書いていないだけでどの環境でも大体使えます\n
<HR>
<B>機能一覧</B>\n
  @ref ClassGroup
*/