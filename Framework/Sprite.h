//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/ISprite.h>
#include <Framework/Anime.h>

namespace SDX
{
	/** Imageスプライト.*/
	/** \include Model.h*/
	class SpImage : public ISprite
	{
	private:
		const Image *image;//!<

	public:
		SpImage(const Image *描画Image) :
			image(描画Image)
		{}

		/**.*/
		void Draw(const Point &座標, bool Cameraフラグ) override
		{
			if (Cameraフラグ)
			{
				image->DrawRotateAxis(Camera::Now()->Trans({ 座標.x + gapX, 座標.y + gapY }),
				{ axisX + image->GetWidth() / 2, axisY + image->GetHeight() / 2 },
				zoomX * Camera::Now()->GetZoom(),
				zoomY * Camera::Now()->GetZoom(),
				angle, isTurn);
			}
			else{
				image->DrawRotateAxis({ 座標.x + gapX, 座標.y + gapY },
				{ axisX + image->GetHeight() / 2,
				axisY + image->GetHeight() / 2 },
				zoomX,
				zoomY,
				angle, isTurn);
			}
		}
	};

	/** ImagePackスプライト.*/
	/** \include ModelSample.h*/
	class SpImageS : public ISprite
	{
	private:
		const ImagePack *imageS;//!<
		int index = 0;//!<
	public:
		SpImageS(const ImagePack *描画ImagePack) :
			imageS(描画ImagePack)
		{}

		/**.*/
		void SetIndex(int コマ番号)
		{
			index = コマ番号;
		}

		/**.*/
		int GetIndex()
		{
			return index;
		}

		/**.*/
		void Draw(const Point &座標, bool Cameraフラグ) override
		{
			const auto image = imageS->operator[](index);

			if (Cameraフラグ)
			{
				image->DrawRotateAxis
					(
					Camera::Now()->Trans({ 座標.x + gapX, 座標.y + gapY }),
					{ axisX + image->GetWidth() / 2, axisY + image->GetHeight() / 2 },
					zoomX * Camera::Now()->GetZoom(),
					zoomY * Camera::Now()->GetZoom(),
					angle,
					isTurn
					);
			}
			else{
				image->DrawRotateAxis
					(
				{ 座標.x + gapX, 座標.y + gapY },
				{ axisX + image->GetHeight() / 2, axisY + image->GetHeight() / 2 },
				zoomX,
				zoomY,
				angle,
				isTurn
				);
			}
		}
	};

	/** Animeスプライト.*/
	/** \include */
	class SpAnime : public ISprite
	{
	private:
		const Anime *anime;//!<
		Anime::Player counter;//!<
		double aniSpeed;//!<

	public:

		SpAnime(const Anime *描画Anime, double 再生速度 = 1) :
			anime(描画Anime),
			counter(描画Anime),
			aniSpeed(再生速度)
		{}

		void AnimeUpdate() override
		{
			counter.Update(aniSpeed);
		}

		void Draw(const Point &座標, bool Cameraフラグ) override
		{
			if (Cameraフラグ)
			{
				counter.GetFrame()->DrawRotateAxis
					(
					Camera::Now()->Trans({ 座標.x + gapX, 座標.y + gapY }),
					{ axisX + anime->GetWidth() / 2, axisY + anime->GetHeight() / 2 },
					zoomX * Camera::Now()->GetZoom(),
					zoomY * Camera::Now()->GetZoom(),
					angle,
					isTurn
					);
			}
			else
			{
				counter.GetFrame()->DrawRotateAxis
					(
				{ 座標.x + gapX, 座標.y + gapY },
				{ axisX + anime->GetWidth() / 2, axisY + anime->GetHeight() / 2 },
				zoomX,
				zoomY,
				angle,
				isTurn
				);
			}
		}
	};

	/** Fontスプライト.*/
	/** \include */
	class SpFont : public ISprite
	{
	private:
		const IFont *font;//!<
		std::string& refStr;//!<
		std::string str;//!<
		bool isReference;//!<
		Color rgb;//!<

	public:
		SpFont(const IFont *フォント, Color 描画色, double 縦倍率, double 横倍率, const char* 描画する文字列) :
			font(フォント),
			rgb(描画色),
			str(描画する文字列),
			refStr(str),
			isReference(false)
		{
			this->SetZoom(縦倍率, 横倍率);
		}

