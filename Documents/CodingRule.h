﻿/*!
@page CodingRule SDXコーディング規則
 \n
@section はじめに
 普通にコードを書いた後、レビュー成果物として作成した資料です。\n
同じような事をしてるのにやたらバラバラな事をしていたり、よく考えると不自然な書き方をしているかを分析するために書いています。\n
\n
　数ページの規約を守れば誰でも分かりやすいコードが書けるなんてことはないです。\n
例えば、「yes/noを表す変数はintで無くboolを使おう｣とか｢NULLじゃなくnullptr使おう｣とか常識的な事は規約に書く意味は薄いです。\n
こう言う事を書いても無駄に規約が長くなって読むのが面倒になる上、大量にある常識的を全て抜け無く書くのは難しく、中途半端で意味が無いです\n
\n
なので本規約は「複数のコーディングスタイルがありどちらも大した差がないので、どちらかに統一する｣事が主眼になっています。\n
例えば、インデントを4か8にするかTabにするか空白にするかは大した差が無いかもしれませんが、少なくとも同じプロジェクト内ではどちらかに統一すべきと言った具合です\n
\n
　また特殊な事情で制限をかけている事が少しあるので、その辺りの注意等も書いています\n
\n
<B>基本方針</B>\n
①C++初学者のために初歩的な構文だけ使うとか考えない、常識的なコードを書く\n
②仮引数以外の日本語識別子は基本的に避ける\n
③規約に問題があれば見直しを行う\n
\n
<B>適用範囲</B>\n
  SDXのみ対象です。\n
  派生ライブラリやサンプルコードは命名規則に準拠せず、英語以外の識別子を必要な時に使います。\n
  また、こう言う方針で書いてると言うだけなので、プルリクエストする時にここの規約に合わせる必要もないです\n
もしプルリクエストが来たら、規約から外れ過ぎないように修正して取り込みます\n
またレビューを厳密に行っていないので、多少は方針に従っていないコードがあります\n
\n
<B>参考</B>\n
以下のページや書籍等を参考にしたり反面教師にしたりしています\n
<a href="http://msdn.microsoft.com/ja-jp/library/ms229042(v=vs.100).aspx" target="_blank"><B>クラスライブラリ開発のデザインガイドライン</B></a>\n
<a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml" target="_blank"><B>Google C++スタイルガイド</B></a>\n
Effective C++（書籍）
@section 命名規則
コードの一貫性を保つ上で、最も重要ですが常識に頼ると統一出来ない部分です\n
\n
<B>基本</B>\n
  無理の無い範囲でわかりやすくする。一般的ではない省略は行わない。\n
InitializeをInitとしたりしているが、極力さけたいので変更するかもしれない\n
\n
<B>ファイル名</B>\n
  ヘッダーファイル名は、クラス名と同じにし拡張子は.hにし.hppにしない。\n
\n
<B>仮引数</B>\n
基本的に日本語にします。\n
Unicode範囲内の特殊な記号は使いません\n
句読点などの規格非準拠な文字は使いません\n
\n
<B>仮引数以外の識別子</B>\n
  それ以外は半角英数とアンダーバーで命名します\n
ローマ字表記は避け、英単語を元に命名します、$記号は使いません\n
\n
<B>大文字と小文字の使い分け</B>\n
  先頭と単語の区切りを大文字にするのをPascal形式と言い、先頭を小文字にし単語の区切りを大文字にするのをCamel形式と言います。\n
\n
クラス、構造体、メンバー関数、列挙体、列挙子、ローカルで無い定数はPascal形式\n
\n
ローカル変数とメンバー変数はCamel形式\n
\n
マクロはすべて大文字にして_で単語をつなぐ。ただし、必要で無い場合はマクロは避けます。\n
\n
名前空間は全て大文字にし_で単語を繋ぎます\n
\n
<B>慣用的な命名</B>\n
ループカウンタはa,b,cの順で一文字の変数を用いる、基本的に3重以上のループは書かない\n
範囲ベースのループは for(auto it: hoge)とかfor(auto & it:hoge)とかfor(const auto &int :hoge)とかにする\n
bool値はis～、can～にする\n
テンプレート仮引数の前にはTを付ける\n
\n
@section スタイルの統一
<B>ヘッダーファイル</B>\n
基本的にはヘッダーファイルで実装と宣言をする。\n
実装が不可能な場合は実装と宣言を分ける\n
前方宣言で十分な場合、無闇にincludeしない\n
\n
<B>可変数引数</B>\n
可変数引数は使わず可変テンプレートを使います。\n
抽象クラスのメンバー関数に可変数引数が必要な場合は、可変テンプレートで初期化可能な型を引数にします\n
文字列の場合はVariadicStreamを使います\n
\n
<B>インライン関数</B>\n
inlineキーワードは使わず、コンパイラの判断にまかせたいのですが、\n
明示的に書かないとinline化してくれない事もあるので必要なら使います。\n
\n
<B>インクルードガード</B>\n
使いたいコンパイラが全て #pragma onceを実装しているため。\n
#defineによるインクルードガードではなく、#pragma onceを使う。\n
\n
<B>キャスト</B>\n
int,float,doubleの相互変換はcスタイルキャスト可。\n
それ以外はc++スタイルのキャストを使う。\n
\n
列挙型とintの相互変換もcスタイルキャストしても良いがなるべく避ける\n
(int)(value)を推奨\n
<B>座標型</B>\n
int型の座標とdouble型の座標を示したい場合がありややこしいので、Pointを引数に使わない\n
心変わりするかも\n
\n
@section その他
<B>名前空間</B>\n
グローバル変数は作らず、少なくともSDX名前空間に入れる。\n
using namespace std;は使わない\n
DxLib名前空間は省略しない\n
\n
<B>仮想クラス</B>\n
純粋仮想関数を１つ以上持つクラスは、先頭にIをつけます。\n
メンバー変数を持っていてもIを付けます\n
\n
<B>アクセス制御</B>\n
公開する必要の無い、関数や変数はプライベートにする。\n
代入か取得の片方しかしないメンバー変数はプライベートにし、Get関数とSet関数を作る。\n
GetとSetの両方をしたい場合はpublicにしても良い\n
\n
<B>宣言の順番</B>\n
まずprivate、次にprotected、そしてpublic\n
変数の宣言ののち関数を宣言する\n
調整中\n
\n
<B>入出力ストリーム、文字列ストリーム</B>\n
ライブラリ内部では使う、利用者は使用せずにライブラリを使えるようにする。\n
\n
<B>インクリメント</B>\n
最適化されてもされなくても速度差は殆ど無いが\n
デバッグビルドもあるので基本的に前置インクリメントを使う\n
\n
<B>float型</B>\n
基本的に使わず、doubleに統一する\n\n
\n
<B>Boost</B>\n
標準ライブラリを優先して使い、必要な場合はboostを使う。\n
\n
<B>C++11/14/1z</B>\n
VisualStudio2013とclang3.3で対応している範囲のみ使用可能。\n
\n
<B>コメント</B>\n
ソースコード管理システムに登録されるような事は書かない。\n
仮引数と戻り値用のドキュメントコメントは使わない\n
関数とクラスには一行以上の説明を必ず付ける\n
クラスに対してはテストコードをサンプルコードとして付ける\n
変数と列挙子は必要なら一行で説明をつける。コメントなしで分かる変数名にするのが良い。\n
コメントアウトしたコードは速やかに削除する\n
\n
<B>実装コメント</B>\n
分かりにくい場合、関数内部に説明のコメントをつける。\n
サンプルコードについては詳細に付けて良い\n
\n
<B>インデント、スペースとタブ</B>\n
タブ幅は4とし、半角スペースを使う\n
\n
<B>括弧</B>\n
括弧と括弧閉じは同じ高さ、あるいは同じ行にする。
例外としてelseを使う場合は以下の書き方をしても良い。
@code
//ダメ
if( x == 1 ){
    func();
}
//良い
if( x == 1 )
{
    func();
}

//良い
if( x == 1 )
{
    func();
}else{
    func2();
}
@endcode
\n
*/
