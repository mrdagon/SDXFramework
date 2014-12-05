//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <SDXFramework.h>
#include <Utility/IMotion.h>
#include <Framework/Shape.h>

namespace SDX
{
	namespace MOTION
	{
		/*
		//コピペ用ひな形
		template <class TSpeed>
		class Base : public IMotion
		{
		MOTION_BASE
		public:
		Base(const TSpeed &速度):
		speed(速度)
		{}

		void Update(IModel* 移動対象)
		{
		移動対象
		}
		};
		*/


		template <class TSpeed, class TShape>
		/**前方に移動.*/
		/** \include Motion.h */
		class ToFront : public IMotion<TShape>
		{
		private:
			TSpeed speed;
		public:

			/** 速度を指定.*/
			ToFront(TSpeed 速度) :
				speed(速度)
			{}

			bool Update(TShape* 移動対象) override
			{
				移動対象->MovePolar(speed.Update(), 移動対象->GetAngle());

				return true;
			}
		};

		template <class TSpeed, class TShape>
		/**範囲内で跳ね返る.*/
		/** \include Motion.h */
		class Bound : public IMotion<TShape>
		{
		private:
			TSpeed speed;
			double 進行方向;
			Rect 移動範囲;
		public:

			/** 速度と移動範囲、最初の移動方向を指定.*/
			Bound(const TSpeed &速度, const Rect& 移動範囲, double 進行方向) :
				speed(速度),
				移動範囲(移動範囲)
			{}

			bool Update(TShape* 移動対象) override
			{
				//範囲外にいる
				if (移動対象->GetX() < 移動範囲.GetLeft())
				{
					if (進行方向 > PAI / 2 && 進行方向 < PAI * 3 / 2)
					{
						進行方向 = -PAI - 進行方向;
					}
				}

				if (移動対象->GetX() > 移動範囲.GetRight())
				{
					if (進行方向 < PAI / 2 || 進行方向 > PAI * 3 / 2)
					{
						進行方向 = PAI - 進行方向;
					}
				}
				else if (移動対象->GetY() < 移動範囲.GetTop())
				{
					if (進行方向 > PAI)
					{
						進行方向 = PAI * 2 - 進行方向;
					}
				}
				else if (移動対象->GetY() > 移動範囲.GetBottom())
				{
					if (進行方向 < PAI)
					{
						進行方向 = -進行方向;
					}
				}

				if (進行方向 < 0) 進行方向 += PAI * 2;
				if (進行方向 > PAI * 2) 進行方向 -= PAI * 2;

				移動対象->MovePolar(speed.Update(), 進行方向);

				return true;
			}
		};

		template <class TSpeed, class TShape>
		/**目標座標に移動.*/
		/** \include Motion.h */
		class ToPoint : public IMotion<TShape>
		{
		private:
			TSpeed speed;
			Point 目標座標;
		public:
			/** コンストラクタ.*/
			ToPoint(const TSpeed &速度, const Point& 目標座標) :
				speed(速度),
				目標座標(目標座標)
			{}

			bool Update(TShape* 移動対象) override
			{
				//移動対象
				const double nowSpeed = speed.Update();
				const double lx = 目標座標.GetX() - 移動対象->GetX();
				const double ly = 目標座標.GetY() - 移動対象->GetY();

				if (lx * lx + ly * ly <= nowSpeed * nowSpeed)
				{
					移動対象->SetPos(目標座標.GetX(), 目標座標.GetY());
					return false;
				}
				else
				{
					const double angle = atan2(ly, lx);
					移動対象->MovePolar(nowSpeed, angle);
				}

				return true;
			}
		};

		template <class TSpeed, class TShape>
		/**円周上を移動.*/
		/** \include Motion.h */
		class Orbit : public IMotion<TShape>
		{
		private:
			TSpeed speed;
			Point 軌道中心;
			double 角度;
			double 半径X;
			double 半径Y;

			Point 前座標;
		public:

			/** コンストラクタ.*/
			Orbit(const TSpeed &速度) :
				speed(速度),
				前座標(0, 0)
			{}

			bool Update(TShape* 移動対象) override
			{
				//移動対象
				角度 += speed.Update();

				const double nextX = cos(角度) * 半径X;
				const double nextY = sin(角度) * 半径Y;

				移動対象->Move(nextX - 前座標.GetX(), nextY - 前座標.GetX());

				前座標.SetPos(nextX, nextY);

				return true;
			}
		};

		template <class TShape>
		/**範囲内で振動.*/
		/** \include Motion.h */
		class  Vibrate : public IMotion<TShape>
		{
		private:
			double 最大振れ幅;
			double 前振れ幅X = 0;
			double 前振れ幅Y = 0;
		public:

			/** コンストラクタ.*/
			Vibrate(double 最大振れ幅) :
				最大振れ幅(最大振れ幅)
			{}

			bool Update(TShape* 移動対象) override
			{
				//移動対象
				double 振れ幅 = 最大振れ幅;
				前振れ幅X = Rand::Get(-振れ幅, 振れ幅) - 前振れ幅X;
				前振れ幅X = Rand::Get(-振れ幅, 振れ幅) - 前振れ幅X;
				移動対象->Move(前振れ幅X, 前振れ幅Y);
				return true;
			}
		};
	}
}