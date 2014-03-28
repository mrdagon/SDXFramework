/*!
@page howtoAndroid SDXの導入方法(android)
 SDXFrameWorkの利用にはSDXFrameWork_SDL2が必要です。\n
 androidの環境構築は他のOSに比べるとややこしいです\n
 実機デバッグの設定方法は機種により違うので各自で調べて下さい\n
<HR>
<B>1.android-sdkの導入</B>\n
以下のサイトを参考にしてjavaやeclipseの環境を構築して下さい\n
http://techfun.cc/techinf/setup/android/ \n
<HR>
<B>2.android-ndkの導入</B>\n
以下のサイトを参考にしてandroid-ndkを導入して下さい\n
http://dench.flatlib.jp/opengl/androidsdk \n
<HR>
<B>3.SDXの導入とプロジェクト作成</B>\n
 eclipseを起動すると作成されるworkspaceフォルダにSDXFrameWork_SDL2フォルダを移動します。\n
 コマンドプロンプトを開き cd workspace/SDXFrameWork_SDL2 で作成したプロジェクトのフォルダに移動\n
 ndk-build のコマンドでコンパイルをします\n
 \n
 eclipseを起動し、ファイルメニューからインポートを選び、Existing Android Code Into Workspaceを選びます\n 
 ルート・ディレクトリにworkspace内のSDXFrameWork_SDL2フォルダを選択します\n
 プロジェクトをワークスペースにコピーにチェックを入れ、新規プロジェクト名を変更し完了を押します。\n
 少し待つとコピーされたプロジェクトが作成されます\n
 \n
 workspace/作成したプロジェクト名/jni/srcの中にあるmain.cppにC++のコードを書いて下さい\n
 \n
 workspace/作成したプロジェクト名/assetsの中に画像ファイル等のリソースを置いてください。
<HR>
<B>4.コンパイルと実行</B>\n
コマンドプロンプトを開き cd workspace/sdlactivity 等で作成したプロジェクトのフォルダに移動\n
ndk-build のコマンドでコンパイルを行います\n
\n
eclipseから実行を押すと、ソフトが起動します\n
シミュレータの場合、OpenGL絡みのでエラーが出る場合があります\n
その場合は実機でデバッグして下さい
<HR>
<B>5.eclipse上でのndk-build</B>\n
 プロジェクト>プロパティー>C/C++ ビルド>ツールチェーンエディターの\n
 現在のビルダーを AndroidBuilderに変更します、調査中\n
<HR>
<B>6.配布ファイル名の変更</B>\n
 このページを参考にして下さい\n
 http://ggkuron.hatenablog.com/entry/2013/08/02/073940\n
<HR>
<B>7.配布方法</B>\n
binフォルダに.apkファイルが作成されるので、それを配布して下さい。\n
 配布方法は色々あるので、GooglePlayへの登録方法等をネットで調べて下さい。\n
<B>8.端末の向きの変更</B>\n
AndroidManifest.xmlを書き換えて変更します。\n
android:screenOrientation="landscape"\n
で横に固定します。\n
android:screenOrientation="portrait"\n
で縦に固定\n
回転可能にしたい場合は自分で調べて下さい
*/
