#pragma once//☀SDXFramework
#include <Multimedia/Image.h>
#include <Framework/Anime.h>
#include <Multimedia/Font.h>
#include <Multimedia/Screen.h>

namespace SDX
{
/** ビットマップフォントを表すクラス.*/
/**    \include BmpFontSample.h*/
class BmpFont : public IFont
{
private:
    ImagePack *divImageNumber;
    ImagePack *divImageAlphabetCapital;
    ImagePack *divImageAlphabetLow;

    bool isNumber;
    bool isAlphabetCapital;
    bool isAlphabetLow;
    int numberHeight;
    int numberWidth;
        
    int alphabetCapitalHeight;
    int alphabetCapitalWidth;

    int alphabetLowHeight;
    int alphabetLowWidth;

    int maxHeight;

    int enterSpace;

    int spaceWidth;
public:
    BmpFont():
        isNumber(false),
        isAlphabetCapital(false),
        isAlphabetLow(false),
        enterSpace(0)
    {}

    ~BmpFont(){};
        
    /** 改行の高さを取得.*/
    int GetEnterHeight() const
    {
        return this->enterSpace;
    }
            
    /** 改行の高さを設定.*/
    /**0の場合、改行後の上下がくっつく*/
    void SetEnterHeight(int 改行の高さ)
    {
        this->enterSpace = 改行の高さ;
    }
            
    /** 数字フォントを設定.*/
    /**    数字描画に使うImagePackを設定する\n
        0～9の順に10個並べた画像を使う*/
    bool SetNumber( ImagePack* 数字用イメージ )
    {
        if( 数字用イメージ->GetSize() < 10 ) return false;

        divImageNumber = 数字用イメージ;

        numberWidth = 数字用イメージ->GetWidth();
        numberHeight = 数字用イメージ->GetHeight();
        spaceWidth = 数字用イメージ->GetWidth();

        maxHeight   = std::max( maxHeight , 数字用イメージ->GetHeight() );
        isNumber = true;

        return true;
    }
            
    /** 英大文字フォントをセット.*/
    /**    英大文字に使うImagePackを設定する\n
        A～Zの順に26個並べた画像を使う*/
    bool SetAlphabetCapital(ImagePack* 大文字用イメージ )
    {
        if( 大文字用イメージ->GetSize() < 26 ) return false;

        this->divImageAlphabetCapital = 大文字用イメージ;

        this->alphabetCapitalWidth = 大文字用イメージ->GetWidth();
        this->alphabetCapitalHeight = 大文字用イメージ->GetHeight();
        this->spaceWidth = 大文字用イメージ->GetWidth();
    
        this->maxHeight = std::max(this->maxHeight, 大文字用イメージ->GetHeight());
                
        this->isAlphabetCapital = true;

        return true;
    }
            
    /** 英小文字フォントをセット.*/
    /** 英小文字に使うImagePackを設定する\n
        A～Zの順に26個並べた画像を使う*/
    bool SetAlphabetLow(ImagePack* 小文字用イメージ )
    {
        if( 小文字用イメージ->GetSize() < 26 ) return false;

        divImageAlphabetLow = 小文字用イメージ;

        alphabetLowWidth = 小文字用イメージ->GetWidth();
        alphabetLowHeight = 小文字用イメージ->GetHeight();
        spaceWidth = 小文字用イメージ->GetWidth();
                
        maxHeight = std::max( maxHeight, 小文字用イメージ->GetHeight());
                
        isAlphabetLow = true;
        return true;
    }
            
