//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Image.h>
#include <Framework/Anime.h>
#include <Multimedia/Font.h>
#include <Multimedia/Screen.h>

namespace SDX
{
	/** ビットマップフォントを表すクラス[非推奨].*/
	/** MixFontクラスの利用を推奨*/
	/** \include BmpFont.h*/
	class BmpFont : public IFont
	{
	private:
		ImagePack *divImageNumber;//!<
		ImagePack *divImageAlphabetCapital;//!<
		ImagePack *divImageAlphabetLow;//!<

		bool isNumber;//!<
		bool isAlphabetCapital;//!<
		bool isAlphabetLow;//!<
		int numberHeight;//!<
		int numberWidth;//!<

		int alphabetCapitalHeight;//!<
		int alphabetCapitalWidth;//!<

		int alphabetLowHeight;//!<
		int alphabetLowWidth;//!<

		int maxHeight;//!<

		int enterSpace;//!<

		int spaceWidth;//!<
	public:
		BmpFont() :
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
		/** 0の場合、改行後の上下がくっつく*/
		void SetEnterHeight(int 改行の高さ)
		{
			this->enterSpace = 改行の高さ;
		}

		/** 数字フォントを設定.*/
		/** 数字描画に使うImagePackを設定する\n*/
		/**	0～9の順に10個並べた画像を使う*/
		bool SetNumber(ImagePack* 数字用イメージ)
		{
			if (数字用イメージ->GetSize() < 10) return false;

			divImageNumber = 数字用イメージ;

			numberWidth = 数字用イメージ->GetWidth();
			numberHeight = 数字用イメージ->GetHeight();
			spaceWidth = 数字用イメージ->GetWidth();

			maxHeight = std::max(maxHeight, 数字用イメージ->GetHeight());
			isNumber = true;

			return true;
		}

		/** 英大文字フォントをセット.*/
		/** 英大文字に使うImagePackを設定する\n*/
		/**	A～Zの順に26個並べた画像を使う*/
		bool SetAlphabetCapital(ImagePack* 大文字用イメージ)
		{
			if (大文字用イメージ->GetSize() < 26) return false;

			this->divImageAlphabetCapital = 大文字用イメージ;

			this->alphabetCapitalWidth = 大文字用イメージ->GetWidth();
			this->alphabetCapitalHeight = 大文字用イメージ->GetHeight();
			this->spaceWidth = 大文字用イメージ->GetWidth();

			this->maxHeight = std::max(this->maxHeight, 大文字用イメージ->GetHeight());

			this->isAlphabetCapital = true;

			return true;
		}

		/** 英小文字フォントをセット.*/
		/** 英小文字に使うImagePackを設定する\n*/
		/**	A～Zの順に26個並べた画像を使う*/
		bool SetAlphabetLow(ImagePack* 小文字用イメージ)
		{
			if (小文字用イメージ->GetSize() < 26) return false;

			divImageAlphabetLow = 小文字用イメージ;

			alphabetLowWidth = 小文字用イメージ->GetWidth();
			alphabetLowHeight = 小文字用イメージ->GetHeight();
			spaceWidth = 小文字用イメージ->GetWidth();

			maxHeight = std::max(maxHeight, 小文字用イメージ->GetHeight());

			isAlphabetLow = true;
			return true;
		}

