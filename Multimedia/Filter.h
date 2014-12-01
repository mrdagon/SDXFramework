//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include<Multimedia/SDX.h>
#include<Multimedia/Image.h>
#include<Framework/ImagePack.h>

namespace SDX
{
	/** Imageにフィルター処理を行う関数群[未実装].*/ 
	/** ImageやImagePackに対して画像編集ソフトにあるようなフィルター処理を施す。*/
	/** \include Filter.h*/
	/** @todo OpenGLが必要なので、実装予定無し*/
	class Filter
	{
	public:
		/** モノトーンフィルタ.*/
		/** 画像をモノトーン調に変化させる。\n*/
		/** 各ピクセルの色をRGB形式からYCbCr形式に変換して、その上ですべてのピクセルの輝度以外の成分を\n*/
		/** 引数の Cb Cr の値を置き換えた後、再びＲＧＢ形式に戻す。\n*/
		/** 値の調整が難しいが、似たような効果を得ることができる Filter::Hsb より負荷は低い。\n*/
		/** 赤色差と青色差は-255～255で指定する。*/
		static bool Mono(Image *処理イメージ, int 青色差, int 赤色差)
		{
			return false;
		}
		static bool Mono(ImagePack &処理イメージ郡, int 青色差, int 赤色差)
		{
			for (auto it : 処理イメージ郡)
			{
				Mono(it, 青色差, 赤色差);
			}
			return false;
		}
		static Image MonoMake(Image *処理イメージ, int 青色差, int 赤色差)
		{
			Image image = 処理イメージ->Clone();
			Mono( &image, 青色差, 赤色差);
			return image;
		}

		/** ガウスフィルタ.*/
		/** 画像にガウス関数を使用したぼかし効果を与える。\n*/
		/** 使用ピクセル幅は 8 か 16 か 32で指定。\n*/
		/** ぼかし強さは 1 で約1ピクセル幅ぼかす。\n*/
		/** \n*/
		/** ぼかしの限界は 使用ピクセル幅 で決まり、値が大きいほどぼかしの強さの限界が大きくなり、\n*/
		/** それとともに処理負荷も大きくなる。\n*/
		/** このフィルタは非常に負荷が大きいので、強いぼかしをかけたい場合は 使用ピクセル の値を 32 にして強いぼかしを\n*/
		/** 掛けるより、縮小フィルタ( DX_GRAPH_FILTER_DOWN_SCALE )で画像を縮小した後弱いぼかしを掛け、\n*/
		/** その後 DrawExtend で元の大きさで描画する、という方法を採ったほうが処理負荷を小さく抑えることができます。*/
		static bool Gauss(Image* 処理イメージ, int 使用ピクセル幅, double ぼかし強さ)
		{
			return false;
		}
		static bool Gauss(ImagePack *処理イメージ郡, int 使用ピクセル幅, double ぼかし強さ)
		{
			return false;
		}

		/** 縮小フィルタ.*/
		/** 分母は 2 か 4 か 8 を指定\n*/
		/**	画像を分母で指定した数で割って縮小する。\n*/
		/**	DrawExtend でも縮小描画することができるが、それよりも綺麗に縮小した画像を得ることができる。\n*/
		/**	主にFilter::Gaussの処理負荷を下げる目的で使用されることを想定している。*/
		static bool DownScale(Image* 処理イメージ, int 分母)
		{
			return false;
		}
		static bool DownScale(ImagePack *処理イメージ郡, int 分母)
		{
			return false;
		}

		/** 明るさクリップフィルタ.*/
		/** 画像の各ピクセルを輝度に応じて引数で渡す色で塗りつぶす。\n*/
		/** クリップタイプがClipType::Lessの場合、クリップパラメータより輝度が小さいピクセル、\n */
		/** クリップタイプがClipType::Graterの場合、輝度が大きいピクセルをクリップ処理する。\n */
		/** クリップ判定されたピクセルは、クリップ色で塗られ、αチャンネルがある場合α値をクリップαにする。*/
		static bool BrightClip(Image* 処理イメージ, ClipType cmpType, int cmpParam, int clipFillColor, int clipFillAlpha)
		{
			return false;
		}
		static bool BrightClip(ImagePack *処理イメージ郡, ClipType cmpType, int cmpParam, int clipFillColor, int clipFillAlpha)
		{
			return false;
		}