    /** 書式付きで文字を描画.*/
    bool Draw(int X座標 , int Y座標 , Color 描画色 , VariadicStream 描画する文字列 ) const override
    {
        Screen::SetBright(描画色);

        
        for (auto it : 描画する文字列.StringS)
        {
            int i = 0;
            int addX = 0;
            int addY = this->maxHeight;
            const char* bufstr = it.c_str();

            while ( bufstr[i] != 0)//終端なら終了
            {
                if (bufstr[i] >= '0' && bufstr[i] <= '9' && this->isNumber)
                {
                    divImageNumber[0][bufstr[i] - '0']->DrawExtend(
                        X座標 + addX,
                        Y座標 + addY - this->numberHeight,
                        X座標 + addX + this->numberWidth,
                        Y座標 + addY);

                    addX += this->numberWidth;
                }
                else if (bufstr[i] >= 'A' && bufstr[i] <= 'Z' && this->isAlphabetCapital)
                {

                    divImageAlphabetCapital[0][bufstr[i] - 'A']->DrawExtend
                        (
                        X座標 + addX,
                        Y座標 + addY - this->alphabetCapitalHeight,
                        X座標 + addX + this->alphabetCapitalWidth,
                        Y座標 + addY
                        );

                    addX += this->alphabetCapitalWidth;

                }
                else if (bufstr[i] >= 'a' && bufstr[i] <= 'z' && this->isAlphabetLow)
                {

                    divImageAlphabetLow[0][bufstr[i] - 'a']->DrawExtend
                        (
                        X座標 + addX,
                        Y座標 + addY - this->numberHeight,
                        X座標 + addX + this->numberWidth,
                        Y座標 + addY
                        );

                    addX += this->alphabetLowWidth;

                }
                else if ( bufstr[i] == ' ')
                {
                    addX += spaceWidth;
                }
                ++i;
                if (i == strlen( bufstr )) break;
            }
            addY += maxHeight + enterSpace;
        }

        Screen::SetBright(Color::White);
        return true;
    }
    bool ZMask(int X座標, int Y座標, ZMaskType Zマスクタイプ, VariadicStream 描画する文字列) const override
    {
        for (auto it : 描画する文字列.StringS)
        {
            int i = 0;
            int addX = 0;
            int addY = this->maxHeight;
            const char* bufstr = it.c_str();

            while (bufstr[i] != 0)
            {
                if (bufstr[i] >= '0' && bufstr[i] <= '9' && this->isNumber)
                {
                    this->divImageNumber[0][bufstr[i] - '0']->ZMaskExtend
                        (
                        X座標 + addX,
                        Y座標 + addY - this->numberHeight,
                        X座標 + addX + this->numberWidth,
                        Y座標 + addY,
                        Zマスクタイプ
                        );
                    addX += this->numberWidth;
                }
                else if (bufstr[i] >= 'A' && bufstr[i] <= 'Z' && this->isAlphabetCapital)
                {

                    this->divImageAlphabetCapital[0][bufstr[i] - 'A']->ZMaskExtend
                        (
                        X座標 + addX,
                        Y座標 + addY - this->alphabetCapitalHeight,
                        X座標 + addX + this->alphabetCapitalWidth,
                        Y座標 + addY,
                        Zマスクタイプ
                        );

                    addX += this->alphabetCapitalWidth;

                }
                else if (bufstr[i] >= 'a' && bufstr[i] <= 'z' && this->isAlphabetLow)
                {

                    this->divImageAlphabetLow[0][bufstr[i] - 'a']->ZMaskExtend
                        (
                        X座標 + addX,
                        Y座標 + addY - this->numberHeight,
                        X座標 + addX + this->numberWidth,
                        Y座標 + addY,
                        Zマスクタイプ
                        );

                    addX += this->alphabetLowWidth;

                }
                else if (bufstr[i] == ' ')
                {
                    addX += this->spaceWidth;
                }
                ++i;
                if (i == strlen(bufstr)) break;
            }
            addY += this->maxHeight + this->enterSpace;
        }
        return true;
    }
    
    /** 文字を回転して描画[未実装].*/
    bool DrawRotate(int X座標, int Y座標, double 拡大率, double 角度, Color 描画色, bool 反転フラグ, VariadicStream 描画する文字列) const override
    {
        return false;
    }
    /** 文字を回転してマスク[未実装].*/
    bool ZMaskRotate(int X座標, int Y座標, double 拡大率, double 角度, ZMaskType Zマスクタイプ, bool 反転フラグ, VariadicStream 描画する文字列) const override
    {
        return false;
    }

