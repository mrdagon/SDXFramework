﻿/*!
@page PortaBility 移植性においての注意
  SDXはWindows、Mac、Linux系、iOS、Android、WindowsStoreAppで動くため、ソースコードの修正作業等は殆ど必要ありません。\n
\n
  しかしながら実際は様々な理由でそのまま動かない事があるので、以下の点等に注意する必要があります。\n
\n
<HR>
<B>文字エンコーディング</B>\n
BOM付きのUTF-8でソースコードを保存して下さい。\n
Shift-JIS等で保存するとVisualStudio以外でビルド不可能になる事があります。\n
\n
VisualStudioにはデフォルトでUTF-8で保存する機能がないので、ファイルオプションから個別に設定を行うか、\n
Shift-JISには存在しないがUTF-8に存在する文字(例:☀や☎)をコメントする等して下さい\n
\n
外部リソースとしてテキストファイルを使う場合もShift-JISで無くUTF-8を使いましょう\n
<HR>
<B>リソースファイル名</B>\n
Androidでエラーが出るため、画像やテキストファイル名、フォルダ名等はアルファベット(a~z,A~Z)と数字(0~9)と半角アンダーバーのみにして下さい。\n
<HR>
<B>識別子</B>\n
Androidでエラーが出るため、関数名、クラス名等はアルファベット(a~z,A~Z)と数字(0~9)と半角アンダーバーのみにして下さい。\n
仮引数や変数に使う分にはエラーは出ないようです、また一応ソースを変換するツールも配っています\n
<HR>
<B>デフォルトフォント</B>
OSによってシステムフォントのパスが変わるため、デフォルトフォントで描画出来ない事があります。\n
@code
Drawing::SetDefaultFont("配布するフォント名.ttf",16);
@endcode
ttfファイルを一緒に配布して、上のような処理をしておくと各プラットフォームでデフォルトフォントを共通に出来ます\n
<HR>
<B>DXLIB版とSDL版</B>\n
WindowsはDXLIB、それ以外はSDLで開発する事も可能です。\n
そういった場合、一部の関数はDXLIBでしか実装されていない事や一部の関数(SetIcon等)の仕様が違う事に注意して下さい。\n
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
<B>ソースファイル名</B>\n
Android版ではソースファイル名をmkファイルに列挙する必要があります\n
実装と宣言を分けて開発している場合はAndroid.mkファイルを修正する必要がありますし、プリコンパイルヘッダー作成用のソース等も追加する必要があります\n
\n
またヘッダーファイル名がSDLで使われているヘッダーファイルと被るとエラーになる事があります。#include "block.h"等でバグりました\n
<HR>
<B>jpgファイル</B>\n
AndroidでArm以外のCPU向けにビルドすると、エラーが出ています。\n
jpgの使用をオフにすると動くのですが、原因が分かっていません。\n
<HR>
<B>アプリ内課金や広告、BlueTooth通信等</B>\n
今のところSDXで実装していないので、自前処理する必要があります。\n
また特定のコンパイラの拡張書式や特定OSのAPIを使っている場合、移植性が下がります\n
*/