#pragma once//☀DXLIB
/** OS標準の日本語フォント.*/
/** SystemFont::GothicとSystemFont::Mincho以外はプラットフォーム依存*/
/** 参考外部リンク:http://rinrin.saiin.net/~aor/fonts/fonts */
namespace SystemFont
{
    static const char* Gothic = "MS UI Gothic";///< 各OS標準の日本語フォント
    static const char* Mincho = "ＭＳ 明朝";///< 各OS標準の日本語フォント

    static const char* UI_Gothic = "MS UI Gothic";
    static const char* Ｐゴシック = "ＭＳ Ｐゴシック";
    static const char* ゴシック = "ＭＳ ゴシック";
    static const char* Ｐ明朝 = "ＭＳ Ｐ明朝";
    static const char* 明朝 = "ＭＳ 明朝";
    static const char* メイリオ = "メイリオ";
    static const char* Meiryo_UI = "Meiryo UI";
    //win8.1以降
    //static const char* 游ゴシック = "";
    //static const char* 游ゴシック_Light = "";
    //static const char* 游ゴシック_Bold = "";
    //static const char* 游明朝 = "";
    //static const char* 游明朝_Demibold = "";
}