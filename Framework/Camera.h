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
	//影響があるクラス
	//[Renderer]SetArea,SetClip,回転が効かないので影響無しにしても良さそう
	//[Drawing]色々
	//[Image]色々
	//[Input]影響無し
	//[Font]imageから間接的に影響
	//[BmpFrame]imageから間接的に影響(継ぎ目がある?)
	//[Shape]Drawingから間接的に影響
	//[Sprite]ImageやDrawingから間接的に影響(継ぎ目がある？)再実装が必要
	private:
		Point position;//!< 中心の位置
		Point forcus;//!< Screen上の座標positonがWindow上のforcusに来るように補正をかける
		double zoom;//!< 
		double angle;//!< 

		MOTION::IMotion<Point> *motion;

		static Camera* active;//!< 現在アクティブなカメラ
	public:
		/** カメラの作成.*/
		/** 初期座標と拡大率を指定してカメラを初期化*/
		Camera(const Point &座標, double 拡大率) :
			position(座標),
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

		/** 中心座標を設定.*/
		void SetPos(const Point &座標)
		{
			position = 座標;
		}

		/** 中心座標を取得*/
		Point GetPos()
		{
			return position;
		}

		/** 焦点座標を設定.*/
		void SetForcus(const Point &座標)
		{
			forcus = 座標;
		}

		/** 焦点座標を設定.*/
		Point GetForcus()
		{
			return forcus;
		}

		/** 拡大率を設定.*/
		void SetZoom(double 拡大率)
		{
			zoom = 拡大率;
		}

		/** 拡大率を取得.*/
		double GetZoom()
		{
			return this->zoom;
		}

		/** 焦点のX座標を取得.*/
		double GetX()
		{
			return position.x;
		}

		/** 焦点のY座標を取得.*/
		double GetY()
		{
			return position.y;
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
		double TransX(double X座標変換前)
		{
			return forcus.x + (X座標変換前 - position.x) * zoom;
		}

		/** カメラの位置と拡大率に応じてY座標を変換.*/
		double TransY(double Y座標変換前)
		{
			return forcus.y + (Y座標変換前 - position.y) * zoom;
		}

		/** 座標を画面上のどこに表示されるか変換.*/
		Point Trans(const Point &変換前座標)
		{
			return{ TransX(変換前座標.x) , TransY(変換前座標.y) };
		}

		/** 領域を画面上のどこに相当するか変換.*/
		SDL_Rect TransRect(const SDL_Rect &変換前矩形)
		{
			return{ 0, 0, 0, 0 };
		}
	};
}
