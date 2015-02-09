﻿/*!
@page PortaBility 移植においての注意
　SDXはWindows、Mac、GNU/Linux、iOS、Android等に対応するソフトウェアを、ソースコードの修正を殆どせずに作成出来ます。\n
\n
　しかしながら実際は様々な理由でそのまま動かない事があるので、以下の点等に注意する必要があります。\n
例えば特定のコンパイラの拡張文法や特定OSのAPIを使っている場合、当然移植性が下がります\n
\n
<HR>
<B>文字エンコーディング</B>\n
　BOM付きのUTF-8でソースコードを保存する事を推奨します。\n
Shift-JIS等で保存するとVisualStudio以外でビルド不可能になる事があります。\n
\n
　VisualStudioにはデフォルトでUTF-8で保存する設定が面倒なので、\n
Shift-JISには存在しないがUTF-8に存在する文字(例:☀や©)をコメントしておくと安心です\n
\n
外部リソースとしてテキストファイルを使う場合もShift-JISで無くUTF-8が推奨されます\n
<HR>
<B>リソースファイル名</B>\n
一部環境でエラーが出るため、画像やテキストファイル名、フォルダ名等はアルファベット(a~z,A~Z)と数字(0~9)と半角アンダーバーのみにして下さい。\n
Androidを想定する場合、大文字のアルファベットも避けて下さい。\n
<HR>
<B>WindowsXP</B>\n
VisualStudioで作成したソフトをWindowsXPで動かしたい場合、設定を変更する必要があります。\n
プロジェクト>プロパティ>構成プロパティ>全般>プラットフォームツールセットをXPに対応している物に変更して下さい。
<HR>
<B>識別子</B>\n
　Androidでは関数名やクラス名等にアルファベット(a~z,A~Z)と数字(0~9)と半角アンダーバー以外を使うとエラーが出る事があります。\n
仮引数や変数に使う分にはエラーは出ないようです。Android以外では問題なく基本ソース文字セット以外の識別子が使えます。\n
一応ソースを変換するツール(UTF_Convert.exe)も配っているので、必要なら使ってください\n
https://github.com/mrdagon/UTFConvert \n
<HR>
<B>デフォルトフォント</B>\n
　OSによってシステムフォントのパスが変わるため、デフォルトフォントで描画出来ない事があります。\n
@code
Drawing::SetDefaultFont("配布するフォント名.ttf",16);
@endcode
　ttfファイルを一緒に配布して、上のような処理をしておくと各プラットフォームでデフォルトフォントを共通に出来ます\n
複数のOSに対応したい場合、OS標準フォントは使うのを避けて下さい\n
<HR>
<B>ファイル入出力</B>\n
　テキストファイルの入出力処理を標準ライブラリの関数で行うと、保存先がOSによってバラバラになります。\n
Fileクラスを使ってください。\n
\n
特にAndroidではFile::Openの第四引数で保存先が変わるので注意して下さい\n
<HR>
<B>デスクトップとタブレットにおける入出力の違い</B>\n
　タブレットOSでタッチ操作をするとMouseクラスとTouchクラスの両方で値を更新しますが、\n
デスクトップOSでマウス操作をしてもTouchクラスを更新していません。\n
仮想ジョイパッドを画面に表示したりも今のところしていません\n
この辺りは仕様が変わる可能性があります\n
<HR>
<B>ソースファイル</B>\n
　Android版ではソースファイル名をmkファイルに列挙する必要があります\n
実装と宣言を分けて開発している場合はAndroid.mkファイルを修正する必要がありますし、プリコンパイルヘッダー作成用のソース等も追加する必要があります\n
OS毎にプリコンパイルの設定が面倒な場合は以下のようにmain.cppでインクルードすると楽です\n
@code
#ifndef __WINDOWS__
	#include "PreCompile.cpp"
	#include "main2.cpp"
#endif
@endcode
\n
　またヘッダーファイル名がSDLで使われているヘッダーファイルと被るとエラーになる事があります。
@code
#include "block.h"
@endcode
でバグりました\n
<HR>
*/