    /** 拡大率を指定して文字を描画.*/
    bool DrawExtend(int X座標, int Y座標, double X拡大率, double Y拡大率, Color 描画色, VariadicStream 描画する文字列) const override
    {
        for (auto it : 描画する文字列.StringS)
        {
            int i = 0;
            int addX = 0;
            int addY = this->maxHeight;
            const char* bufstr = it.c_str();

            Screen::SetBright(描画色);

            while (bufstr[i] != 0)
            {
                if (bufstr[i] >= '0' && bufstr[i] <= '9' && this->isNumber)
                {

                    this->divImageNumber[0][bufstr[i] - '0']->DrawExtend
                        (
                        X座標 + int(addX * X拡大率),
                        Y座標 + int((addY - this->numberHeight) * Y拡大率),
                        X座標 + int((addX + this->numberWidth) * X拡大率),
                        Y座標 + int(addY * Y拡大率)
                        );

                    addX += this->numberWidth;

                }
                else if (bufstr[i] >= 'A' && bufstr[i] <= 'Z' && this->isAlphabetCapital)
                {

                    this->divImageAlphabetCapital[0][bufstr[i] - 'A']->DrawExtend
                        (
                        X座標 + int(addX * X拡大率),
                        Y座標 + int((addY - this->alphabetCapitalHeight) * Y拡大率),
                        X座標 + int((addX + this->alphabetCapitalWidth) * X拡大率),
                        Y座標 + int(addY * Y拡大率)
                        );

                    addX += this->alphabetCapitalWidth;

                }
                else if (bufstr[i] >= 'a' && bufstr[i] <= 'z' && this->isAlphabetLow)
                {
                    this->divImageAlphabetLow[0][bufstr[i] - 'a']->DrawExtend
                        (
                        X座標 + int(addX * X拡大率),
                        Y座標 + int((addY - this->alphabetLowHeight) * Y拡大率),
                        X座標 + int((addX + this->alphabetLowWidth) * X拡大率),
                        Y座標 + int(addY * Y拡大率)
                        );

                    addX += this->alphabetLowWidth;
                }
                else if (bufstr[i] == ' ')
                {
                    addX += this->spaceWidth;
                }
                ++i;
                if (i == strlen(bufstr)) break;
            }
            addY += this->maxHeight + this->enterSpace;
        }

        Screen::SetBright(Color::White);

        return true;
    }
    bool ZMaskExtend(int X座標, int Y座標, double X拡大率, double Y拡大率, ZMaskType Zマスクタイプ, VariadicStream 描画する文字列) const override
    {
        for (auto it : 描画する文字列.StringS)
        {
            int i = 0;
            int addX = 0;
            int addY = this->maxHeight;
            const char* bufstr = it.c_str();

            while (bufstr[i] != 0)
            {
                if (bufstr[i] >= '0' && bufstr[i] <= '9' && this->isNumber)
                {

                    this->divImageNumber[0][bufstr[i] - '0']->ZMaskExtend
                        (
                        X座標 + int(addX * X拡大率),
                        Y座標 + int((addY - this->numberHeight) * Y拡大率),
                        X座標 + int((addX + this->numberWidth) * X拡大率),
                        Y座標 + int(addY * Y拡大率),
                        Zマスクタイプ
                        );

                    addX += this->numberWidth;

                }
                else if (bufstr[i] >= 'A' && bufstr[i] <= 'Z' && this->isAlphabetCapital)
                {

                    this->divImageAlphabetCapital[0][bufstr[i] - 'A']->ZMaskExtend
                        (
                        X座標 + int(addX * X拡大率),
                        Y座標 + int((addY - this->alphabetCapitalHeight) * Y拡大率),
                        X座標 + int((addX + this->alphabetCapitalWidth) * X拡大率),
                        Y座標 + int(addY * Y拡大率),
                        Zマスクタイプ
                        );

                    addX += this->alphabetCapitalWidth;

                }
                else if (bufstr[i] >= 'a' && bufstr[i] <= 'z' && this->isAlphabetLow)
                {
                    this->divImageAlphabetLow[0][bufstr[i] - 'a']->ZMaskExtend
                        (
                        X座標 + int(addX * X拡大率),
                        Y座標 + int((addY - this->alphabetLowHeight) * Y拡大率),
                        X座標 + int((addX + this->alphabetLowWidth) * X拡大率),
                        Y座標 + int(addY * Y拡大率),
                        Zマスクタイプ
                        );

                    addX += this->alphabetLowWidth;
                }
                else if (bufstr[i] == ' ')
                {
                    addX += this->spaceWidth;
                }
                ++i;
                if (i == strlen(bufstr)) break;
            }
            addY += this->maxHeight + this->enterSpace;
        }
        return true;
    }
    
};
}