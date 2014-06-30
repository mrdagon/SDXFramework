﻿/*!
@page ReleaseNote 更新履歴
各バージョンの主な更新履歴です \n
詳細はGithubのコミットコメントを確認して下さい\n
今後の変更予定はSorceForgeの
\n
<HR>
<B>ver 0.09</B>\n
DXLIB版を開発停止、以降はSDL2.0版の開発に注力して行きます。\n
DXLIB版とSDL2.0版の互換性の維持を終了\n
\n
int 座標X,int 座標Yとなっている関数をconst Point &座標に変更\n
int X座標,int Y座標,int 高さ,int 幅はconst Rect &領域に変更\n
非実装だったZマスク系関数を削除\n
テキスト入力系の関数を一旦削除\n
Rectの座標を左上以外に出来るように変更\n
ユーティリティーにEnumArrayを追加
<B>ver 0.08</B>\n
細かいバグを修正\n
<B>ver 0.07</B>\n
Android対応強化\n
Fileクラスを修正、Multimediaフォルダに移動\n
ModelMoveクラスの関数名を全て英語に変更\n
四角同士の当たり判定の無駄な処理を消して高速化\n
Touchクラスを追加\n
Sample.hをSample/Sample.hに変更\n
可変文字列の引数を全てVariadicStreamに変更\n
ドキュメントに移植に関するページを追加\n
大体実装が終わったので、SDL版とDXLIB版のソースを分割、#define SDLや#define DXLIBを不要に\n
\n
<B>ver 0.06</B>\n
iOSとandroidに暫定対応\n
\n
SDL版のImage::DrawRotateのバグを修正\n
<HR>
<B>ver 0.051</B>\n
SystemFont名前空間にデフォルトフォントを追加\n
DrawingにSetDefaultFont関数を追加\n
\n
MacでもFileクラスのファイル指定が常に相対パスになるように修正\n
\n
WindowsでSDLを使う場合、#define SDL_WINとするように変更\n
\n
サンプルゲームのバグを大幅に修正\n
\n
Fontの回転描画と、フォントからImageを作成する関数を追加\n
\n
SDLに円等の図形描画機能を実装\n
<B>ver 0.05</B>\n
MacOSX対応\n
\n
可変数引数を使用していた関数を全てVariadicStreamを利用するように変更\n
\n
Fileクラスのバグを修正\n
\n
SpFontの仕様を変更\n
\n
Drawing::Rect\n
Screen::SaveBmp\n
Screen::SetArea\n
の3つを座標指定から大きさを指定するように変更
\n
AsyncroLoad を ThreadLoad に 改名\n
\n
線分と円の当たり判定のバグを修正\n
\n
コメントや引数名を修正\n
\n
UpDateとなっていた関数をUpdateに変更\n
\n
<BR>
<B>ver 0.04</B>\n
安定版として公開開始\n
*/