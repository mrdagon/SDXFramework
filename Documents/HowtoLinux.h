/*!
@page howtoLinux SDXの導入方法(Linux)
 Ubuntuでの導入方法メモです。\n
 多分、この通りにやっても上手く行きません\n
 linuxのディストリビューションによってSDL2.0のインストール方法が変わります\n
 Ubuntu13.10のclangはデフォルトでver3.27であり、Unicodeの識別子が使えません\n
 しかしUbuntuのclang-3.3パッケージにバグ?があるのかSDL2.0の動作しか確認していません\n
<HR>
<B>1.SDL2.0のインストール</B>\n
 ターミナルを起動して以下のコマンドを実行する\n
 $ sudo apt-get install libsdl2-dev\n
 $ sudo apt-get install libsdl2-image-dev\n
 $ sudo apt-get install libsdl-ttf2.0-dev\n
 $ sudo apt-get install libsdl2-mixer-de\n
 これでSDLの必要なファイルがインストールされます
<HR>
<B>2.SDXの導入</B>\n
 SDXFramework_SDL2/jni/SDL/includeフォルダをインクルードパスに指定するか\n
 usr/include等のフォルダに置いて下さい\n
<HR>
<B>3.コンパイル</B>\n
 clangの最新版や標準ライブラリ等を自前でコンパイルしc++のコンパイルが可能な状態にします\n
 \n
 main.cppファイルを作成します。\n
 @code
 #include <SDXFrameWork.h>
 #include <Multimedia/SDXafx.h>

 using namespace SDX;

 int main(int argc, char* argv[])
 {
 System::Initialise("sample", 640, 480);//ライブラリの初期化

 int x = 320;
 int y = 240;

 while (System::Update())
 {
 if (Input::pad.Down.hold) y += 5;
 if (Input::pad.Up.hold) y -= 5;
 if (Input::pad.Right.hold) x += 5;
 if (Input::pad.Left.hold) x -= 5;

 Drawing::Rect(x-10, y-10, 20, 20, Color::White, true);
 }

 System::End();//ライブラリの終了処理

 return 0;
 }
 @endcode
 main.cppがあるディレクトリに移動してコマンドを実行\n
 $ clang -o sdxtest main.cpp -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer\n
*/