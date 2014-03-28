#pragma once//☀DXLIB
#include<Multimedia/Image.h>

namespace SDX
{
/** Image同士の合成処理を行う関数群[DXLIB].*/
/** 合成元のイメージに入力イメージを合成し、画像編集ソフトにあるような合成処理を施す。\n
	合成率は0.0～1.0の範囲で指定し、率が高い程入力の影響が強くなる。\n
	\include BlendSample.h*/
class Blend
{
public:
	/** 加算合成.*/
	/** 合成イメージに入力イメージの色を足す。*/
	bool Add( Image* 合成イメージ , const Image *入力イメージ ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend(合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_ADD);
	}
			
	/** 焼き込み合成.*/
	/**	合成して暗くする。\n
		[計算方法]\n
		合成後の色 = 1.0 - ( 1.0 -  合成元の色 ) / 入力の色\n
		※入力の色が0.0の時、合成後の色は0.0*/
	bool Burn( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend(合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_BURN);
	}

	/** 比較合成(暗).*/
	/** 合成と入力の暗い方を合成後の色にする。*/
	bool Darken( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend(合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_DARKEN);
	}
			
	/** 減算合成.*/
	/** 合成イメージから、入力イメージを減算する。*/
	bool Difference( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend(合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_DIFFERENCE);
	}
			
	/** 覆い焼き合成.*/
	/** 合成後、明るくする。\n
		[計算方法]\n
		合成後の色 = 合成元の色 / (1.0 - 入力の色)\n
		※入力の色が1.0の場合、合成後の色は1.0*/
	bool Dodge( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend(合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_DODGE);
	}
			
	/** 除外合成.*/
	/** 合成後、暗くする。\n
		[計算方法]\n
		合成後 = 合成元 + 入力 - 2.0 * 合成元 * 入力*/
	bool Exclusion( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend(合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_EXCLUSION);
	}
			
	/** ハードライト合成.*/
	/** オーバーレイ合成の条件を、合成元から入力に変更して計算。*/
	bool HardLight( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend(合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_HARDLIGHT);
	}
			
	/** 比較合成(明).*/
	/** 合成と入力の明るい方を合成後の色にする。*/
	bool Lighten( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend( 合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_LIGHTEN);
	}
			
	/** 乗算合成.*/
	/**	二つのイメージの色を乗算する。\n
		各成分は0.0～1.0の値に見立てて乗算を行うので、\n
		元の色より暗くなる事はあっても明るくなることはない。*/
	bool Multiple( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend( 合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_MULTIPLE);
	}
			
	/** 通常合成.*/
	/** 特殊な効果を付けずに合成\n
		合成率が1に近いほど、入力画像の不透明度が高くなる。*/
	bool Normal( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend( 合成イメージ->GetHandle() , 入力イメージ->GetHandle() , (int)(合成率*255) ,DX_GRAPH_BLEND_NORMAL);
	}
			
	/** オーバーレイ合成.*/
	/** 合成イメージの色が0.5以下の部分は暗く、それ以外は明るくする合成。\n
		[計算方法]\n
		GrHandleの色が0.5以下:\n
		合成後の色 = 合成元の色 * 入力の色 * 2.0\n
		それ以外:\n
		合成後の色 = 2.0 * ( 合成元の色 + 入力の色 - 合成元の色 * 入力の色 ) - 1.0*/
	bool OverLay( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend( 合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_OVERLAY);
	}
			
	/** RGBAの要素を選択して合成.*/
	/**	合成後の画像として赤・緑・青・アルファの各成分を 合成元、入力のどちらのどの要素から取るかを指定する。\n
		例えば、赤要素 に RGBA::BlendR を指定した場合は、合成後の画像の赤成分は、入力イメージの緑成分になる。*/
	bool RgbaSelectMix( Image* 合成イメージ , const Image *入力イメージ, RGBA 赤要素 , RGBA 緑要素 , RGBA 青要素 , RGBA 透明要素 ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend( 合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_RGBA_SELECT_MIX, 赤要素 , 緑要素 , 青要素 , 透明要素 );
	}
			
	/** スクリーン合成.*/
	/** 加算合成のように明るくする。\n
		[計算方法]\n
		合成後の色 = 1.0f - ( ( 1.0f - 合成イメージの色 ) * ( 1.0f - 入力イメージの色 ) )*/
	bool Screen( Image* 合成イメージ , const Image *入力イメージ,double 合成率 = 1.0)
	{
		return !DxLib::GraphBlend( 合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_SCREEN);
	}
			