		SpFont(const IFont *フォント, Color 描画色, double 縦倍率, double 横倍率, std::string& 参照する文字列) :
			font(フォント),
			rgb(描画色),
			refStr(参照する文字列),
			isReference(true)
		{
			this->SetZoom(縦倍率, 横倍率);
		}

		void Draw(const Point &座標, bool Cameraフラグ) override
		{
			if (Cameraフラグ)
			{
				font->DrawExtend
					(
					Camera::Now()->Trans({ 座標.x + gapX, 座標.y + gapY }),
					zoomX * Camera::Now()->GetZoom(),
					zoomY * Camera::Now()->GetZoom(),
					rgb,
					refStr.c_str()
					);
			}
			else
			{
				font->DrawExtend
					(
				{ 座標.x + gapX, 座標.y + gapY },
				zoomX,
				zoomY,
				rgb,
				refStr.c_str()
				);
			}
		}

		void SetText(const char* 表示する文字)
		{
			refStr = 表示する文字;
		}
	};

	/** IFrameスプライト.*/
	/** \include */
	class SpFrame : public ISprite
	{
	private:
		const IFrame *bmpFrame;//!<
		double width;//!<
		double height;//!<

	public:
		SpFrame(const IFrame *描画する枠, double 幅, double 高さ) :
			bmpFrame(描画する枠),
			width(幅),
			height(高さ)
		{}

		void Draw(const Point &座標, bool Cameraフラグ) override
		{
			if (Cameraフラグ)
			{
				const Point 左上 = Camera::Now()->Trans({ 座標.x + gapX, 座標.y + gapY });

				bmpFrame->Draw
					(
				{
					左上.x,
					左上.y,
					width * zoomX * Camera::Now()->GetZoom(),
					height * zoomY * Camera::Now()->GetZoom()
				}
				);
			}
			else
			{
				bmpFrame->Draw
					(
				{
					座標.x + gapX,
					座標.y + gapY,
					width * zoomX,
					height * zoomY
				}
				);
			}
		}
	};

	/** マップチップスプライト.*/
	/** \include */
	class SpMap : public ISprite
	{
	private:
		ImagePack &chip;//!<
		int width;//!<
		int height;//!<
		int rotate;//!<
		std::vector< std::vector<int> > data;//!<
	public:

		SpMap(ImagePack& マップチップ, const char* ファイル名, int 幅, int 高さ, int 角度) :
			width(幅),
			height(高さ),
			rotate(角度),
			chip(マップチップ)
		{
			File csvFile(ファイル名, FileMode::Read);

			data.resize(幅);

			for (int a = 0; a < 幅; ++a)
			{
				data[a].resize(高さ);
			}

			auto lineS = csvFile.GetCsvToInt2();

			for (int a = 0; a < 高さ; ++a)
			{
				for (int b = 0; b < 幅; ++b)
				{
					data[b][a] = lineS[a][b];
				}
			}
		}

		void Draw(const Point &座標, bool カメラ有りフラグ) override
		{
			const int chipW = chip.GetWidth();
			const int chipH = chip.GetHeight();

			if (カメラ有りフラグ)
			{
				const int baseY = int(Camera::Now()->TransY(座標.y));
				const int baseX = int(Camera::Now()->TransX(座標.x));

				double posXA;
				double posYA;
				double posXB;
				double posYB;

				for (int a = 0; a < width; ++a)
				{
					posXA = baseX + chipW * a * Camera::Now()->GetZoom();
					posXB = baseX + chipW * (a + 1) * Camera::Now()->GetZoom();

					for (int b = 0; b < height; ++b)
					{
						posYA = baseY + chipH * b * Camera::Now()->GetZoom();
						posYB = baseY + chipH * (b + 1) * Camera::Now()->GetZoom();
						const int no = data[a][b];
						if (no == 0) continue;
						chip[no]->DrawExtend({ posXA, posYA }, { posXB, posYB });
					}
				}
			}
			else{
				for (int a = 0; a < width; ++a)
				{
					for (int b = 0; b < height; ++b)
					{
						const int no = data[a][b];
						if (no == 0) continue;
						chip[no]->Draw({ 座標.x + a*chipW, 座標.y + b*chipH });
					}
				}
			}
		}
	};

	/** Nullスプライト.*/
	/** \include */
	class SpNull : public ISprite
	{
	public:

		SpNull()
		{}

		void Draw(const Point &座標, bool カメラ有りフラグ) override
		{}
	};
}