		/** 色相・彩度・明度フィルタ.*/
		/** 画像の各ピクセルの、色相、彩度、明度を補正する。\n*/
		/**	色相は-180～180で指定し、相対的に変化させます\n*/
		/**	彩度 -1.0～で指定し、相対的に変化させます、-1でグレー、0で変化なし。\n*/
		/**	明度 -1.0～1.0で指定し、負の場合暗く、正の場合は明るくなる。*/
		static bool Hsb(Image* 処理イメージ, int 色相, double 彩度, double 明度)
		{
			return false;
		}
		static bool Hsb(ImagePack *処理イメージ郡, int 色相, double 彩度, double 明度)
		{
			return false;
		}

		/** 色相・彩度・明度フィルタ.*/
		/** 画像の各ピクセルの、色相、彩度、明度を補正する。\n*/
		/**	色相は0～360で指定、120が緑、240で青、360が赤になる。\n*/
		/**	絶対値で指定するので、モノトーン調の処理になる。\n*/
		/**	彩度と明度は、Filter::Hsbと同じ。*/
		static bool MonoHsb(Image* 処理イメージ, int 色相, double 彩度, double 明度)
		{
			return false;
		}
		static bool MonoHsb(ImagePack *処理イメージ郡, int 色相, double 彩度, double 明度)
		{
			return false;
		}

		/** 階調反転フィルタ.*/
		/** 各ピクセルのRGB値を反転する。*/
		bool Invert(Image* 処理イメージ)
		{
			return false;
		}
		bool Invert(ImagePack *処理イメージ郡)
		{
			return false;
		}

		/** レベル補正フィルタ.*/
		/** 画像にレベル補正を行い、コントラストを調整する。\n*/
		/**	処理前下限、0以上にすると暗くなります。\n*/
		/**	処理前上限、255以下にすると、明るくなります。\n*/
		/**	処理後下限、0以上にすると白っぽくなります。\n*/
		/**	処理後上限、255以下にすると黒に近くなります\n*/
		/**	ガンマ値は1以上にすると、明るくなり、1以下にすると暗くなります。*/
		bool Level(Image* 処理イメージ, int 処理前下限, int 処理前上限, int 処理後下限, int 処理後上限, double ガンマ値)
		{
			return false;
		}
		bool Level(ImagePack *処理イメージ郡, int 処理前下限, int 処理前上限, int 処理後下限, int 処理後上限, double ガンマ値)
		{
			return false;
		}

		/** ２階調フィルタ.*/
		/** 各ピクセルの輝度が閾値より暗いか明るいかで各ピクセルを変換する*/
		bool TwoColor(Image* 処理イメージ, int 閾値, int 暗色, int 暗色α値, int 明色, int 明色α値)
		{
			return false;
		}
		bool TwoColor(ImagePack *処理イメージ郡, int 閾値, int 暗色, int 暗色α値, int 明色, int 明色α値)
		{
			return false;
		}

		/** グラデーションマップフィルタ.*/
		/** 各ピクセルの輝度からグラデーションマップのＸ座標を算出し変換する。\n*/
		/**	輝度が0の場合はグラデーションマップの一番左上のピクセルの色が( x:0 y:0 座標のピクセル )、\n*/
		/**	輝度が255( 最大 )の場合、グラデーションマップの一番右上のピクセルの色が( x:255 y:0 座標のピクセル )*/
		/**	出力結果の色になる。*/
		bool GradientMap(Image* 処理イメージ, const Image *入力イメージ, bool 反転フラグ)
		{
			return false;
		}
		bool GradientMap(ImagePack *処理イメージ郡, const Image *入力イメージ, bool 反転フラグ)
		{
			


			return false;
		}
	};
}