	/** ソフトライト合成.*/
	/** 合成イメージの色が0.5以下の部分は暗く、それ以外は明るくする合成。\n
		[計算方法]\n
		GrHandleの色が0.5以下:\n
		合成後の色 = pow( 合成元, ( 1.0f - 入力 ) * 2.0 )\n
		それ以外:\n
		合成後の色 = pow( 合成元, 0.5 / 入力 )*/
	bool SoftLight( Image* 合成イメージ , const Image *入力イメージ,double 合成率)
	{
		return !DxLib::GraphBlend( 合成イメージ->GetHandle() , 入力イメージ->GetHandle(),int(合成率*255),DX_GRAPH_BLEND_SOFTLIGHT);
	}
};

/** イメージを合成して合成.*/
/** Blendクラスを参照。\n
	２つのイメージを特殊効果付きでブレンドし、イメージのハンドルを返す。\n
	\include*/
class BlendBlt
{
public:
	/** 説明.*/
	static Image Add(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width  = std::max( 合成元A->GetWidth() , 合成元B->GetWidth() );
		const int height = std::max( 合成元A->GetHeight() , 合成元B->GetHeight() );
		Image outPut( width , height , true , true , true );
		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_ADD);

		return outPut;
	}
	static Image Add(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width  = std::max( 合成元A->GetWidth() , 合成元B->GetWidth() );
		const int height = std::max( 合成元A->GetHeight() , 合成元B->GetHeight() );
		Image outPut( width , height , true , true , true );
		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_ADD);

        return outPut;
	}
		
	/** 説明.*/
	static Image Burn(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_BURN);

		return outPut;
	}
	static Image Burn(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

        DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_BURN);

		return outPut;
	}
		
	/** 説明.*/
	static Image Darken(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_DARKEN);

		return outPut;
	}
	static Image Darken(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_DARKEN);

		return outPut;
	}
		
	/** 説明.*/
	static Image Diference(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_DIFFERENCE);

		return outPut;
	}
	static Image Difference(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_DIFFERENCE);

		return outPut;
	}
		
	/** 説明.*/
	static Image Dodge(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_DODGE);

		return outPut;
	}
	static Image Dodge(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_DODGE);

		return outPut;
	}
		
	/** 説明.*/
	static Image Exclusion(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_EXCLUSION);

		return outPut;
	}
	static Image Exclusion(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_EXCLUSION);

		return outPut;
	}
		
	/** 説明.*/
	static Image HardLight(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_HARDLIGHT);

		return outPut;
	}
	static Image HardLight(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_HARDLIGHT);

		return outPut;
	}
		
	/** 説明.*/
	static Image Lighten(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_LIGHTEN);

		return outPut;
	}
	static Image Lighten(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_LIGHTEN);

		return outPut;
	}
		
	/** 説明.*/
	static Image Multiple(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_MULTIPLE);

		return outPut;
	}
	static Image Multiple(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_MULTIPLE);

		return outPut;
	}
	
	/** 説明.*/
	static Image Normal(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_NORMAL);

		return outPut;
	}
	static Image Normal(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_NORMAL);

		return outPut;
	}
		
	/** 説明.*/
	static Image OverLay(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_OVERLAY);

		return outPut;
	}
	static Image OverLay(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_OVERLAY);

		return outPut;
	}
		
	/** 説明.*/
	static Image RgbaSelectMix(const Image *合成元A,const Image *合成元B,double 合成率, RGBA selectR , RGBA selectG , RGBA selectB , RGBA selectA)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_RGBA_SELECT_MIX, selectR , selectG , selectB , selectA );

		return outPut;
	}
	static Image RgbaSelect(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率, RGBA selectR , RGBA selectG , RGBA selectB , RGBA selectA)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_RGBA_SELECT_MIX, selectR , selectG , selectB , selectA );

		return outPut;
	}
		
	/** 説明.*/
	static Image Screen(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_SCREEN);

		return outPut;
	}
	static Image Screen(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_SCREEN);

		return outPut;
	}
		
	/** 説明.*/
	static Image SoftLight(const Image *合成元A,const Image *合成元B,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlend(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle(),int(合成率*255),DX_GRAPH_BLEND_SOFTLIGHT);

		return outPut;
	}
	static Image SoftLight(const Image *合成元A,const Image *合成元B, int srcX1, int srcY1, int srcX2, int srcY2, int blendX, int blendY, int destX, int destY,double 合成率)
	{
		const int width = std::max(合成元A->GetWidth(), 合成元B->GetWidth());
		const int height = std::max(合成元A->GetHeight(), 合成元B->GetHeight());
		Image outPut(width, height, true, true, true);

		DxLib::GraphBlendRectBlt(合成元A->GetHandle() , 合成元B->GetHandle() , outPut.GetHandle() , srcX1, srcY1, srcX2, srcY2, blendX, blendY, destX, destY,int(合成率*255),DX_GRAPH_BLEND_SOFTLIGHT);

		return outPut;
	}
};



}