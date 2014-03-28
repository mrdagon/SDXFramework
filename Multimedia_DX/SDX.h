#pragma once//☀DXLIB

#include<vector>
#include<string>
#include<memory>
#include<math.h>
#include<algorithm>
#include<list>
#include<iomanip>

#include<vector>

/** SDXフレームワーク共通の名前空間.*/
namespace SDX
{
	const double PAI = 3.1415926535897931;
	const double DEG = PAI / 180;
}

#include <DXLib/DXLib.h>
#undef max
#undef min

#pragma execution_character_set("utf-8")//charの文字コードをUTF-8に変更

int main(int argc, char* argv[]);
using ImageHandle = int;
using SoundHandle = int;
using ScreenHandle = int;
using WindowHandle = int;
using StickHandle = int;
using FontHandle = int;
using ColorData = int;
#define NULL_HANDLE -1

#include<xutility>
