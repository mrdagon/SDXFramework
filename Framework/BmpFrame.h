//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/ImagePack.h>
#include <Framework/IFrame.h>

namespace SDX
{
	/** 描画用枠を表すクラス.*/
	/** \include BmpFrame.h*/
	class BmpFrame : public IFrame
	{
	private:
		ImagePack *frame = nullptr;//!<
	public:

		BmpFrame() = default;

		/** フレームを作成する.*/
		/** フレーム画像は３×３分割した9マスの物が使える*/
		BmpFrame(ImagePack *フレーム画像)
		{
			Make(フレーム画像);
		}

		/** フレームを作成する.*/
		/** フレーム画像は３×３分割した9マスの物が使える*/
		bool Make(ImagePack *フレーム画像)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ Make(フレーム画像); });
				return true;
			}

			if (フレーム画像->GetSize() != 9) return false;
			frame = フレーム画像;

			return true;
		}

		/** 矩形のフレームを描画.*/
		/** 右上座標を指定してフレームを描画する*/
		void Draw(const Rect &領域) const
		{
			if (frame == nullptr){ return; }

			auto camera = Camera::Get();

			int width = frame->GetWidth();
			int height = frame->GetHeight();
			bool isMin = true;//枠が小さいため部分描画が必要フラグ
			int partW = width;
			int partH = height;
			int partLeft = 0;
			int partTop = 0;

			//外枠
			if (width * 2 > 領域.GetW())
			{
				width = (int)領域.GetW() / 2;
				partW = width;
				partLeft = frame->GetWidth() - width;
				isMin = true;
			}
			if (height * 2 > 領域.GetH())
			{
				height = (int)領域.GetH() / 2;
				partH = height;
				partTop = frame->GetHeight() - height;
				isMin = true;
			}

			if (camera)
			{
				Camera::Set();

				width = int(width * camera->zoom);
				height = int(height *camera->zoom);

				//カメラ補正有り
				int xA = (int)camera->TransX(領域.GetLeft());
				int xB = xA + width;
				int xD = (int)camera->TransX(領域.GetRight());
				int xC = xD - width;

				int yA = (int)camera->TransY(領域.GetTop());
				int yB = yA + height;
				int yD = (int)camera->TransY(領域.GetBottom());
				int yC = yD - height;

				//内側
				frame[0][4]->DrawExtend({ xB, yB, xC -xB, yC - yB });

				if (isMin)
				{
					frame[0][3]->DrawPartExtend({ xA, yB, width, yC - yB }, { 0, 0, width, height});//左
					frame[0][5]->DrawPartExtend({ xC, yB, width, yC - yB }, { partLeft, 0, width, height });//右

					frame[0][1]->DrawPartExtend({ xB, yA, xC - xB, height }, { 0, 0, width, height });//上
					frame[0][7]->DrawPartExtend({ xB, yC, xC - xB, height }, { 0, partTop, width, height });//下

					frame[0][0]->DrawPartExtend({ xA, yA, width, height }, { 0, 0, width, height });//左上
					frame[0][2]->DrawPartExtend({ xC, yA, width, height }, { partLeft, 0, width, height });//右上
					frame[0][6]->DrawPartExtend({ xA, yC, width, height }, { 0, partTop, width, height });//左下
					frame[0][8]->DrawPartExtend({ xC, yC, width, height }, { partLeft, partTop, width, height });//右下
				}
				else
				{
					frame[0][3]->DrawExtend({ xA, yB, width, yC - yB });//左
					frame[0][5]->DrawExtend({ xC, yB, width, yC - yB });//右

					frame[0][1]->DrawExtend({ xB, yA, xC - xB, height });//上
					frame[0][7]->DrawExtend({ xB, yC, xC - xB, height });//下

					frame[0][0]->DrawExtend({ xA, yA, width, height });//左上
					frame[0][2]->DrawExtend({ xC, yA, width, height });//右上
					frame[0][6]->DrawExtend({ xA, yC, width, height });//左下
					frame[0][8]->DrawExtend({ xC, yC, width, height });//右下
				}

				Camera::Set(camera);
			}
			else
			{
				//カメラ補正無し
				int xA = (int)領域.GetLeft();
				int xB = (int)領域.GetLeft() + width;
				int xC = (int)領域.GetRight() - width;
				int yA = (int)領域.GetTop();
				int yB = (int)領域.GetTop() + height;
				int yC = (int)領域.GetBottom() - height;

				//内側
				frame[0][4]->DrawExtend({ xB, yB, 領域.GetW() - width * 2, 領域.GetH() - height * 2 });

				if (isMin)
				{
					//外枠
					frame[0][3]->DrawPartExtend({ xA, yB, width, 領域.GetH() - height * 2 }, { 0, 0, width, height });//左
					frame[0][5]->DrawPartExtend({ xC, yB, width, 領域.GetH() - height * 2 }, { partLeft, 0, width, height });//右

					frame[0][1]->DrawPartExtend({ xB, yA, 領域.GetW() - width * 2, height }, { 0, 0, width, height });//上
					frame[0][7]->DrawPartExtend({ xB, yC, 領域.GetW() - width * 2, height }, { 0, partTop, width, height });//下

					frame[0][0]->DrawPartExtend({ xA, yA, width, height }, { 0, 0, width, height });//左上
					frame[0][2]->DrawPartExtend({ xC, yA, width, height }, { partLeft, 0, width, height });//右上
					frame[0][6]->DrawPartExtend({ xA, yC, width, height }, { 0, partTop, width, height });//左下
					frame[0][8]->DrawPartExtend({ xC, yC, width, height }, { partLeft, partTop, width, height });//右下
				}
				else
				{
					//外枠
					frame[0][3]->DrawExtend({ xA, yB, width, 領域.GetH() - height * 2 });//左
					frame[0][5]->DrawExtend({ xC, yB, width, 領域.GetH() - height * 2 });//右

					frame[0][1]->DrawExtend({ xB, yA, 領域.GetW() - width * 2, height });//上
					frame[0][7]->DrawExtend({ xB, yC, 領域.GetW() - width * 2, height });//下

					frame[0][0]->DrawExtend({ xA, yA, width, height });//左上
					frame[0][2]->DrawExtend({ xC, yA, width, height });//右上
					frame[0][6]->DrawExtend({ xA, yC, width, height });//左下
					frame[0][8]->DrawExtend({ xC, yC, width, height });//右下
				}

			}

			Camera::Set(camera);
		}
	};
}