		/** 書式付きで文字を描画.*/
		bool Draw(const Point &座標, Color 描画色, VariadicStream 描画する文字列) const override
		{
			Screen::SetBright(描画色);

			for (auto it : 描画する文字列.StringS)
			{
				int a = 0;
				int addX = 0;
				int addY = this->maxHeight;
				const char* bufstr = it.c_str();

				while (bufstr[a] != 0)//終端なら終了
				{
					if (bufstr[a] >= '0' && bufstr[a] <= '9' && this->isNumber)
					{
						divImageNumber[0][bufstr[a] - '0']->DrawExtend(
						{ 座標.x + addX,
						座標.y + addY - this->numberHeight },
						{ 座標.x + addX + this->numberWidth,
						座標.y + addY });

						addX += this->numberWidth;
					}
					else if (bufstr[a] >= 'A' && bufstr[a] <= 'Z' && this->isAlphabetCapital)
					{
						divImageAlphabetCapital[0][bufstr[a] - 'A']->DrawExtend
							(
						{ 座標.x + addX,
						座標.y + addY - this->alphabetCapitalHeight },
						{ 座標.x + addX + this->alphabetCapitalWidth,
						座標.y + addY }
						);

						addX += this->alphabetCapitalWidth;
					}
					else if (bufstr[a] >= 'a' && bufstr[a] <= 'z' && this->isAlphabetLow)
					{
						divImageAlphabetLow[0][bufstr[a] - 'a']->DrawExtend
							(
						{ 座標.x + addX,
						座標.y + addY - this->numberHeight },
						{ 座標.x + addX + this->numberWidth,
						座標.y + addY }
						);

						addX += this->alphabetLowWidth;
					}
					else if (bufstr[a] == ' ')
					{
						addX += spaceWidth;
					}
					++a;
					if (a == strlen(bufstr)) break;
				}
				addY += maxHeight + enterSpace;
			}

			Screen::SetBright(Color::White);
			return true;
		}

		/** 文字を回転して描画[未実装].@todo*/ 
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, Color 描画色, bool 反転フラグ, VariadicStream 描画する文字列) const override
		{
			return false;
		}

		/** 拡大率を指定して文字を描画.*/
		bool DrawExtend(const Point &座標, double X拡大率, double Y拡大率, Color 描画色, VariadicStream 描画する文字列) const override
		{
			for (auto it : 描画する文字列.StringS)
			{
				int a = 0;
				int addX = 0;
				int addY = this->maxHeight;
				const char* bufstr = it.c_str();

				Screen::SetBright(描画色);

				while (bufstr[a] != 0)
				{
					if (bufstr[a] >= '0' && bufstr[a] <= '9' && this->isNumber)
					{
						this->divImageNumber[0][bufstr[a] - '0']->DrawExtend
							(
						{ 座標.x + int(addX * X拡大率),
						座標.y + int((addY - this->numberHeight) * Y拡大率) },
						{ 座標.x + int((addX + this->numberWidth) * X拡大率),
						座標.y + int(addY * Y拡大率) }
						);

						addX += this->numberWidth;
					}
					else if (bufstr[a] >= 'A' && bufstr[a] <= 'Z' && this->isAlphabetCapital)
					{
						this->divImageAlphabetCapital[0][bufstr[a] - 'A']->DrawExtend
							(
						{ 座標.x + int(addX * X拡大率),
						座標.y + int((addY - this->alphabetCapitalHeight) * Y拡大率) },
						{ 座標.x + int((addX + this->alphabetCapitalWidth) * X拡大率),
						座標.y + int(addY * Y拡大率) }
						);

						addX += this->alphabetCapitalWidth;
					}
					else if (bufstr[a] >= 'a' && bufstr[a] <= 'z' && this->isAlphabetLow)
					{
						this->divImageAlphabetLow[0][bufstr[a] - 'a']->DrawExtend
							(
						{ 座標.x + int(addX * X拡大率),
						座標.y + int((addY - this->alphabetLowHeight) * Y拡大率) },
						{ 座標.x + int((addX + this->alphabetLowWidth) * X拡大率),
						座標.y + int(addY * Y拡大率) }
						);

						addX += this->alphabetLowWidth;
					}
					else if (bufstr[a] == ' ')
					{
						addX += this->spaceWidth;
					}
					++a;
					if (a == strlen(bufstr)) break;
				}
				addY += this->maxHeight + this->enterSpace;
			}

			Screen::SetBright(Color::White);

			return true;
		}
	};
}