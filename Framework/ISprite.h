//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Image.h>
#include <Framework/Camera.h>
#include <Multimedia/Screen.h>
#include <Multimedia/Input.h>
#include <Multimedia/Font.h>
#include <Framework/BmpFrame.h>
#include <memory>

namespace SDX
{
	/*! 2Dモデルに貼り付けるスプライトを表す抽象クラス.*/
	/*!    \include ModelSample.h */
	class ISprite
	{
		friend class IModel;

	protected:
		double    zoomX = 1;
		double    zoomY = 1;

		double    gapX = 0;//中心モデルとの位置差
		double    gapY = 0;

		double    axisX = 0;//回転軸
		double    axisY = 0;

		Color    color = { 255, 255, 255, 255 };
		double    angle = 0;

	public:
		bool isTurn = false;

		ISprite(){}

		virtual ~ISprite(){};

		/*! ISpriteを描画する.*/
		virtual void Draw(const Point &座標, bool カメラフラグ) = 0;

		/*! Shapeとの相対座標を移動.*/
		void MoveGap(double X移動量, double Y移動量)
		{
			gapX += X移動量;
			gapY += Y移動量;
		}

		/*! Shapeとの相対座標を指定.*/
		void SetGap(const Point &座標)
		{
			gapX = 座標.x;
			gapY = 座標.y;
		}

		/*! 表示倍率を設定.*/
		void SetZoom(double X拡大率, double Y拡大率)
		{
			zoomX = X拡大率;
			zoomY = Y拡大率;
		}

		/*! 拡大率を掛け算する.*/
		void MultiZoom(double 倍率)
		{
			MultiZoom(倍率, 倍率);
		}

		/*! 縦横別で拡大率を掛け算する.*/
		void MultiZoom(double X倍率, double Y倍率)
		{
			zoomX *= X倍率;
			zoomY *= Y倍率;

			gapX *= X倍率;
			gapY *= Y倍率;

			axisX *= X倍率;
			axisY *= Y倍率;
		}

		/*! 横方向の表示倍率を取得.*/
		double GetZoomX()
		{
			return this->zoomX;
		}

		/*! 縦方向の表示倍率を取得.*/
		double GetZoomY()
		{
			return this->zoomY;
		}

		/*! 左右反転フラグを設定.*/
		void SetTurn(bool 反転フラグ)
		{
			this->isTurn = 反転フラグ;
		}

		/*! 左右反転フラグを取得.*/
		bool GetTurn()
		{
			return this->isTurn;
		}

		/*! 表示角度を取得.*/
		double GetAngle()
		{
			return this->angle;
		}

		/*! 表示角度を設定.*/
		void SetAngle(double 角度)
		{
			this->angle = 角度;
		}

		/*! 回転させる.*/
		void Rotate(double 回転する角度)
		{
			this->angle += 回転する角度;
		}

		/*! 描画色を取得.*/
		Color GetColor()
		{
			return color;
		}

		/*! 透明度を0～255で設定.*/
		void SetColor(Color 描画色)
		{
			color = 描画色;
		}

		/*! 説明.*/
		virtual void AnimeUpdate(){};
	};
}