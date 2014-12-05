//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include "Utility/IMotion.h"
namespace SDX
{
	/** 2D用に座標変換を行うカメラを表すクラス.*/
	/** @todo グローバルな機能として設計中*/
	/** \include Camera.h*/
	class Camera
	{
	//●影響があるクラスと関数
	//[Renderer/Screen]<OK>
	//SetArea
	//SetClip
	//[Drawing]<OK>
	//Line
	//Rect
	//Circle
	//Oval
	//Polygon
	//Triangle
	//Pixel
	//[Image]<OK>
	//Draw～6種
	//
	//●間接的に影響
	//[Font]<OK>
	//Imageを利用
	//[BmpFrame]
	//Imageを利用
	//[Shape]<OK>
	//Drawingを利用
	//[Sprite]<OK>
	//ImageやDrawingを利用
	private:
		double angle;//!< 
		MOTION::IMotion<Point> *motion;

		static Camera* active;//!< 現在アクティブなカメラ
	public:
		Point position;//!< 中心の位置
		Point forcus;//!< Screen上の座標positonがWindow上のforcusに来るように補正をかける
		double zoom;//!< 拡大率、マイナスになると上下左右反転

		/** カメラの作成.*/
		/** 初期座標と拡大率を指定してカメラを初期化*/
		Camera(const Point &座標, double 拡大率) :
			position(座標),
			forcus(座標),
			zoom(拡大率),
			angle(0)
		{};

		/** 現在アクティブなカメラを取得.*/
		static Camera* Get()
		{
			return active;
		}

		/** 現在アクティブなカメラを設定.*/
		static void Set(Camera *アクティブにするCamera = nullptr)
		{
			active = アクティブにするCamera;
		}

		/** モーションに応じてカメラ位置の更新.*/
		void Update()
		{
			if (motion)
			{
				motion->Update(&position);
			}
		}

		/** カメラの位置と拡大率に応じてX座標を変換.*/
		double TransX(double X座標変換前) const
		{
			return forcus.x + (X座標変換前 - position.x) * zoom;
		}

		/** カメラの位置と拡大率に応じてY座標を変換.*/
		double TransY(double Y座標変換前) const
		{
			return forcus.y + (Y座標変換前 - position.y) * zoom;
		}

		/** 座標を画面上のどこに表示されるか変換.*/
		Point Trans(const Point &変換前座標) const
		{
			return{ TransX(変換前座標.x) , TransY(変換前座標.y) };
		}

		/** 領域を画面上のどこに相当するか変換.*/
		SDL_Rect TransRect(const SDL_Rect &変換前矩形) const
		{
			return{ (int)TransX(変換前矩形.x), (int)TransY(変換前矩形.y), (int)(変換前矩形.w * zoom), (int)(変換前矩形.h *zoom) };
		}
	};
}
