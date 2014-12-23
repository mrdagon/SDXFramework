//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Sprite.h>
#include <Framework/Shape.h>

namespace SDX
{
	/** ShapeとSpriteをまとめて、2Dモデルを表すクラス.*/
	/** \include Model.h*/
	class IModel : public IPosition
	{
	private:
		double angle = 0;//!<
		double shadowSize = 1;//!<
	protected:
		bool isRemove = false;//!< 消滅フラグ
	public:
		IShape &iShape;//!< 対応Shape
		ISprite &iSprite;//!< 対応Sprite

		/** コンストラクタ.*/
		IModel(IShape &図形, ISprite &描画方法) :
			iShape(図形),
			iSprite(描画方法)
		{}
		
		virtual ~IModel() = default;

		/** 消滅フラグの取得.*/
		bool GetRemoveFlag() const
		{
			return isRemove;
		}

		/** 更新処理を行う.*/
		virtual void Update(){}

		/** 影の大きさを設定.*/
		void SetShadowSize(double 影の表示倍率)
		{
			shadowSize = 影の表示倍率;
		}

		/** 描画する.*/
		virtual void Draw() const
		{
			iSprite.Draw( iShape );

			//当たり判定を表示するならコメントアウト解除
			//iShape.Draw({255,0,0,128} );
		}

		/** 影を描画する.*/
		void DrawShadow(double X座標ずれ, double Y座標ずれ)
		{
			if (shadowSize <= 0) return;

			X座標ずれ *= shadowSize;
			Y座標ずれ *= shadowSize;

			double zoomX = iSprite.zoomX;
			double zoomY = iSprite.zoomY;
			iSprite.zoomX *= shadowSize;
			iSprite.zoomY *= shadowSize;

			iSprite.gap.Move(X座標ずれ,Y座標ずれ);
			iSprite.Draw( iShape);
			iSprite.gap.Move(-X座標ずれ, -Y座標ずれ);

			iSprite.zoomX = zoomX;
			iSprite.zoomY = zoomY;
		}

		/** 指定座標に移動.*/
		void SetPos(double X座標, double Y座標) override
		{
			iShape.SetPos(X座標, Y座標);
		}

		/** 縦横別で拡大率を掛ける.*/
		void MultiZoom(double X倍率, double Y倍率) override
		{
			zoomX *= X倍率;
			zoomY *= Y倍率;

			iShape.MultiZoom(X倍率, Y倍率);
			iSprite.MultiZoom(X倍率, Y倍率);
		}
		
		/** 相対座標で移動.*/
		void Move(double X移動量, double Y移動量) override
		{
			iShape.Move(X移動量, Y移動量);
		}

		/** 回転させる.*/
		void Rotate(double 回転角度) override
		{
			angle += 回転角度;
			iSprite.Rotate(回転角度);
			iShape.Rotate(回転角度);
		}

		/** 角度を取得する.*/
		double GetAngle() const override
		{
			return angle;
		}

		/** X座標を取得.*/
		double GetX() const override
		{
			return iShape.GetX();
		}

		/** Y座標を取得.*/
		double GetY() const override
		{
			return iShape.GetY();
		}

		/** X座標を取得.*/
		double GetW() const override
		{
			return iShape.GetW();
		}

		/** Y座標を取得.*/
		double GetH() const override
		{
			return iShape.GetH();
		}

		/** 色をまとめて変更する、透明度も含む.*/
		void SetColor(const Color &描画色)
		{
			iSprite.color = 描画色;
		}

		/** 横方向の拡大率を取得.*/
		double GetZoomX() const
		{
			return zoomX;
		}

		/** 縦方向の拡大率を取得.*/
		double GetZoomY() const
		{
			return zoomY;
		}

		/** Modelとの衝突判定.*/
		bool Hit(const IModel *判定を行うModel) const
		{
			return iShape.Hit(&判定を行うModel->iShape);
		}

		/** Shapeとの衝突判定.*/
		bool Hit(const IShape *判定を行うShape) const
		{
			return iShape.Hit(判定を行うShape);
		}
	};
}